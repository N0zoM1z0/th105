// Real non-DYNAMIC_CRC_TABLE provider from zlib1.2.3 crc32.c, with its
// unchanged generated table. C++ spelling retains the actual C ABI.
#include "../../third_party/zlib-1.2.3/zutil.h"
#define TBLS 8
#include "../../third_party/zlib-1.2.3/crc32.h"
extern "C" const unsigned long FAR * ZEXPORT get_crc_table(void)
{
 return (const unsigned long FAR *)crc_table;
}
