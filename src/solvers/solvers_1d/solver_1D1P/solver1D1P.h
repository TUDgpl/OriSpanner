#pragma once
using namespace std;
#include <cmath>
#include "solver_1D.h"
#include "miscellaneous.h"
#include <list>
#include "dgraph.h"
#include <set>


class Solver_1D1P:public Solver_1D{
public:
	Solver_1D1P() {};
	void set(size_t point_size);
	virtual void say_hello() { printf("Run Solver_1D1P"); };
	void print();
	void debug();
	void output(double od);
	void draw();
protected:
	vector<double> pVector;
	// (p_i, p_i+1) path not included
	DGraph solution_g;
	bool isPlanarity();
private:
};