#include <zlib.h>
#include <stddef.h>

// Shared game-memory codec for score files and network replay packets.
// Provider headers/sources are independently pinned by png-source-lock.json.
namespace th105 {
typedef char ReplayZStreamSize[sizeof(z_stream) == 56 ? 1 : -1];
typedef char ReplayZStreamAlignment[__alignof(z_stream) == 4 ? 1 : -1];
typedef char ReplayZStreamOutput[offsetof(z_stream, avail_out) == 16 ? 1 : -1];
// Native early failures do not call End. Preserve this ownership policy.

unsigned __cdecl encode_score_payload_4067f0(const unsigned char *input,unsigned length,unsigned char *output,unsigned capacity)
{
 z_stream stream;
 stream.zalloc=0;stream.zfree=0;stream.opaque=0;
 if(deflateInit(&stream,Z_DEFAULT_COMPRESSION)!=Z_OK)return 0;
 stream.next_in=const_cast<unsigned char *>(input);
 stream.avail_in=length;
 stream.next_out=output;
 stream.avail_out=capacity;
 int status=deflate(&stream,Z_FINISH);
 if(status!=Z_STREAM_END && (status!=Z_OK || !stream.avail_out))return 0;
 if(deflateEnd(&stream)!=Z_OK)return 0;
 return capacity-stream.avail_out;
}
unsigned __cdecl decode_score_payload_406890(const unsigned char *input,unsigned length,unsigned char *output,unsigned capacity)
{
 z_stream stream;
 stream.zalloc=0;stream.zfree=0;stream.opaque=0;
 if(inflateInit(&stream)!=Z_OK)return 0;
 stream.next_in=const_cast<unsigned char *>(input);
 stream.avail_in=length;
 stream.next_out=output;
 stream.avail_out=capacity;
 int status=inflate(&stream,Z_NO_FLUSH);
 if(status!=Z_STREAM_END && (status!=Z_OK || !stream.avail_out))return 0;
 if(inflateEnd(&stream)!=Z_OK)return 0;
 return capacity-stream.avail_out;
}
}
