#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
	printf("hello world");
	//---以下三个函数都能实现暂停功能---//
	getchar();           //头文件stdio.h
	//system("pause");   //头文件stdlib.h
	//Sleep(2000);       //头文件windows.h  linux下是sleep(2000)
	return 0;
}