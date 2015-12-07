
#ifndef __STRFUNC_H
#define __STRFUNC_H

#include <string>

#ifdef WIN32
#include <windows.h>



std::string string_To_UTF8(const std::string & str);

std::string UTF8_To_string(const std::string & str);

std::string UTF8_To_string_Ex(const std::string & str);

#else

std::string insteadSpecialChar(const std::string &str);

#endif // WIN32


#endif
