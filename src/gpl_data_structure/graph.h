#pragma once
using namespace std;
#include "miscellaneous.h"
class Arc {
public:
	Arc(unsigned int source, unsigned int target, unsigned int length) {
		s = source;
		t = target;
		l = length;
	}
	void print();
	void debug(vector<unsigned int>& points);
protected:
	unsigned s;
	unsigned t;
	unsigned l;
};

class point_set_1D {
public:
	point_set_1D(){};
	void set();
	void print();
	void debug(vector<unsigned int>& points);
protected:
	vector<unsigned int> points;


};