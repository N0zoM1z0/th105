#include "library/ZlibCrcTable.cpp"
// Real file-buffer/reader/package/CRC source context. Original TU unknown;
// no code stubs or source-level private register declarations.
#include "assets/PackageFileIndexNode.cpp"
#include "assets/PackageFileEntry.cpp"
#include "assets/FileReader.cpp"
#include "assets/CaseInsensitivePathHash.cpp"
#include <cstring>
#include <cstdlib>
#include <new>
namespace th105 {
extern bool g_bootstrap_mode;
class FileBufferContext {
public:
 unsigned char *data_00;
 unsigned size_04;
 FileBufferContext():data_00(0),size_04(0){}
 ~FileBufferContext(){if(data_00)free(data_00);}
 bool load_plain(const char *);
 bool load_encoded(const char *);
 bool load_text(const char *);
 bool load_csv(const char *);
};
// Capture the real destination/length arguments before virtual reader dispatch.
// This ordinary forwarding helper is inlined naturally, without a forced ABI.
inline bool read_file_buffer(CFileReader *file, void *destination, FileSize size)
{
 return file->read(destination,size);
}
bool FileBufferContext::load_plain(const char *path)
{
 FileReaderOwner file;
 if(!file.open(path))return false;
 CFileReader *reader=file.reader;
 size_04=reader->size();
 if(size_04!=0){
  if(data_00!=0)free(data_00);
  data_00=new unsigned char[size_04+1];
  data_00[size_04]=0;
  read_file_buffer(reader,data_00,size_04);
 }
 return true;
}
bool FileBufferContext::load_encoded(const char *path)
{
 FileReaderOwner file;
 if(!file.open(path))return false;
 CFileReader *reader=file.reader;
 size_04=reader->size();
 if(size_04!=0){
  if(data_00!=0)free(data_00);
  data_00=new unsigned char[size_04+1];
  data_00[size_04]=0;
  read_file_buffer(reader,data_00,size_04);
  unsigned char key=0x8b,delta=0x71;
  unsigned char *cursor=data_00;
  for(unsigned i=0;i<size_04;++i,++cursor){
   *cursor^=key;key=static_cast<unsigned char>(key+delta);delta=static_cast<unsigned char>(delta-107);
  }
 }
 return true;
}
bool FileBufferContext::load_text(const char *path)
{
 if(g_bootstrap_mode){
  char encoded[260];unsigned length=std::strlen(path);
  strcpy_s(encoded,260,path);std::memcpy(encoded+length-4,".cv0",4);
  return load_encoded(encoded);
 }
 return load_plain(path);
}
bool FileBufferContext::load_csv(const char *path)
{
 if(g_bootstrap_mode){
  char encoded[260];unsigned length=std::strlen(path);
  strcpy_s(encoded,260,path);std::memcpy(encoded+length-4,".cv1",4);
  return load_encoded(encoded);
 }
 return load_plain(path);
}
}

#include <deque>
#include <string>
namespace th105 {
struct CsvContext {
 typedef std::deque<std::string> Row;
 typedef std::deque<Row> Rows;
 Rows rows;
 Rows::iterator row;
 Row::iterator field;
 bool comment,quote;
 bool load(const char *path);
 void parse(const char *text);
 void reset();
 void clear_rows() throw();
};
typedef char CsvContextSize[sizeof(CsvContext)==0x30?1:-1];
void CsvContext::clear_rows() throw(){ rows.clear(); }
bool CsvContext::load(const char *path)
{
 FileBufferContext file;
 if(!file.load_csv(path))return false;
 parse(reinterpret_cast<const char *>(file.data_00));
 reset();
 return true;
}
void CsvContext::reset()
{
 row=rows.begin();
 if(row!=rows.end())field=row->begin();
}
void CsvContext::parse(const char *text)
{
 comment=false;quote=false;
 clear_rows();
 Row pending;
 std::string value;
 for(const char *cursor=text;*cursor;++cursor){
  switch(*cursor){
  case '#':comment=true;break;
  case ',':
   if(!comment){pending.push_back(value);value.erase(value.begin(),value.end());}
   break;
  case '"':quote=!quote;break;
  case '\r':
   if(quote && !comment)value.insert(value.end(),*cursor);
   break;
  case '\n':
   if(quote){
    if(!comment)value.insert(value.end(),*cursor);
   }else{
    if(!comment){pending.push_back(value);value.erase(value.begin(),value.end());rows.push_back(pending);pending.clear();}
    comment=false;
   }
   break;
  default:
   if(!comment)value.insert(value.end(),*cursor);
   break;
  }
 }
}
}
