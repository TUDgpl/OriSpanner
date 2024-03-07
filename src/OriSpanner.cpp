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
	if (Input_file_s.empty()) S.readIPE();
	else S.readFile();
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		S.debug();
		S.output(od);
		measures.addElement("info", "solver", "DP");
		measures.addElement("performance", "dilation", to_string(boost::rational_cast<double>(od)));
		S.outputMeasures();
		outputMeasure("dp.json");
		S.draw();
	}
}

