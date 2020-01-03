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
#include <fstream>
#include <sstream>
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
		
		//---输入John Doe再回车输入beijing---//
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
		//2、当第三个参数省略时，系统默认该字符为回车换行符'\n'。
		//3、例如调用cin.getline(m,5,'a');当输入jlkjkljkl时输出jklj，输入jkaljkljkl时，输出jk
		//4、会在读取的字符串后面自动加上'\0'
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
		std::cout << "---------------------------" << std::endl;
		std::cout << "--------Test get-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		//1、读取单个字符: 
		//int get();              --- ch=cin.get()
        //istream& get (char& c); --- cin.get(char ch)
		//注意： 
		//（1）cin.get()从输入缓冲区读取单个字符时不忽略分隔符（空格、制表符或换行符），直接将其读取。
		//（2）cin.get()的返回值是int类型，成功：读取字符的ASCII码值，遇到文件结束符时，返回EOF，即-1，
		//     Windows下标准输入文件结束符为Ctrl+z，Linux为Ctrl+d。
        //（3）cin.get(char var)如果成功返回的是cin对象，因此可以支持链式操作，如cin.get(b).get(c)。
		char a;
		char b;
		a=std::cin.get();
		std::cin.get(b);
		std::cout<<a<<b<<std::endl;
		//输入：e[回车]，输出： a:e b:换行符\n
		std::cout << "--------------1-------------" << std::endl;
		
		//2、读取多个字符
		//1)istream& get (char* s, streamsize n);
		//  从cin或者istream中提取c风格的字符串，最大字符串长度为n，最后一个字符为‘\0’字符串结束字符：
		/*  char c[20];            --正确
		 *  char* c= new char[20]; --正确
		 *  char* c;               --错误，没开辟内存不能作为get函数的参数
		 *  cin.get(c,20);
		 */
		//2)istream& get (char* s, streamsize n, char delim);
		//  delim为定界字符(delimiting characters),其默认值应该是'\n'(换行字符),如果人为定义的话可以是任意定义的字符
		//  例如：cin.get(c,20,'a');  
		//  当遇到a字符时，只取a字符前的字符串部分输出给c字符串，此时，a字符并不从cin输入缓冲区提取，留给后来的变量提取，而getline则直接丢弃该字符!;
		char ch='a',c[20];
		std::cin.get(c,5);
		std::cin.get(ch);
		std::cout<<c<<"--"<<(int)ch<<std::endl;
		//输入：1[空格]23[回车]，输出:1 23--10 
		//遇到换行符时结束读取，但是不对换行符进行处理，换行符仍然残留在输入缓冲区。
		//第二次由cin.get()将换行符读入变量ch，打印输入换行符的ASCII码值为10。
		std::cout << "--------------2-------------" << std::endl;
		
		//3、读取字符到buf
		//1)istream& get (streambuf& sb);
		//2)istream& get (streambuf& sb, char delim);

		return 0;
	}
	
	/********************************************/
	/*偷看下一个字符而不从输入流提取；          */
	/********************************************/
	int TestPeek(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "--------Test peek-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		//cin.peek() 其返回值是一个char型的字符，其返回值是指针指向的当前字符，但它只是观测，指针仍停留在当前位置，并不后移。如果要访问的字符是文件结束符，则函数值是EOF（-1）。
		//若把输入流比作一个 栈类 那么这里的peek函数就相当于栈的成员函数front 而如果cin.get()则相当于栈的成员函数pop。
		char c;
		int n;
		char str[256];
		std::cout << "Enter a number or a word: ";
		c=std::cin.peek(); //偷看下一个字符而不从输入流提取
		std::cout<<"cin.peek()= "<<c;
		if ( (c >= '0') && (c <= '9') )
		{	
			std::cin >> n;
			std::cout << "You have entered number " << n << std::endl;
		}
		else
		{
			std::cin >> str;
			std::cout << " You have entered word " << str << std::endl;
		}
		
		return 0;
	}
	
	/********************************************/
	/*istream& putback (char c); //将c放入输入流*/
	/********************************************/
	int TestPutback(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "--------Test putback-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		char ch;
		int n;
		// char c=std::cin.peek(); //偷看下一个字符而不从输入流提取
		// std::cout<<"cin.peek()= "<<(int)c;
		// c=std::cin.peek(); //偷看下一个字符而不从输入流提取
		// std::cout<<"cin.peek()= "<<(int)c;
		
		std::cout << "input an integer:";
		std::cin.get(ch);
		std::cin >> n;
		std::cout << "ch=" << ch << std::endl;
		std::cout << "n=" << n << std::endl;
		std::cin.ignore(1000, '\n');
		std::cout << "input an integer:";
        
		std::cin.get(ch);
		std::cin.putback(ch);	//退回 一个字符
		std::cin >> n;
		std::cout << "ch=" << ch << std::endl;
		std::cout << "n=" << n << std::endl;

		return 0;
	}
	
	/****************************************************************************/
	/*read()方法从缓冲区或设备读取指定长度的字节数,返回对自身的引用.            */
    /*而readsome()方法只能从缓冲区中读取指定长度字节数,并返回实际已读取的字节数.*/
	/****************************************************************************/
	int TestRead_Readsome(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "----Test read readsome-----" << std::endl;
		std::cout << "---------------------------" << std::endl;
		const int LEN = 4096;
		
		char chars[ LEN + 1 ] = {0};
		std::ifstream in("./istreamStudy.exe", std::ios_base::in | std::ios_base::binary); 
		
		in.read( chars, LEN );   //将文件从设备载入缓冲区,并读取LEN长度
		std::cout << chars << std::endl;
		
		in.readsome( chars, LEN );//就可以从缓冲区中读取.在缓冲区中没有数据时,用readsome()得不到任何数据.
		std::cout << chars << std::endl;
		return 0;
		
		// 而有时候想要从设备读取指定长度的数据,但又要知道实际读取的长度,这时候就要用另一个方法: gcount()
		// 它返回自上次读取以来所读取的字节数,因此可以这样得到实际读取的长度.
		// int count = 0;
		// in.read( chars, LEN );
		// count = in.gcount();
		// cout << "Read in " << count << " chars : " << chars << endl;
		// 实际上,readsome()也是调用read()和gcount()来实现的.
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
	//QX::TestGet();
	//QX::TestPeek();
	QX::TestPutback();
	QX::TestRead_Readsome();
	return 0;
}