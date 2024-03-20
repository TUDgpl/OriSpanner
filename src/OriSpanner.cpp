// OriSpanner.cpp : Defines the entry point for the application.
//
#include "OriSpanner.h"
#include <filesystem>
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
template <typename SolverT>
void solve() {
	SolverT solver = new SolverT() ;
	solver.set();
	solver.solve();
};
/*
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
*/
template <typename Solver_T>
void test_solver(){
	Solver_T S;
	if (Input_file_s.empty()) S.readIPE();
	else S.readFile();
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		S.debug();
		S.output(od);
		//measures.addElement("info", "solver", Algo_t);
		//measures.addElement("performance", "dilation", to_string(od));
		//S.outputMeasures();
		//outputMeasure(".json");
		S.draw();
	}
}

int test(int argc, char* argv[]) {
	parseInitOptions(argc, argv);
	if (Algo_t.compare("dp") == 0)
	{
		test_solver<DP>();
		return 0;
	}
	if (Algo_t.compare("sat") == 0)
	{
		test_solver<Sat2P>();
		return 0;
	}
	if (Algo_t.compare("sat1") == 0)
	{
		test_solver<Sat1P>();
		return 0;
	}
	return -1;
}

int main(int argc, char* argv[]) {
	for (const auto& dirEntry : recursive_directory_iterator(argv[2])) {
		string bina = "./OriSpanner";
		string a_flag = "-a";
		string instance_flag = "-f";
		string arg = dirEntry.path().generic_string();
		if (argv[1] == "sat1") {
			string algo = "sat1";
			char* argv1[] = { bina.data(), a_flag.data(), algo.data(),instance_flag.data(),  arg.data() };
			test(5, argv1);
		}
		else {
			string algo2 = "sat";
			char* argv2[] = { bina.data(), a_flag.data(), algo2.data(),instance_flag.data(),  arg.data() };
			test(5, argv2);
		}
	}
}