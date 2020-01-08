/*
 * ostreamStudy.cpp
 * @time    :2020/01/09 16:59
 * @location:JieShun ShenZhen
 * @Copyright 2020, XiaoQian. All rights reserved.
 * @commit:练习c++标准库中的ostream类

 */
#include<cstring>   // strlen
#include <iostream> // std::cin, std::cout

#include "ostreamStudy.hpp"

namespace QX{
	
	/********************************************/
	/***************ostream重载<<****************/
	/********************************************/
	std::ostream& operator<< (std::ostream& os,const Point& p)//被const修饰的表面为输入型参数
	{
		return os << "x=" << p.m_iX << " "<< "y=" << p.m_iY << std::endl;
		//返回的是一个流,可以直接 cout<<Point
	}
	 
	Point::Point(int x,int y):m_iX(x),m_iY(y)
	{
		std::cout.put(65) << std::endl; //控制台输出ASCII码=65的字符(A)
		std::cout.flush();        //刷新缓冲,无条件地将缓冲区中的输出信息送显示器.
		// std::ends :输出 '\0' 
		// std::flush:冲洗输出流 
		// std::endl :输出 '\n' 并冲洗输出流 
	}
	
	int Point::TestWrite(void)
	{
		const char * state1 = "Beijing";
		const char * state2 = "Shanghai";

		int len1 = strlen(state1);
		int len2 = strlen(state2);
		std::cout << "Increasing loop index:\n";
		int i;
		for (i = 1; i <= len2; i++) 
		std::cout.write(state2, i) << std::endl;//从state2中读取i个字节到显示器

		// concatenate output
		std::cout << "Decreasing loop index:\n";
		for (i = len2; i > 0; i--)
		std::cout.write(state2, i) << std::endl;//从state2中读取i个字节到显示器

		//exceed string length
		std::cout << "Exceeding string length:\n";
		std::cout.write(state1, len1 + 60) << std::endl;
		std::cout.write(state2, len2 + 50) << std::endl;
		
		return 0;
	}
	
}

int main(void)
{
    QX::Point p(2,1);
    std::cout << p; 
	p.TestWrite();
	return 0;
}