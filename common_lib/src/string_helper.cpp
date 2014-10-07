#include <string>
#include "string/string_helper.h"

namespace cupid
{
std::string trim_left(const std::string& s,const std::string& filt)
{
	if(0 == s.length()) 
	{
		return std::string();
	}
	char* head = const_cast<char *>(s.c_str());
	char* p = head;
	while(*p) 
	{
		bool b = false;
		for(size_t i=0; i<filt.length(); i++) 
		{
			if((unsigned char)*p == (unsigned char)filt.c_str()[i]) 
			{
				b = true;
				break;
			}
		}
		if(!b) break;
		p++;
	}
	return std::string(p,0,s.length()-(p-head));
}

std::string trim_right(const std::string& s,const std::string& filt)
{
	if(0 == s.length()) 
	{
		return std::string();
	}
	char* head = const_cast<char *>(s.c_str());
	char* p = head + s.length() - 1;
	while(p >= head) 
	{
		bool b = false;
		for(size_t i=0; i<filt.length(); i++) 
		{
			if((unsigned char)*p == (unsigned char)filt.c_str()[i]) 
			{
				b=true;
				break;
			}
		}
		if(!b) 
		{
			break;
		}
		--p;
	}
	return std::string(head, 0, p+1-head);
}


} // end of namespace cupid

