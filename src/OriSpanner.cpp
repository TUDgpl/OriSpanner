// OriSpanner.cpp : Defines the entry point for the application.
//

#include "OriSpanner.h"
int main()
{
	vector<unsigned int> points{ 1, 2, 3, 4, 5 };
	Arc f(1, 2, 1);
	f.debug(points);
	f.print();
	hello();
}
