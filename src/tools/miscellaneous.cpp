#include "miscellaneous.h"
jsonM measures;

string result_folder_s;
string algo_t;
string input_file_s;
void parseInitOptions(int argc, char* argv[]) {
	cxxopts::Options options("dynaMIS", "Geometric MIS");

	options.add_options()
		("a,algorithm", "Algorithm Option", cxxopts::value<std::string>())
		("h,help", "Print usage")
		("d", "dictionary", cxxopts::value<std::string>()->default_value("D:/GIT/OriSpanner"))
		("f,filename", "input file", cxxopts::value<std::string>())
		;
	options.allow_unrecognised_options();
	auto result = options.parse(argc, argv);
	if (result.count("filename")) {
		input_file_s = strdup(result["filename"].as<std::string>().c_str());
		string outFile(input_file_s);
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

	if (result.count("help"))
	{
		printInitUsage();
		exit(0);
	}


	result_folder_s = result["d"].as<std::string>();

	if (result.count("algorithm")) {
		algo_t = result["algorithm"].as<std::string>();
		measures.addElement("info", "algo_type", algo_t);
	}
};
void printInitOptions() {
	printf("dynaMIS Initialization options \n");
	cout << "file:" << input_file_s << endl;
	cout << "algorithm:" << algo_t << "-" << endl;
	cout << "result_folder:" << result_folder_s << endl;
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

printf("   greedy: a greedy algorithm by selecting the shortes edges\n");
	printf("   *More details see the paper \"Oriented Spanners\" <https://arxiv.org/abs/2306.17097>\n");
	printf("---------------------------------------------------------------------------------\n");
}

void outputMeasure(const char* append) {
	string outFile(input_file_s);
	std::string key = "/";
	std::size_t found = outFile.rfind(key);
	outFile = outFile.substr(found + 1);
	string appendix;
	appendix += "-";
	appendix += algo_t;
	appendix += append;
	measures.output(result_folder_s.c_str(), appendix.c_str(), outFile.c_str());
};