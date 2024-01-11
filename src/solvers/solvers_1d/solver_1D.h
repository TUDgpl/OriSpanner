#pragma once
using namespace std;
#include <cmath>
#include "solver.h"
#include "miscellaneous.h"
#include <set>
#include "dgraph.h"

class Solver_1D :public Solver {
public:
	Solver_1D() {};
	virtual void set(size_t point_size);
	virtual void say_hello() { printf("Run Solver_1D1P"); };
	void read_point(char* str);
	void output(RationalNumber od) override;
	void print() override;
	void draw() override;
	void debug() override;
	virtual bool is_planarity() = 0;
	vector<RationalNumber> pVector;
	DGraph solution;
	RationalNumber teo_g = 5;
	virtual void draw_tikz(double range, std::string path, std::string optional_parameters) = 0;
};