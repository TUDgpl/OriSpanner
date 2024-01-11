#pragma once
using namespace std;
#include "miscellaneous.h"

class Solver {
public:
	Solver() {};
	virtual void say_hello(){ printf("Run Solver"); };
	virtual void set(int point_size) {};
	virtual void print() = 0;
	virtual void debug() = 0;
	virtual void readFile();
	virtual void read_point(char* str) = 0;
	virtual RationalNumber solve() { return -1; };
	virtual void output(RationalNumber od)=0;
	virtual void draw() = 0;
	virtual bool is_planarity() = 0;
	// theoretical guarantee
protected:
	double teo_g = 5;

};
