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
	Sat2P S;
	S.readFile();
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		S.debug();
		S.output(od);
		S.draw();
	}
}
/*
// long edge conjecture test 
int main(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	Sat2P S;
	S.readFile();
	RationalNumber best(2, 1);
	RationalNumber best_short(2, 1);
	int test_len = 4;
	// only using edge length < test_len  
	bool conter_found = S.conjecture_check(best, best_short,test_len);
	if (conter_found) {
		printf("counterexample for edge length limit %i ,(%f, %f)", test_len, boost::rational_cast<double>(best), boost::rational_cast<double>(best_short));
	}
	else {
		assert(best == best_short);
		printf("%f, SHORT", boost::rational_cast<double>(best));
	}
}
*/
