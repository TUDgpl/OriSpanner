// OriSpanner.cpp : Defines the entry point for the application.
//
#pragma once
#include "OriSpanner.h"

template <typename SolverT>
void solve() {
	SolverT solver = new SolverT() ;
	solver.set();
	solver.solve();
};

int main(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	Sat1P S;
	S.readFile();
	//S.print();
	// set solver
	if (true) {
		double od = S.solve();
		S.output(od);
		S.draw();
	}
}

