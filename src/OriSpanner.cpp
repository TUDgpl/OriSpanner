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
	DP S;
	S.readFile();
	S.print();
	// set solver
	if (true) {
		double od = S.solve();
		char file_str[400];
		strcpy(file_str, Result_folder_s.c_str());
		strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
		strcat(file_str, Algo_t.c_str());
		strcat(file_str, ".txt");
		printf(file_str);
		S.output(file_str,od);
	}

}
/*
int main(int argc, char* argv[]) {
	DGraph graph(3);
	graph.addEdge(0, 2);
	graph.addEdge(1, 2);
	graph.print();
	graph.debug();
	cout << endl;
	return 0;
}
*/