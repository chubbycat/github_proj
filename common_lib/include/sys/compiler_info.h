#ifndef __CUPID_COMPILER_INFO_H__
#define __CUPID_COMPILER_INFO_H__

#ifdef __GNUC__
/// convert gcc version to a number. eg, gcc 4.5.1 -> 40501
#define GCC_VERSION_NUMBER() (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#endif

#endif // __CUPID_COMPILER_INFO_H__
