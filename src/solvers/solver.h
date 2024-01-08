#pragma once
using namespace std;
#include "miscellaneous.h"

class Solver {
public:
	Solver() {};
	virtual void say_hello(){ printf("Run Solver"); };
	virtual void set(size_t s) {};
	virtual void print() = 0;
	virtual void debug() = 0;
	virtual void readFile();
	virtual void read_point(char* str) = 0;
	virtual double solve() { return -1; };
	virtual void output(double od)=0;
	virtual void draw() = 0;
	virtual bool isPlanarity() { return false; };
	// theoretical guarantee
protected:
	double teo_g = 5;

};
