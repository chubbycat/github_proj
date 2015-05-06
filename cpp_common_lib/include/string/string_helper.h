#ifndef __CUPID_STRING_HELPER_H__
#define __CUPID_STRING_HELPER_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <errno.h>

namespace cupid
{
struct comm_error_t: public std::logic_error
{ 
	comm_error_t(const std::string& s);
};

/**
 * @brief 一个字符串是否全部为数字(0-9)
 * @param s 输入字符串
 * @return true/false
 */
inline bool is_digits(const std::string& s)
{
	if (0 == s.length()) 
	{
		return false;
	}
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i])) 
		{
			return false;
		}
	}
	return true;
}

/**
 * @brief 一个字符串是否全部为16进制数字(0-9/a-f/A-F)
 * @param s 输入字符串
 * @return true/false
 */
inline bool is_xdigits(const std::string& s)
{
	if(s.length() == 0) return false;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isxdigit(s[i])) return false;
	}
	return true;
}

/**
 * @brief 转为大小
 */
inline std::string upper(const std::string &s)
{
	std::string s2;
	for(size_t i=0;i<s.length();i++) 
	{
		s2 += ((unsigned char)toupper(s[i]));
	}
	return s2;
}

/**
 * @brief 转为小写
 */
inline std::string lower(const std::string &s)
{
	std::string s2;
	for(size_t i=0;i<s.length();i++) 
	{
		s2 += ((unsigned char)tolower(s[i]));
	}
	return s2;
}

/**
 * @brief 删除s左边所有包含filt中字符的字符
 * @param s 输入字符串
 * @param filt filt串
 * @return string trim后的值
 */
std::string trim_left(const std::string& s,const std::string& filt=" ");

/**
 * @param s 输入字符串
 * @param filt filt串
 * @return string trim后的值
 */
std::string trim_right(const std::string &s,const std::string& filt=" ");

/**
 * @brief trim_left+trim_right
 * @param s 输入字符串
 * @param filt filt串
 * @return string trim后的值
 */
inline std::string trim(const std::string &s,const std::string& filt=" ")
{
	return trim_right(trim_left(s, filt),filt);
}

/**
 * @brief 通用模板方法: 类型T转为字符串
 * @param t 类型T的对象
 * @return 字符串
 */
template<typename T> 
std::string tostr(const T& t)
{
	std::ostringstream s;
	s << t;
	return s.str();
}

/**
 * @brief 通用模板方法: 字符串转为类型T
 * @param s 
 * @return T 类型T
 */
template<typename T> T 
strto(const std::string& s)
{
	std::istringstream is(s);
	T t;
	is >> t;
	return t;
}

/**
 * @brief 通用模板方法: pair转为字符串
 * @param it  map等容器的iterator
 * @return 字符串
 */
template<typename F, typename S> 
std::string tostr(const std::pair<F, S>& it)
{
	std::ostringstream s;
	s << "["+(it.first)+"="+(it.second)+"]";
	return s.str();
}

/**
 * @brief 通用模板方法: iterator转为字符串
 * @param itbegin  容器的iterator begin
 * @param itend  容器的iterator end
 * @return 字符串
 */
template <typename I> 
std::string tostr(I itbegin,I itend)
{
	std::string s;
	I it = itbegin;
	for(I it=itbegin; it!=itend; it++) 
	{
		s.append(tostr(*it));
		s.append(" ");
	}
	return s;
}

/**
* 解析字符串,用分隔符号分隔,保存在vector里
* 例子: |a|b||c|
*
* 如果withEmpty=true时, 采用|分隔为:"","a", "b", "", "c", ""
* 如果withEmpty=false时, 采用|分隔为:"a", "b", "c"
* @param sStr: 输入字符串
* @param sSep: 分隔字符串(每个字符都算为分隔符)
* @param withEmpty: true: 空的也算一个元素, false:空的过滤
* @return vector<string>
*/
template<typename T> 
std::vector<T> sepstr(const std::string& sStr, const std::string& sSep, bool withEmpty = true)
{
    std::vector<T> vt;

    std::string::size_type pos = 0;
    std::string::size_type pos1 = 0;

    while(true)
    {
        std::string s;
        pos1 = sStr.find_first_of(sSep, pos);
        if(pos1 == std::string::npos)
        {
            if(pos + 1 <= sStr.length())
            {
                s = sStr.substr(pos);
            }
        }
        else if(pos1 == pos)
        {
            s = "";
        }
        else
        {
            s = sStr.substr(pos, pos1 - pos);
            pos = pos1;
        }

        if(withEmpty)
        {
            vt.push_back(strto<T>(s));
        }
        else
        {
            std::string tmp = strto<T>(s);
            if(!tmp.empty())
            {
                vt.push_back(tmp);
            }
        }

        if(pos1 == std::string::npos)
        {
            break;
        }

        pos++;
    }

    return vt;
}

/*******************************************************************************************************
 * 简易用法
 */

inline uint32_t s2u(const std::string& s) throw (cupid::comm_error_t)
{
	errno = 0;
	uint32_t u = strtoul(s.c_str(), NULL, 10);
	if(errno != 0) 
	{
		throw cupid::comm_error_t(std::string("cupid::s2u: not digits:")+s);
	}

	return u;
}

inline uint32_t s2u(const std::string& s, uint32_t defaultvalue)
{
	errno = 0;
	uint32_t u = strtoul(s.c_str(), NULL, 10);
	if(errno != 0) 
	{
		return defaultvalue;
	}

	return u;
}
 
/**
 * uint32_t转string
 * @see #s2u
 */
inline std::string u2s(const uint32_t u)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%u", u);
	return std::string(tmp_str);
}
/**
 * uint64_t转string
 * @see #s2ul
 */
inline std::string ul2s(const uint64_t u)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%lu", u);
	return std::string(tmp_str);
}

/**
 * uint32_t转string(16进制形式)
 * @see #sx2u
 */
inline std::string u2sx(const uint32_t u)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%x", u);
	return std::string(tmp_str);
}
/**
 * uint64_t转string(16进制形式)
 * @see #sx2ul
 */
inline std::string ul2sx(const uint64_t u)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%lx", u);
	return std::string(tmp_str);
}

/**
 * int转string
 * @see #s2i
 */
inline std::string i2s(const int i)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%d", i);
	return std::string(tmp_str);
}

/**
 * int64_t转string
 * @see #s2l
 */
inline std::string l2s(const int64_t i)
{
	char tmp_str[64] ={0};
	snprintf(tmp_str, sizeof(tmp_str), "%ld", i);
	return std::string(tmp_str);	
}

/**
 * char转string
 * @see #s2c
 */
inline std::string c2s(const char c)
{
	if(c==0) return std::string("");
	return std::string()+c;
}

inline bool is_qq(uint32_t q)
{
	return (q > 10000);
}

inline bool is_qq(const std::string& s)
{
	return is_qq(s2u(s, 0));
}

inline bool is_cellphone(const std::string& s)
{
	if(!cupid::is_digits(s) || s.size() < 4)
		return false;
	// 13xxx 15xxx 18xxx
	if(s[0] == '1' && (s[1] == '3' || s[1] == '4' || s[1] == '5' || s[1] == '8')) {
		return s.length() == 11;
	}
	// 013xxx 015xxx 018xxx
	if(s[0] == '0' && s[1] == '1' && (s[2] == '3' || s[2] == '4' || s[2] == '5' || s[2] == '8')) {
		return s.length() == 12;
	}
	// 8613xxx 8615xxx 8618xxx
	if(s[0] == '8' && s[1] == '6' && s[2] == '1' && (s[3] == '3' || s[3] == '4' || s[3] == '5' || s[3] == '8')) {
		return s.length() == 13;
	}
	return false;
}

inline bool is_telephone(const std::string& s)
{
	if(!cupid::is_digits(s)) return false;
	// 0755xxx
	if(s[0] == '0') {
		return (s.length() >= 10 && s.length() <= 12);
	}
	// 86755xxx
	if(s[0] == '8' && s[1] == '6') {
		if(s[2] == '1' && (s[3] == '3' || s[3] == '5' || s[3] == '8'))
			return false;
		return (s.length() >= 11 && s.length() <= 13);
	}
	return false;
}

inline bool is_phone(const std::string& s)
{
	return (is_cellphone(s) || is_telephone(s));
}

//////////////////////////////////////////////////////////////////////////
// StartsWith Utility

/** Tests if this sequence starts with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \param pr	equal compare
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename II1, typename II2, typename Pr >
inline bool string_start_with(II1 f1, II1 l1, II2 f2, II2 l2, Pr pr)
{
	for(; f1 != l1 && f2 != l2; ++f1, ++f2){
		if(!pr(*f1, *f2))
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param f1	first position of source sequence
 *  \param l1	last position of source sequence
 *  \param f2	first position of prefix sequence
 *  \param l2	last position of prefix sequence
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename II1, typename II2 >
inline bool string_start_with(II1 f1, II1 l1, II2 f2, II2 l2)
{
	for(; f1 != l1 && f2 != l2; ++f1, ++f2){
		if(*f1 != *f2)
			return false;
	}
	return f2 == l2;
}

/** Tests if this sequence starts with the specified prefix sequence
 *  \param s1	source string
 *  \param s2	prefix string
 *  \return		true if source sequence starts with prefix sequence
 */
template < typename ch_t, typename tr_t, typename a_t >
inline bool string_start_with(const std::basic_string<ch_t, tr_t, a_t>& s1,
						 const std::basic_string<ch_t, tr_t, a_t>& s2)
{
	return string_start_with(s1.begin(), s1.end(), s2.begin(), s2.end());
}

} // end of namespace cupid

#endif // __CUPID_STRING_HELPER_H__
