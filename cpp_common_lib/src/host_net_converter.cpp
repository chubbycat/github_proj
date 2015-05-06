#include "net/host_net_converter.h"

namespace cupid
{

/*
 * Convert a 64 bit value to network byte order.
 */
uint64_t hton64(uint64_t val)
{
    union 
	{ 
		uint64_t ll;
        uint32_t l[2];
    } w, r;

    /* platform already in network byte order? */
    if(htonl(1) == 1L)
	{
        return val;
	}
    w.ll = val;
    r.l[0] = htonl(w.l[1]);
    r.l[1] = htonl(w.l[0]);
	
    return r.ll;
}

/*
 * Convert a 64 bit value from network to host byte order.
 */
uint64_t ntoh64(uint64_t val)
{
    union 
	{ 
		uint64_t ll;
        uint32_t l[2];
    } w, r;

    /* platform already in network byte order? */
    if(htonl(1) == 1L)
	{
        return val;
	}
    w.ll = val;
    r.l[0] = ntohl(w.l[1]);
    r.l[1] = ntohl(w.l[0]);
	
    return r.ll;
}

}
