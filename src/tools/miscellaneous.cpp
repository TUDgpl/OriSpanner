#include "miscellaneous.h"
jsonM measures;

string Result_folder_s;
string Algo_t;
string Input_file_s;
double W;
double H;

void printArgs(int argc, char* argv[]) {
	std::cout << argc-1 <<" arguments:" << std::endl;
	if (argc > 1)
	{
		std::copy(argv + 1, argv + argc, std::ostream_iterator<const char*>(std::cout, "\n"));
	}
}
void parseInitOptions(int argc, char* argv[]) {
	printArgs(argc, argv);
	cxxopts::Options options("OriSpanner", "Test");
	options.add_options()
		("a,algorithm", "Algorithm Option", cxxopts::value<std::string>())
		("h,help", "Print usage")
		("d", "dictionary", cxxopts::value<std::string>()->default_value("D:/GIT/OriSpanner"))
		("f,filename", "input file", cxxopts::value<std::string>())
		;
	options.allow_unrecognised_options();
	auto result = options.parse(argc, argv);
	if (result.count("help"))
	{
		printInitUsage();
		exit(0);
	}

	if (result.count("filename")) {
		Input_file_s = strdup(result["filename"].as<std::string>().c_str());
		string outFile(Input_file_s);
		std::string key = "/";
		std::size_t found = outFile.rfind(key);
		outFile = outFile.substr(found + 1);
		measures.addElement("info", "file", outFile);
	}
	else {
		std::cerr << "Input file missing" << std::endl;
		printInitUsage();
		exit(0);
	}



	Result_folder_s = result["d"].as<std::string>();

	if (result.count("algorithm")) {
		Algo_t = result["algorithm"].as<std::string>();
		measures.addElement("info", "algo_type", Algo_t);
	}
};
void printInitOptions() {
	printf("dynaMIS Initialization options \n");
	cout << "file:" << Input_file_s << endl;
	cout << "algorithm:" << Algo_t << "-" << endl;
	cout << "result_folder:" << Result_folder_s << endl;
}

/*print the manual of the program*/
void printInitUsage() {
	cout << "\n--------oriSpanner, a orinted spanner solver by " << GREEN << "TU Dortmund" << RESET << " -----------------\n";
	printf("\nauthor: Guangping Li\n");
	printf("\n-------------------Usage--------------------------------------------------------\n");
	printf("./oriSpanner  <instance> [options]\n");

	printf("\n-------------------Options------------------------------------------------------\n");
	printf("   --help, -h : output this help\n");
	printf("   --algorithm, -a : algorithm in use (see options below)\n");
	printf("---------------------------------------------------------------------------------\n");
	printf("\n-------------------algorithm options------------------------------------------------------\n");
	printf("   ilp : exact solver using Gurobi Optimizer \n");
	printf("   greedy: a greedy algorithm by selecting the shortes edges\n");
	printf("   dp: a dynamic programming algorithm to find an optimal 1-PPB \n");
	printf("   *More details see the paper \"Oriented Spanners\" <https://arxiv.org/abs/2306.17097>\n");
	printf("---------------------------------------------------------------------------------\n");
}

void outputMeasure(const char* append) {
	string outFile(Input_file_s);
	std::string key = "/";
	std::size_t found = outFile.rfind(key);
	outFile = outFile.substr(found + 1);
	string appendix;
	appendix += "-";
	appendix += Algo_t;
	appendix += append;
	measures.output(Result_folder_s.c_str(), appendix.c_str(), outFile.c_str());
};