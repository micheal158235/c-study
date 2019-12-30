/*
 * iomanipStudy.hpp
 * @time    :2019/12/30 17:42
 * @location:JieShun ShenZhen
 * @Copyright 2019, XiaoQian. All rights reserved.
 * @commit:练习c++标准库中的iomanip类
 */
 
 /*------------------------------------------------------------------------------------------------
iomanip是指IO Manipulators，意思是输入输出操纵器。

iomanip中包含如下函数：

1、setiosflags：
setiosflags(ios::fixed) 固定的浮点显示，与setprecision(n)合用，可以控制小数点右边的数字的个数。
setiosflags(ios::scientific) 用指数表示小数
setiosflags(ios::left) 左对齐
setiosflags(ios::right)右对齐
setiosflags(ios::skipws) 忽略前导空白
setiosflags(ios::uppercase) 16进制数大写输出
setiosflags(ios::lowercase) 16进制小写输出
setiosflags(ios::showpoint) 强制显示小数点
setiosflags(ios::showpos) 强制显示符号
setiosflags(ios::showbase)显示输出的进制
2、setw(n)
 预设输出的文字的宽度。n是在输出时分配了n个字符的输出宽度，然后默认的是在n个字符宽度中右对齐输出。
3、setfill(char c)
在预设宽度中没有用完的部分填充进字符‘c’。可以和setw()函数一同使用。
4、setbase(int n) 
将输出的数据转换为n进制。
5、 setprecision(n)
控制输出流显示浮点数的数字个数，C++中默认的输出数值有效位是6位。
-----------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>
#include <fstream>

#include "iomanipStudy.hpp"

namespace QX{
	
	int TestIOManipFunction(void)
	{
		// 前缀0表示八进制 前缀0x表示十六进制 不带前缀表示十进制
		int a = 123;
		double pi = 22.0/7.0;

		// setbase(n) 设置整数为n进制(n=8,10,16)
		// oct 八进制 dec 十进制 hex 十六进制
		// setiosflags(ios::showbase) 显示进制的前缀
		// 数值默认十进制显示输出
		std::cout << a << std::endl;
		std::cout << "oct: " << std::showbase << std::setbase(8) << a << " " << std::oct << a << std::endl;
		std::cout << "dec: " << std::showbase << std::setbase(10) << a << " " << std::dec << a << std::endl;
		std::cout << "hex: " << std::showbase << std::setbase(16) << a << " " << std::hex << a << std::endl;

		// setprecision(n) 设置浮点数的有效数字为n位
		// 有效位数默认是6位，即setprecision(6)，即小数点前面和小数点后面加起来的位数为6个有效数字（注意会四舍五入）
		std::cout << pi << std::endl;
		std::cout << std::setprecision(12) << pi << std::endl;

		// setfill(n) 设置字符填充，c可以是字符常或字符变量
		// setw(n) 设置字段宽度为n位, 若是实际宽度大于被设置的，则setw函数此时失效, 只针对其后的第一个输出项有效
		// setiosflags(ios::left) 输出左对齐
		// setiosflags(ios::right) 输出右对齐 默认右对齐
		std::cout << std::setfill('*') << std::setw(20) << std::setprecision(12) << pi << std::endl;
		std::cout << std::setfill('*') << std::setw(20) << std::setprecision(12) << std::right << pi << std::endl;
		std::cout << std::setfill('*') << std::setw(20) << std::setprecision(12) << std::left << pi << std::endl;

		// setiosflags(ios::fixed) 设置浮点数以固定的小数位数显示
		std::cout << std::fixed << std::setprecision(12) << pi << std::endl;

		// setiosflags(ios::scientific)  设置浮点数以科学计数法表示 科学计数法输出E与十六进制输出默认是以小写的，要换成大写需添加uppercase
		std::cout << std::scientific << std::setprecision(12) << pi << std::endl;
		std::cout << std::scientific << std::uppercase << std::setprecision(12) << pi << std::endl;

		// resetiosflags() 终止已经设置的输出格式状态，在括号中应指定内容
		std::cout << std::setiosflags(std::ios::scientific) << std::setprecision(12) << pi << "   " << std::resetiosflags(std::ios::scientific) << pi << std::endl;

		system("pause");
		return 0;
	}

}

int main(void)
{
	QX::TestIOManipFunction();
	return 0;
}