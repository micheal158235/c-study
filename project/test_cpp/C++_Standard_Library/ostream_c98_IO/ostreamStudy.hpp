#ifndef _OSTREAMSTUDY_H
#define _OSTREAMSTUDY_H

#include <ostream>

namespace QX{
	int TestBaseFunction(void);
	class Point
	{
	public:
		friend std::ostream& operator<< (std::ostream& os,const Point& p);
		Point(int x,int y);
		int TestWrite(void);
	private:
		int m_iX;
		int m_iY;
	};

}

#endif