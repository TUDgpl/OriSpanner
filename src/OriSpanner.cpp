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
#ifdef __linux__
	std::cout << "run on linux" << std::endl;
#elif _WIN32
	std::cout << "run on windows" << std::endl;
#endif

	parseInitOptions(argc, argv);
	Simple S;
	S.readFile();
	S.print();
	// set solver
	if (true) {
		S.solve();
	}





}
