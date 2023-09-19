#pragma once
using namespace std;
#include <cmath>
#include "solver.h"
#include "miscellaneous.h"
#include <list>
struct Arc_1D{
	Arc_1D() { s = 0;  t = 0; l = 0; };
	Arc_1D(unsigned int source, unsigned int target, int len) {
		s = source;
		t = target;
		l = len;
	}
	void print() const;
	void debug(vector<unsigned int>& points);

	unsigned s;
	unsigned t;
	unsigned l;
};

bool find_cross(const Arc_1D& a1, const Arc_1D& a2);


class Solver_1D:public Solver {
public:
	Solver_1D() {};
	void set(size_t point_size);
	virtual void say_hello() { printf("Run Solver_1D"); };
	void read_point(char* str);
	void print();
	void debug(vector<unsigned int>& points);
protected:
	vector<unsigned int> pVector;
	list<Arc_1D> solution;
	bool check_planarity();
};