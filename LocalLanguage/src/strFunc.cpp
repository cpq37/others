#include "strFunc.h"

#ifdef WIN32
std::string string_To_UTF8(const std::string & str) 
{ 
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0); 

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2); 

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), pwBuf, nwLen); 

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 

	char * pBuf = new char[nLen + 1]; 
	ZeroMemory(pBuf, nLen + 1); 

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL); 

	std::string retStr(pBuf); 

	delete []pwBuf; 
	delete []pBuf; 

	pwBuf = NULL; 
	pBuf  = NULL; 

	return retStr; 
} 

std::string UTF8_To_string(const std::string & str) 
{ 
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); 

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2); 

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), pwBuf, nwLen); 

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 

	char * pBuf = new char[nLen + 1]; 
	memset(pBuf, 0, nLen + 1); 

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL); 

	std::string retStr = pBuf; 

	delete []pBuf; 
	delete []pwBuf; 

	pBuf = NULL; 
	pwBuf = NULL; 

	return retStr; 
} 


std::string UTF8_To_string_Ex(const std::string & str) 
{ 
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0); 

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2); 

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), pwBuf, nwLen); 

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL); 

	char * pBuf = new char[nLen + 1]; 
	memset(pBuf, 0, nLen + 1); 

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL); 
	char* pChar = new char[nLen + 1];
	memset(pChar, 0, nLen + 1);
	int i = 0;
	while( i < nLen + 1 )
	{

		char c = pBuf[i];
		if ( (c=='_') || (c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') )
		{
			pChar[i] = c;
		}
		else if( c )
		{
			pChar[i] = '_';
		}
		i++;
	}

	std::string retStr = pChar; 

	delete []pBuf; 
	delete []pwBuf; 
	delete []pChar;

	pBuf = NULL; 
	pwBuf = NULL; 
	pChar = NULL;

	return retStr; 
} 

#endif

std::string insteadSpecialChar(const std::string &str)
{
	std::string retStr = "";
	int nLen = (int)str.length();
	int i = 0;
	while( i < nLen )
	{

		char c = str.at(i);
		if ( (c=='_') || (c >= 'A' && c <='Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') )
		{
			retStr += c;
		}
// 		else if( '\"' == c )
// 		{
// 			retStr = retStr + '\\' + c;
// 		}
		else if( c )
		{
			retStr += '_';
		}
		i++;
	}

	return retStr;
}

std::string string_replace(const std::string&s1, const std::string&s2, const std::string&s3)
{
	std::string retStr = s1;
	std::string::size_type pos=0;
	std::string::size_type a=s2.size();
	std::string::size_type b=s3.size();
	while((pos=retStr.find(s2,pos))!=std::string::npos)
	{
		retStr.replace(pos,a,s3);
		pos+=b;
	}

	return retStr;
}