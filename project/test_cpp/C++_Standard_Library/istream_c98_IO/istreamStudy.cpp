/*
 * istreamStudy.cpp
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

//#include <sstream>
#include <cassert>  //assert函数
#include <limits>   //std::numeric_limits<std::streamsize>::max()
#include <fstream>  //std::ifstream
#include <iostream> // std::cin, std::cout

#include "istreamStudy.hpp"

namespace QX{
	/********************************************/
	/**********测试std::cin的基本功能************/
	/********************************************/
	int TestBaseFunction(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "------TestBaseFunction-----" << std::endl;
		std::cout << "---------------------------" << std::endl;
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max());//当TestBaseFunction放在main函数的首行运行时，运行到此处后不能往下运行！
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//当TestBaseFunction放在main函数的首行运行时，回车后才能往下运行！
		std::cin.clear();//清除状态位
		std::cin.sync(); //清除缓冲区

		char ch1, ch2, ch3;
		int int1, int2, int3, int4;
		
		//键盘输入"12t33[回车]"
		std::cout << "please input '12t33' + [回车] \n";
		std::cin >> ch1; //ch1获取到1，缓冲区还剩2t33[回车]
		std::cout << "ch1=" << ch1 << std::endl;
		std::cin >> ch2; //ch2获取到2，缓冲区还剩t33[回车]
		std::cout << "ch2=" << ch2 << std::endl;
		std::cin >> ch3; //ch3获取到t，缓冲区还剩33[回车]
		std::cout << "ch3=" << ch3 << std::endl;
		std::cin >> int4; //ch4获取到33，缓冲区还剩[回车]
		std::cout << "int4=" << int4 << std::endl;
		
		
		//键盘输入"y[回车]"
		std::cout << "please input 'y' + [回车] \n";
		std::cin >> int1;        //缓冲区数据是y[回车],int1是int类型，所获取失败，状态位good被置位成，程序继续往下运行
		std::cout << "int1=" << int1 << " rdstate() = " << std::cin.rdstate() << std::endl;
		std::cin >> int2;        //缓冲区数据是y[回车],int2是int类型，所获取失败，状态位good被置位成，程序继续往下运行
		std::cout << "int2=" << int2 << " rdstate() = " << std::cin.rdstate() << std::endl;
		while(std::cin.rdstate())//cin.rdstate()!=0时键盘输入的数据格式不对
		{
			std::cout<<"输入类型不是整型或者范围溢出"<<std::endl;
			std::cin.clear();    //清除状态位，使状态位good = std::ios::goodbit。
			// cin.clear()是用来更改cin的状态标示符的，cin在接收到错误的输入的时候，会设置状态位good。
			// 如果good位不为1，则cin不接受输入，直接跳过。如果下次输入前状态位没有改变那么即使清除了缓冲区数据流也无法输入。
			// 所以清除缓冲区之前必须要cin.clear(标识符)。
			//标识符:
			// std::ios::goodbit(0) 无错误
			// std::ios::Eofbit 已到达文件尾
			// std::ios::failbit 非致命的输入/输出错误，可挽回
			// std::ios::badbit(4) 致命的输入/输出错误,无法挽回
			std::cin.sync(); 
			// sync()的作用就是清除输入缓冲区。成功时返回0，失败时badbit会置位，函数返回-1. 
			// 另外，对于绑定了输出的输入流，调用sync()，还会刷新输出缓冲区。 
			// 但由于程序运行时并不总是知道外部输入的进度，很难控制是不是全部清除输入缓冲区的内容。
			// 通常我们有可能只是希望放弃输入缓冲区中的一部分，而不是全部。
			// 比如清除掉当前行、或者清除掉行尾的换行符等等。但要是缓冲区中已经有了下一行的内容，
			// 这部分可能是我们想保留的。这个时候最好不要用sync()。可以考虑用ignore函数代替。 
			// 　 　std::cin.ignore(std::numeric_limits<std::streamsize>::max(),’\n’);//清除输入缓冲区的当前行 
			// 　　 std::cin.ignore(std::numeric_limits<std::streamsize>::max()); //清除输入缓冲区里所有内容 
			//      std::cin.ignore()//清除一个字符
			std::cout << "please input '33' + [回车] \n";
			std::cin >> int3;   //int2获取到33，缓冲区还剩[回车]
			std::cout << "int3=" << int3 << std::endl;
		}
		return 0;
	}
	
	/*******************************************************************************/
	// 虽然可以使用 cin 和 >> 运算符来输入字符串，但它可能会导致一些需要注意的问题。
    // 当 cin 读取数据时，它会传递并忽略任何前导白色空格字符（空格、制表符或换行符）。
	// 一旦它接触到第一个非空格字符即开始阅读，当它读取到下一个空白字符时，它将停止读取。
	// 以下面的语句为例：
	// cin >> namel;
	// 可以输入 "Mark" 或 "Twain"，但不能输入 "Mark Twain"，
	// 因为 cin 不能输入包含嵌入空格的字符串。下面程序演示了这个问题：
	/*******************************************************************************/
	int TestGetline(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "--------Test getline-------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行,避免受到上个函数的干扰
		
		//（1）cin>>等价于cin.operator>>()，即调用成员函数operator>>()进行读取数据。 
		//（2）当cin>>从缓冲区中读取数据时，若缓冲区中第一个字符是空格、tab或换行这些分隔符时，cin>>会将其忽略并清除，
		//     继续读取下一个字符，若缓冲区为空，则继续等待。但是如果读取成功，字符后面的分隔符是残留在缓冲区的，cin>>不做处理。 
		//（3）不想略过空白字符，那就使用 noskipws 流控制。比如cin>>noskipws>>input;
		char a;
		int b;
		float c;
		std::string str;
		std::string test;
		std::cout << "please input [回车][回车][回车]a[回车]5[回车]2.33[回车]hello[回车] \n";
		std::cin>>a>>b>>c>>str;
		getline(std::cin,test); //读取到[回车]后继续往下运行
		std::cout<<"char_a=" <<a <<" int_b="<<b<<" float_c="<<c<<" str="<<str<<" test="<<test<<std::endl;
		//从结果可以看出，cin>>对缓冲区中的第一个换行符视而不见，采取的措施是忽略清除，继续阻塞等待缓冲区有效数据的到来。
		//但是，getline()读取数据时，并非像cin>>那样忽略第一个换行符，getline()发现cin的缓冲区中有一个残留的换行符，
		//不阻塞请求键盘输入，直接读取，送入目标字符串后，再将换行符替换为空字符’\0’，因此程序中的test为空串。
		std::cout << "--------------1-------------" << std::endl;
		
		//以下这段代码运行后，用户根本没有机会输入 city 城市名。
		//因为在第一个输入语句中，当 cin 读取到 John 和 Doe 之间的空格时，
		//它就会停止阅读，只存储John 作为name 的值。在第二个输入语句中， 
		//cin使用键盘缓冲区中找到的剩余字符，并存储 Doe 作为 city 的值。
		//输入John Doe再回车输入beijing---//
		std::string name;
		std::string city;
		std::cout << "please input 'John Doe' + [回车] \n";
		std::cin >> name;       //name获取到“John”
		std::cout << "并未在此处停留等待输入city \n";
		std::cin >> city;       //city获取到“Doe”
		std::cout << "name=" << name << " city=" << city << std::endl;
		std::cout << "--------------2-------------" << std::endl;
		//上一段代码运行完后，缓冲区中还剩下一个[回车]字符，可以使用一个叫做getline的函数。
		//此函数可读取整行，包括前导和嵌入的空格，并将其存储在字符串对象中。
		//cin.getline()属于istream流，而getline()属于string流，是不一样的两个函数
		#if 0
		std::string receive = "\n";
		getline(std::cin,receive);                                        //清除残留在输入缓冲区中的[回车]
		#else                                                             //以下代码也能清除缓冲区中的[回车]
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行
	    #endif
		//输入John Doe再回车再输入chicago
		std::string name1;
		std::string city1;
		std::cout << "please input 'John Doe' + [回车] \n";
		std::getline(std::cin, name1); //name1获取到;'John Doe'
		std::cout << "please input 'chicago' + [回车] \n";
		std::getline(std::cin, city1); //city1获取到;'chicago'
		std::cout << "name1=" << name1 << " city1=" << city1 << std::endl;
		std::cout << "--------------3-------------" << std::endl;
		
		//1、cin.getline()实际上有三个参数，cin.getline(接收字符串的变量,接收字符个数,结束字符)
		//2、当第三个参数省略时，系统默认该字符为回车换行符'\n'。
		//3、例如调用cin.getline(m,5,'a');当输入jlkjkljkl时输出jklj，输入jkaljkljkl时，输出jk
		//4、会在读取的字符串后面自动加上'\0'
		//gcount()函数表示返回最后一次cin输出的字符个数，包括字符串结束符'\0';      
		char ch[20];
		std::cout << "Please, enter a word: ";
		std::cin.getline(ch,20);
		std::cout << "gcount()=" << std::cin.gcount() << " ch=" << ch << '\n';
		
		return 0;
	}
	
	/********************************************/
	// cin.get
	// 输入结束条件：Enter键
	// 对结束符处理：不丢弃缓冲区中的Enter
	/********************************************/
	int TestGet(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "---------Test get----------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cout << " rdstate222() = " << std::cin.rdstate() << std::endl;
		
		//----------------------------------------清空缓冲区--------------------------------------//
		std::cin.clear();//清除状态位
		std::cin.sync(); //清除缓冲区
		
		// 如此清除输入缓冲区，如果缓冲区无数据，则要敲击[回车]，程序才会往下走
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行,避免受到上个函数的干扰
		
		// 如此清除输入缓冲区，如果缓冲区无数据，输入状态将被置成致命的输入:std::ios::badbit(4)
		// char clearBuf[4096];
		// std::cin.get(clearBuf,4096).get();//清除输入缓冲区,避免受到上个函数的干扰
		// std::cout << " rdstate() = " << std::cin.rdstate() << std::endl;
		//----------------------------------------清空缓冲区--------------------------------------//
		
		//1、读取单个字符: 
		//int get();              --- ch=cin.get()
        //istream& get (char& c); --- cin.get(char ch)
		//（1）cin.get()从输入缓冲区读取单个字符时不忽略分隔符（空格、制表符或换行符），直接将其读取。
		//（2）cin.get()的返回值是int类型，成功：读取字符的ASCII码值，遇到文件结束符时，返回EOF，即-1，
		//     Windows下标准输入文件结束符为Ctrl+z，Linux为Ctrl+d。
        //（3）cin.get(char var)如果成功返回的是cin对象，因此可以支持链式操作，如cin.get(b).get(c)。
		char a;
		char b;
		//输入：e[回车]，输出：a:e b:换行符\n
		std::cout << "please input 'e' + [回车] \n";
		a=std::cin.get();
		std::cin.get(b);
		std::cout<<a<<b<<std::endl;
		std::cout << "--------------1-------------" << std::endl;
		
		//2.1、读取多个字符
		//1)istream& get (char* s, streamsize n);
		//  从cin或者istream中提取c风格的字符串，最大字符串长度为n，最后一个字符为‘\0’字符串结束字符：
		    // char c[20];            --正确
		    // char* c= new char[20]; --正确
		    // char* c;               --错误，没开辟内存不能作为get函数的参数
		    // cin.get(c,20);
		//2)istream& get (char* s, streamsize n, char delim);
		//  delim为定界字符(delimiting characters),其默认值应该是'\n'(换行字符),如果人为定义的话可以是任意定义的字符
		//  例如：cin.get(c,20,'a');  
		//  当遇到a字符时，只取a字符前的字符串部分输出给c字符串，此时，a字符并不从cin输入缓冲区提取，留给后来的变量提取，而getline则直接丢弃该字符!;
		char ch='a',c[20];
		//输入：1[空格]23[回车]，输出:c=1 23 ch=10
        std::cout << "please input 1[空格]23[回车] \n";		
		std::cin.get(c,5); //遇到换行符时结束读取，但是不对换行符进行处理，换行符仍然残留在输入缓冲区。
		std::cin.get(ch);  //将换行符读入变量ch，换行符(\n)的ASCII码值为10。
		std::cout<<"c=" << c << " ch="<<(int)ch << std::endl;
		std::cout << "--------------2-------------" << std::endl;
		// 2.2、cin.get(char_type* s, streamsize cnt,char_type delim)与cin.getline(char_type* s, streamsize cnt,char_type delim)的区别
		// 1)cin.get()当输入的字符串超过规定长度时，不会引起cin函数的错误，后面的cin操作会继续执行，只是直接从缓冲区中取数据。
          // 但是cin.getline()当输入超过规定长度时，会引起cin函数的错误，后面的cin操作将不再执行。
			// 当输入的字符数大于cnt时，则get函数只读取cnt-1个字符，而其余的字符仍然保存在缓冲区中，还可再对其进行读取；
			// 但是函数getline则不然，getline()会设置失效位(faibit)，并且关闭后面的输入，这个时候再用ch=cin.get()是读取不到留在输入队列中的字符的。
			// 可以用下面的命令来恢复输入：
			// cin.clear()；//因为clear()会重置失效位，打开输入。这个时候ch=cin.get();就可以读取留在输入队列中的字符。
		// 2)cin.get读取一行时，遇到换行符(自定义结束符)时结束读取，但是不对换行符(自定义结束符)进行处理，换行符(自定义结束符)仍然残留在输入缓冲区。
	     // getline读取一行字符时，默认遇到’\n’(自定义结束符)时终止，并且将’\n’(自定义结束符)直接从输入缓冲区中删除掉，不会影响下面的输入处理。
         // 两者都会在读取的字符串后面自动加上'\0'
		// 3)cin.get(str,size);读取一行时，只能将字符串读入C风格的字符串中，即char*，
		  // 但是C++的getline函数还可以将字符串读入C++风格的字符串中，即string类型。（string test; getline(cin,test);）
		// 4)当输入缓冲区只有[回车]字符时，调用cin.get(char_type* s, streamsize cnt)，状态位good将会被置位为致命的输入:std::ios::badbit(4)
        // 鉴于getline较cin.get()的优点，建议使用getline进行行的读取。
		
		//3、读取字符到buf
		//1)istream& get (streambuf& sb);
		//2)istream& get (streambuf& sb, char delim);

		return 0;
	}
	
	/************************************************************************************************/
	// 偷看下一个字符而不从输入流提取；其返回值是一个char型的字符，其返回值是指针指向的当前字符，
	// 但它只是观测，指针仍停留在当前位置，并不后移。如果要访问的字符是文件结束符，则函数值是EOF（-1）
	// 若把输入流比作一个栈类,那么peek函数就相当于栈的成员函数front,而cin.get()则相当于栈的成员函数pop。
	/************************************************************************************************/
	int TestPeek(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "---------Test peek---------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行,避免受到上个函数的干扰,当缓冲区无数据时会阻塞程序往下执行
		
		char c;
		int n;
		char str[256];
		std::cout << "Enter a number or a word:";
		c=std::cin.peek(); //偷看下一个字符而不从输入流提取
		std::cout<<"cin.peek()= "<<c;
		if ( (c >= '0') && (c <= '9') )
		{	
			std::cin >> n;
			std::cout << " number=" << n << std::endl;
		}
		else
		{
			std::cin >> str;
			std::cout << " word=" << str << std::endl;
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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行,避免受到上个函数的干扰
		
		char ch, ch1;
		int n;
		//输入"y55x[回车]"
		std::cout << "please input 'y55x' + [回车] \n";  
		std::cin.get(ch);     //ch获取到y，缓冲区还剩55x[回车]
		std::cin >> n;        //n获取到55，缓冲区还剩x[回车]
		std::cout << "ch=" << ch << " n=" << n << std::endl;  
		std::cin.get(ch1);    //ch获取到y，缓冲区还剩[回车]
		std::cin.putback(ch1);//退回一个字符到缓冲区，缓冲区还剩x[回车]
		std::cin >> n;        //由于"x"是char型的，所的(int)n从缓冲区获取失败，程序接着往下运行
		std::cout << "ch1=" << ch1 <<" n=" << n << std::endl;

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
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//清除输入缓冲区的当前行,避免受到上个函数的干扰
		
		const int LEN = 64; 
		char chars[ LEN + 1 ] = {0};
		std::ifstream in("./istreamStudy.cpp", std::ios_base::in | std::ios_base::binary); 
		
		in.read(chars, LEN );    //从文件设备读取LEN长度个字节到chars[]数组内
		std::cout << chars << std::endl;
		in.readsome(chars, LEN );//readsome()只能从缓冲区获取数据,所以用获取不到任何数据
		std::cout << chars << std::endl;
		return 0;
		// 而有时候想要从设备读取指定长度的数据,但又要知道实际读取的长度,这时候就要用另一个方法:std::cin.gcount()
		// 它返回自上次读取以来所读取的字节数,因此可以这样得到实际读取的长度.
		// int count = 0;
		// in.read( chars, LEN );
		// count = in.gcount();
		// cout << "Read in " << count << " chars : " << chars << endl;
		// 实际上,readsome()也是调用read()和gcount()来实现的.
	}
	
	/****************************************************************************
	(1)	istream& seekg (streampos pos);
        指向输入流位置为pos的地方
    (2)	istream& seekg (streamoff off, ios_base::seekdir way);
		第一个参数是偏移量，第二个参数是基地址。
		对于第一个参数，可以是正负数值，正的表示向后偏移，负的表示向前偏移。
		第二个参数可以是：
					ios：：beg：表示输入流的开始位置
					ios：：cur：表示输入流的当前位置
					ios：：end：表示输入流的结束位置
	****************************************************************************/
	int TestSeekg(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "------Test read seekg------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cin.clear();//清除状态位
		std::cin.sync(); //清除缓冲区
		
		std::ifstream is ("./istreamStudy.hpp", std::ifstream::binary);
		if (is) 
		{
		// get length of file:
		is.seekg (0, is.end); 
		int length = is.tellg();
		is.seekg (0, is.beg);

		char * buffer = new char [length];// allocate memory: 
		is.read (buffer,length);          // read data as a block:						  
		is.close();                       					  
		std::cout.write(buffer,length);  // print content:
		delete[] buffer;
		}
		std::cout << "--------------1-------------" << std::endl;
		
		std::ifstream in("istreamStudy.hpp");
		assert(in);
		in.seekg(0,std::ios::end);       //基地址为文件结束处，偏移地址为0，于是指针定位在文件结束处
		std::streampos sp=in.tellg();    //sp为定位指针，因为它在文件结束处，所以也就是文件的大小
		std::cout<<"file size:" << sp << std::endl;
		in.seekg(-sp/3,std::ios::end);   //基地址为文件末，偏移地址为负，于是向前移动sp/3个字节
		std::streampos sp2=in.tellg();   //sp2为30
		std::cout<<"from file to point:" << sp2 << std::endl;
		in.seekg(0,std::ios::beg);       //基地址为文件头，偏移量为0，于是定位在文件头
		std::cout<<in.rdbuf()<<std::endl;//从头读出文件内容
		in.seekg(sp2);                   //这里sp2是绝对位置，与前面的偏移计算无关
		std::cout<<in.rdbuf()<<std::endl;//从sp2开始读出文件内容
		in.close();
		
		return 0;
	}
	
	//测试通过good()、eof()、fail()和bad()等成员函数获取流状态
	int TestStreamStatus(void)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "------Test read seekg------" << std::endl;
		std::cout << "---------------------------" << std::endl;
		std::cin.clear();//清除状态位
		std::cin.sync(); //清除缓冲区
		
		int i;
		while(1)
		{
			std::cout << "请依次输入:’a’[回车];5[回车] 查看效果" << std::endl;
			std::cin >> i;
			bool good = std::cin.good(); //goodbit位表示一切正常，没有错误发生，也没有发生输入结束。
			bool bad  = std::cin.bad();  //badbit位表示了在流缓冲区中发生了致命性错误，流将不能继续使用
			bool fail = std::cin.fail(); //failbit位表示I/O操作由于非法数据而失败，流可以继续使用
			bool eof  = std::cin.eof();  //eofbit位表示输入结束，例如按下了Ctrl-Z
		    std::cout << "i=" << i << " goodbit=" << good << " badbit=" << bad << " failbit=" << fail << " eofbit=" << eof <<std::endl;
			if(good)
				break;
			std::cin.clear(); //清空标志位
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //跳过流中格式不正确的数据
		}
		return 0;
	}
	
}

int main(void)
{
	QX::TestBaseFunction();
	QX::TestGetline();
	QX::TestGet();
	QX::TestPeek();
	QX::TestPutback();
	QX::TestRead_Readsome();
	QX::TestSeekg();
	QX::TestStreamStatus();
	return 0;
}