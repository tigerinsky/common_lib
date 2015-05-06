#ifndef __SIGN_H_
#define __SIGN_H_

#include "city_hash.h"

//calc string 64 bit hash value
#define sign64_str(buf, len) \
    (CityHash64(buf, len))

//calc string 128 bit hash value
#define sign128_str(buf, len) \
    (CityHash128(buf, len))

//calc binary 128 bit hash value
#define sign128_bin(buf, len) \
    (CityHashCrc128(buf, len))


#endif


