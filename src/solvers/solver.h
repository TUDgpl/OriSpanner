#pragma once
using namespace std;
#include "miscellaneous.h"

class Solver {
public:
	Solver() {};
	virtual void say_hello(){ printf("Run Solver"); };
	virtual void set(size_t s) {};
	virtual void print();
	virtual void debug();
	virtual void readFile();
	virtual void read_point(char* str) = 0;
	virtual void solve() = 0;
protected:
	virtual bool check_planarity() { return false; };
};