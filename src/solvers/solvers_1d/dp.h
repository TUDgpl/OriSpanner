#pragma once
#include "solver.h"
#include "solver1D.h"
class DP :public Solver_1D {
public:
	void say_hello() { printf("Run DP"); };

	double solve();
private:
	//initialize OE
	//vector < vector<vector<vector<DGraph>>>> oE;
	vector < vector<vector<vector<bool>>>> valid;
	vector < vector<vector<vector<tuple<int, int,int>>>>> back_tracing;
	vector < vector<vector<vector<double>>>> odV;
	void back_trace(int l, int lp, int rp, int r);
};