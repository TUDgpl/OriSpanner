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
RationalNumber test_solver(){
	Solver_T S;
	if (!Input_file_s.empty()) {
		S.readFile();
	}
	if (!input_ipe_s.empty()) {
		S.readIPE();
	}
	else {
		if (generation_mode) {
			S.generate_instance();
		}
	}
	//S.print();
	// set solver
	if (true) {
		RationalNumber od = S.solve();
		//S.debug();
		//S.output(od);
		return od;
		//measures.addElement("info", "solver", Algo_t);
		//measures.addElement("performance", "dilation", to_string(od));
		//S.outputMeasures();
		//outputMeasure(".json");
		//S.draw();
	}
}

RationalNumber test(int argc,  char* argv[]) {
	//parseInitOptions(argc, argv);
	if (Algo_t.compare("dp") == 0)
	{
		return test_solver<DP>();
	}
	if (Algo_t.compare("sat") == 0)
	{
		return test_solver<Sat2P>();
	}
	if (Algo_t.compare("sat1") == 0)
	{
		return test_solver<Sat1P>();
	}
	cerr << " Error: "<<Algo_t << " can not be recognized " << endl;
	exit(1);
}

void  batch_folder_solver(int argc, char* argv[]) {
	for (const auto& dirEntry : recursive_directory_iterator(argv[2])) {
		string bina = "./OriSpanner";
		string a_flag = "-a";
		string instance_flag = "-f";
		string arg = dirEntry.path().generic_string();
		if (strcmp(argv[1],"sat1") == 0) {
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

int main(int argc, char* argv[]) {
	//generate 
	vector<RationalNumber> pVector_max_global;
	instance_size = std::stoi(argv[argc-1]);
	generate_point_size = std::stoi(argv[argc - 2]);
	int seed_step = std::stoi(argv[argc - 3]) * instance_size;
	range = 100000;
	RationalNumber max = RationalNumber(1, 1);
	parseInitOptions(argc, argv);
	for (int i = 0; i < instance_size; ++i) {
		Input_file_name = "test_" + std::to_string(generate_point_size) + "_" + std::to_string(i) ;
		r.seed(i+ seed_step);
		RationalNumber od = test(argc, argv);
		if (od.numerator() < 0) continue;
		if (od > max) {
			max = od;
			// overwrite the worst case
			pVector_max_global = pVector_max;
		}
	}
	std::sort(pVector_max_global.begin(), pVector_max_global.end());
	std::cout << max.numerator() <<" "<< max.denominator() << std::endl;
	for (auto& i : pVector_max_global) {
		cout << i.numerator() << endl;
	}

}



/*
#include <cassert>
#include "gurobi_c++.h"
using namespace std;

int
main(int   argc, char* argv[])
{
	try {
		GRBEnv env = GRBEnv();

		GRBModel model = GRBModel(env);

		// Create variables

		GRBVar x = model.addVar(0.0, 9, 0.0, GRB_CONTINUOUS, "x");
		GRBVar y = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "y");
		GRBVar z = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "z");

		// Set objective

		GRBLinExpr obj = x;
		model.setObjective(obj, GRB_MAXIMIZE);

		// Add linear constraint: x + y + z <= 10

		model.addConstr(x + y + z <= 10, "c0");

		// Add bilinear inequality constraint: x * y <= 2

	

		try {
			model.optimize();
		}
		catch (GRBException e) {
			cout << "Failed (as expected)" << endl;
			exit(-1);
		}
		cout << x.get(GRB_StringAttr_VarName) << " "
			<< x.get(GRB_DoubleAttr_X) << endl;
		cout << y.get(GRB_StringAttr_VarName) << " "
			<< y.get(GRB_DoubleAttr_X) << endl;
		cout << z.get(GRB_StringAttr_VarName) << " "
			<< z.get(GRB_DoubleAttr_X) << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
		exit(-1);
	}
}
*/