#pragma once
using namespace std;
#include <cmath>
#include "solver.h"
#include "miscellaneous.h"
#include <list>
#include "dgraph.h"
#include <set>


class Solver_1D:public Solver {
public:
	Solver_1D() {};
	void set(size_t point_size);
	virtual void say_hello() { printf("Run Solver_1D"); };
	void read_point(char* str);
	void print();
	void debug();
	void output(const char* outFile, double od);
protected:
	vector<double> pVector;
	// (p_i, p_i+1) path not included
	DGraph solution_g;
	bool isPlanarity();
private:
};