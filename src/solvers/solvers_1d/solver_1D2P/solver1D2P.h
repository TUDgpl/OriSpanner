#pragma once
using namespace std;
#include <cmath>
#include "solver_1D.h"
#include "miscellaneous.h"
#include <list>
#include "dgraph.h"
#include <set>


class Solver_1D2P :public Solver_1D {
public:
	Solver_1D2P() {};
	virtual void say_hello() { printf("Run Solver_1D2P"); };
	void print() override;
	void debug() override;
	void draw() override;
	bool is_planarity() override;

private:
};