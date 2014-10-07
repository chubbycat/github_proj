#ifndef _CUPID_TIME_HELPER_H__
#define _CUPID_TIME_HELPER_H__

#include <time.h>

namespace cupid
{
/**
 * ʱ���ֶ�
 * @see #time_add
 */
enum time_field_t 
{
	YEAR,
	MONTH,
	DAY,
	HOUR,
	MINUTE,
	SECOND
};

/**
 * ʱ�䴦����
 * @param t Դʱ��
 * @param f ʱ���ֶ�
 * @param i �ӵ�ֵ,��Ϊ������ʾ��
 * @return time_t <0ʱ��ʾ������Χ
 */
inline time_t time_add(time_t t, time_field_t f, int i)
{
	struct tm curr;
	switch(f) 
	{
	case SECOND:
		return t+i;
	case MINUTE:
		return t+i*60;
	case HOUR:
		return t+i*60*60;
	case DAY:
		return t+i*60*60*24;
	case MONTH:
		localtime_r(&t, &curr);
		curr.tm_year += (curr.tm_mon-1+i)/12;
		curr.tm_mon = (curr.tm_mon-1+i) %12+1;
		return mktime(&curr);
	case YEAR:
		localtime_r(&t, &curr);
		curr.tm_year += i;
		return mktime(&curr);
	default:
		return 0;
	}

	return 0;
}

} // end of namespace cupid

#endif // _CUPID_TIME_HELPER_H__
