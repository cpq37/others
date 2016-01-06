
#ifndef HEADER_COMMONTYPE_H
#define HEADER_COMMONTYPE_H

typedef unsigned char      BOOL;
typedef unsigned char      U8;
typedef unsigned short     U16;
typedef unsigned int       U32;
typedef unsigned long long U64;

typedef signed char        S8;
typedef signed short       S16;
typedef signed int         S32;
typedef signed long long   S64;

#if !defined(TRUE) && !defined(FALSE)
#define FALSE false
#define TRUE  true
#endif

#ifndef null
#define null 0
#endif

#ifndef NULL 
#define NULL 0
#endif

#endif /* HEADER_COMMONTYPE_H */

 
