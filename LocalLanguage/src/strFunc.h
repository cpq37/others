
#ifndef __STRFUNC_H
#define __STRFUNC_H

#include <string>

#ifdef WIN32
#include <windows.h>

std::string string_To_UTF8(const std::string & str);

std::string UTF8_To_string(const std::string & str);

std::string UTF8_To_string_Ex(const std::string & str);

#endif // WIN32

std::string insteadSpecialChar(const std::string &str);
std::string string_replace(const std::string&s1, const std::string&s2, const std::string&s3);

#endif //__STRFUNC_H
