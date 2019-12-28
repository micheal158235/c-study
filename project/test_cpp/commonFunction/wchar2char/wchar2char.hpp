#ifndef _WCHAR2CHAR_H
#define _WCHAR2CHAR_H

#include<string>

namespace QX{
	std::string Wstr2str(const std::wstring& ws);
	std::wstring Str2wstr(const std::string& str);
	std::string WcharToChar(const wchar_t* wp);
	std::wstring CharToWchar(const char* c);
	void TestWstr2str(void);
	void TestStr2wstr(void);
	void TestWcharToChar(void);
	void TestCharToWchar(void);
}

#endif