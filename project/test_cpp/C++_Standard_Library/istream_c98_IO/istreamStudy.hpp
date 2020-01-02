#ifndef _ISTREAMSTUDY_H
#define _ISTREAMSTUDY_H

namespace QX{
	
	int TestGetline(void);
	int TestGet(void);
	int TestPeek(void);
	int TestPutback(void);
	int TestRead(void);
	int TestReadsome(void);
	int TestSeekg(void);
	int TestStreamStatus(void);//此函数测试通过good()、eof()、fail()和bad()等成员函数获取流状态
	
}

#endif