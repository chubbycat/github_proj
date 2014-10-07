#include <stdio.h>

#include "header/common_header.h"

namespace cupid
{

int check_common_header(const void* data_in_net_order, 
								uint32_t data_len, 
								cupid::common_header_t& header)
{
	if (NULL == data_in_net_order || data_len < 2 /*magic len*/) 
	{
		return 1;
	}
	const uint16_t* magic = reinterpret_cast<const uint16_t*>(data_in_net_order);
	if (COMMON_HEADER_MAGIC_NUM != ntohs(*magic)) 
	{
		return -1;
	}
	if (data_len < COMMON_HEADER_SIZE)
	{
		return 1;
	}
	void* p = const_cast<void*>(data_in_net_order);
	header = *(reinterpret_cast<cupid::common_header_t*>(p));
	header.to_host_order();
	if (data_len < header.len)
	{
		return 1;
	}
	
	return 0;
}
}

