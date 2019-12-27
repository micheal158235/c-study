/*
 * wchar2char.cpp
 *
 * Copyright 2019, XiaoQian. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
wchar_t：在windows下是Unicode编码，也就是俗称宽字节,16位或32位，根据C或C++库而定;
char：当然就是指一个字节，在windows下面默认是gbk编码的.
所以在windows 下 wchar_t 转 char也就是编码转化
wchar_t *字符串和char *字符串的集中互转方法有如下几种方法

方法一：利用Windows的宏W2A,A2W
	USES_CONVERSION;
	char* test1 = W2A(L"我是宽字节");//转化成默认
	wchar_t* test12 = A2W("我是窄字节");

方法二：利用Windows里的ATL里面的类CW2A和CA2W,在转换时候还可以顺便调整编码，不加第二个参数就是保持GBK不变
	std::string test3 = CW2A(L"中文字符", CP_UTF8);//一般可以加一下第二个参数，顺便切换编码
	std::wstring test4 = CA2W("中文字符");//一般不用加第二个参数

方法三：利用Windows API中的函数 WideCharToMultiByte 和 MultiByteToWideChar ，而且也是可以带自定义编码转换
以下函数用法： CharToWchar可以等效于CW2A,WcharToChar可以等效于CA2W

方法四：将使用标准C的mbstowcs方法和wcstombs方法，且配合标准C的setlocale方法，这也是利用标准库跨平台的做法，
但是过程没法直接转成自定义的编码，需要额外转码。所以在Windows平台开发的话不推荐。
 */

//---------------------------方法四----------------------------//
#include<iostream>
#include<stdlib.h>
#include<string>
#include<locale.h>

namespace QX{
	using namespace std;
	 
	/**
	* 将宽字符串转换成普通字符串
	*/
	string wstr2str(const wstring& ws)
	{
		//获取当前的locale
		string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
	 
		const wchar_t* pws = ws.c_str();
		int wsLen = ws.length();
		int bufLen = sizeof(wchar_t) * wsLen + 1;
		char* pRes = new char[bufLen];
		memset(pRes, '\0', bufLen);
		//wcstombs_s(&convertedChars,dest,dByteNum,wcs,_TRUNCATE)
		size_t convertLen = 0;
		wcstombs_s(&convertLen, pRes, bufLen, pws, _TRUNCATE);
		string resStr = pRes;
		delete [] pRes;
	 
		//恢复locale
		setlocale(LC_ALL, curLocale.c_str());
	 
		return resStr;
	}
	 
	/**
	* 将普通字符串转换成宽字符串
	*/
	wstring str2wstr(const string& str)
	{
		//获取当前的locale
		string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
	 
		const char* pstr = str.c_str();
		int strLen = str.length();
		int bufLen = sizeof(char) * strLen + 1;
		wchar_t* pRes = new wchar_t[bufLen];
		wmemset(pRes, '\0', bufLen);
		//mbstowcs_s(&convertedChars,dest,charNum,source,_TRUNCATE);
		size_t convertLen = 0;
		mbstowcs_s(&convertLen, pRes, bufLen, pstr, _TRUNCATE);
		wstring resStr = pRes;
		delete[] pRes;
	 
		//恢复locale
		setlocale(LC_ALL, curLocale.c_str());
		return resStr;
	}
	 
	void test4()
	{
		wstring ws = L"欢迎使用宽字符abc159";
		string str = wstr2str(ws);
		cout << "转换之后的字符串 = " << str << endl;
		
		setlocale(LC_ALL, "chs");//要想输出宽字符，必须设置这个
		string s = "欢迎使用宽字符abc159";
		wstring wstr = str2wstr(s);
		wcout << wstr << endl;
		setlocale(LC_ALL, "C");
	}

}

//---------------------------方法三----------------------------//
#if defined(WIN32)
#include <windows>
#endif
namespace QX{
	
	/**
	* 将宽字符串转换成普通字符串
	*/
	std::string WcharToChar(const wchar_t* wp)
	{
		std::string str = "";
#if defined(WIN32)
		int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
		char	*m_char = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
		m_char[len] = '\0';
		str = m_char;
		delete m_char;
#endif
		return str;
	}
	
	/**
	* 将普通字符串转换成宽字符串
	*/
	std::wstring CharToWchar(const char* c)
	{
		std::wstring str = L"";
#if defined(WIN32)
		int len = MultiByteToWideChar(CP_ACP, 0, c, strlen(c), NULL, 0);
		wchar_t* m_wchar = new wchar_t[len + 1];
		MultiByteToWideChar(CP_ACP, 0, c, strlen(c), m_wchar, len);
		m_wchar[len] = '\0';
		str = m_wchar;
		delete m_wchar;
#endif
		return str;
	}
	
	test3()
	{
		char     chr[8];//长度为8个字节
		wchar_t  *wchar = L"徐凯文";
		std::string str;
		std::wstring wstr;
		//wchar_t to char
		str = wcharTochar(wchar);
		//char to wchar_t
		wstr = charTowchar(chr, wchar, sizeof(wchar_t)* 4);
		cout << "str = " << str << endl;
		wcout << "wstr = " << wstr << endl;
	}

}

