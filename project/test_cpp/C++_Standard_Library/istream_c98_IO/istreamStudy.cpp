/*
 * istreamStudy.hpp
 * @time    :2020/01/02 10:37
 * @location:JieShun ShenZhen
 * @Copyright 2020, XiaoQian. All rights reserved.
 * @commit:练习c++标准库中的istream类
 C++cin详解及清空输入缓冲区:
输入原理：
程序的输入都有一个缓冲区，即输入缓冲区。
一次输入过程是这样的，当一次键盘输入结束时会将输入的数据存入输入缓冲区，而cin对象直接从输入缓冲区中取数据。
正因为cin对象是直接从缓冲区取数据的，所以有时候当缓冲区中有残留数据时，cin对象会直接取得这些残留数据而不会请求键盘输入
一. cin>>
该操作符是根据后面变量的类型读取数据。
输入结束条件 ：遇到Enter、Space、Tab键。
对结束符的处理 ：详见下面 TestGetline() 函数体

[参考文章]：https://blog.csdn.net/selina8921/article/details/79067941
 */
 
#include <limits>
#include <iostream>     // std::cin, std::cout

#include "istreamStudy.hpp"

namespace QX{
	/********************************************/
	/*虽然可以使用 cin 和 >> 运算符来输入字符串，但它可能会导致一些需要注意的问题。
    当 cin 读取数据时，它会传递并忽略任何前导白色空格字符（空格、制表符或换行符）。
	一旦它接触到第一个非空格字符即开始阅读，当它读取到下一个空白字符时，它将停止读取。
	以下面的语句为例：
	cin >> namel;
	可以输入 "Mark" 或 "Twain"，但不能输入 "Mark Twain"，
	因为 cin 不能输入包含嵌入空格的字符串。下面程序演示了这个问题：	
	*/
	/********************************************/
	int TestGetline(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "--------Test getline-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		//注意： 
		//（1）cin>>等价于cin.operator>>()，即调用成员函数operator>>()进行读取数据。 
		//（2）当cin>>从缓冲区中读取数据时，若缓冲区中第一个字符是空格、tab或换行这些分隔符时，cin>>会将其忽略并清除，
		//     继续读取下一个字符，若缓冲区为空，则继续等待。但是如果读取成功，字符后面的分隔符是残留在缓冲区的，cin>>不做处理。 
		//（3）不想略过空白字符，那就使用 noskipws 流控制。比如cin>>noskipws>>input;
		//---从键盘输入:[回车][回车][回车]a[回车]5[回车]2.33[回车]hello[回车]，看看效果---//
		char a;
		int b;
		float c;
		std::string str;
		std::cin>>a>>b>>c>>str;
		std::cout<<a<<" "<<b<<" "<<c<<" "<<str<<std::endl;
		std::string test;
		getline(std::cin,test);//不阻塞
		std::cout<<"test:"<<test<<std::endl;
		//从结果可以看出，cin>>对缓冲区中的第一个换行符视而不见，采取的措施是忽略清除，继续阻塞等待缓冲区有效数据的到来。
		//但是，getline()读取数据时，并非像cin>>那样忽略第一个换行符，getline()发现cin的缓冲区中有一个残留的换行符，
		//不阻塞请求键盘输入，直接读取，送入目标字符串后，再将换行符替换为空字符’\0’，因此程序中的test为空串。
		std::cout << "--------------1-------------" << std::endl;
		
		//---输入John Doe再回车输入chicago---//
		//请注意，以下这段代码运行后，用户根本没有机会输入 city 城市名。
		//因为在第一个输入语句中，当 cin 读取到 John 和 Doe 之间的空格时，
		//它就会停止阅读，只存储 John 作为 name 的值。在第二个输入语句中， 
		//cin 使用键盘缓冲区中找到的剩余字符，并存储 Doe 作为 city 的值。
		std::string name;
		std::string city;
		std::cout << "Input name: ";
		std::cin >> name;
		std::cout << "Input city: ";
		std::cin >> city;
		std::cout << "Output name: " << name << std::endl;
		std::cout << "Output city: " << city << std::endl;
		std::cout << "--------------2-------------" << std::endl;
		
		//为了解决上面这个问题，可以使用一个叫做 getline 的 C++ 函数。
		//此函数可读取整行，包括前导和嵌入的空格，并将其存储在字符串对象中。
		//1、cin.getline()属于istream流，而getline()属于string流，是不一样的两个函数
		//2、当同时使用cin>>,getline()时，需要注意的是，在cin>>输入流完成之后，getline()之前，
		//需要通过添加以下代码:
		#if 0
		std::string receive = "\n";
		getline(std::cin,receive);
		//将回车符作为输入流cin以清除缓存，如果不这样做的话，
		//在控制台上就不会出现getline()的输入提示，而直接跳过，因为程序默认地将之前的变量作为输入流。
		//或者添加以下代码:
		#else
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行
	    #endif
		//输入John Doe再回车输入chicago
		std::string name1;
		std::string city1;
		std::cout << "Input name1: ";
		std::getline(std::cin, name1); //其中 std::cin 是正在读取的输入流，而 name1 是接收输入字符串的 string 变量的名称;
		std::cout << "Input city1: ";
		std::getline(std::cin, city1); //其中 std::cin 是正在读取的输入流，而 city1 是接收输入字符串的 string 变量的名称;
		std::cout << "Output name1 " << name1 << std::endl;
		std::cout << "Output city1 " << city1 << std::endl;
		std::cout << "--------------3-------------" << std::endl;
		
		//1、cin.getline()实际上有三个参数，cin.getline(接收字符串的变量,接收字符个数,结束字符)
		//2、当第三个参数省略时，系统默认为'\0'
		//3、例如调用cin.getline(m,5,'a');当输入jlkjkljkl时输出jklj，输入jkaljkljkl时，输出jk
		//gcount()函数表示返回最后一次cin输出的字符个数，包括字符串结束符'\0';      
		char ch[20];
		std::cout << "Please, enter a word: ";
		std::cin.getline(ch,20);
		std::cout << std::cin.gcount() << " characters read: " << ch << '\n';
		
		return 0;
	}
	

	/********************************************/
	/*
	cin.get
	输入结束条件：Enter键
	对结束符处理：不丢弃缓冲区中的Enter
	*/
	/********************************************/
	int TestGet(void)
	{
		//读取单个字符,直接cin.get(char ch)或ch=cin.get()即可
		//注意： 
		//（1）从结果可以看出，cin.get()从输入缓冲区读取单个字符时不忽略分隔符（空白符），
		//     直接将其读取，就出现了如上情况，将换行符读入变量b，输出时打印两次。
		//（2）cin.get()的返回值是int类型，成功：读取字符的ASCII码值，遇到文件结束符时，返回EOF，即-1，
		//     Windows下标准输入输入文件结束符为Ctrl+z，Linux为Ctrl+d。
        //（3）cin.get(char var)如果成功返回的是cin对象，因此可以支持链式操作，如cin.get(b).get(c)。
		//输入：e[回车]，输出： a:e b:换行符\n
		char a;
		char b;
		a=std::cin.get();
		std::cin.get(b);
		std::cout<<a<<b<<std::endl;
		
		

		return 0;
	}
	
	int TestPeek(void)
	{
		return 0;
	}
	
	int TestPutback(void)
	{
		return 0;
	}
	
	int TestRead(void)
	{
		return 0;
	}
	
	int TestReadsome(void)
	{
		return 0;
	}
	
	int TestSeekg(void)
	{
		return 0;
	}
	
	//此函数测试通过good()、eof()、fail()和bad()等成员函数获取流状态
	int TestStreamStatus(void)
	{
		return 0;
	}

}

int main(void)
{
	//QX::TestGetline();
	QX::TestGet();
	return 0;
}