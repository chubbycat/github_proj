#ifndef __HOST_NET_CONVERTER_H__
#define __HOST_NET_CONVERTER_H__

#include <stdint.h>
#include <arpa/inet.h>

namespace cupid
{

extern uint64_t ntoh64(uint64_t val);

extern uint64_t hton64(uint64_t val);

}

#endif 

