#ifndef __COMMMON_HEADER_H__
#define __COMMMON_HEADER_H__

#include <stdint.h>

#include "cupid_common.h"

namespace cupid
{

#define COMMON_HEADER_MAGIC_NUM   0xbcda
#define COMMON_HEADER_DEF_VER     0x1

#define COMMON_HEADER_SIZE    24

struct common_header_t
{
	uint16_t magic;
	uint16_t ver;
	uint32_t len; // header_len + body_len
	uint32_t seq;
	uint32_t cmd;
	uint64_t log_id;
	
	common_header_t()
	{
		magic = COMMON_HEADER_MAGIC_NUM;
		len = 0;
		ver = COMMON_HEADER_DEF_VER;
		seq = 0;
		cmd = 0;
		log_id = 0;
	}
	
	void to_host_order()
	{
		magic = ntohs(magic);
		ver = ntohs(ver);
		cmd = ntohl(cmd);
		seq = ntohl(seq);
		len = ntohl(len);
		log_id = ntoh64(log_id);
	}

	void to_net_order()
	{
		magic = htons(magic);
		ver = htons(ver);
		cmd = htonl(cmd);
		seq = htonl(seq);
		len = htonl(len);
		log_id = hton64(log_id);
	}
};

/**
 * @return 0: OK, 1: not enough data, -1: not common_header, should close connection
 */
extern int check_common_header(const void* data_in_net_order, 
									uint32_t data_len, 
									cupid::common_header_t& header);
}

#endif 

