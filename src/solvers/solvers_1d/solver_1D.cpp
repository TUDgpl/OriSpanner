#include "solver_1D.h"

void Solver_1D::read_point(char* str) {
	pVector.push_back(atof(strtok(str, " ")));
};

void Solver_1D::set(size_t point_size) {
	pVector.reserve(point_size);
	solution = DGraph(point_size);
};

void Solver_1D::output(double od) {
	char file_str[400];
	strcpy(file_str, Result_folder_s.c_str());
	strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
	strcat(file_str, Algo_t.c_str());
	strcat(file_str, "solution.txt");

	std::ofstream ofs;
	std::string s(file_str);
	try {
		ofs.open(s, std::fstream::out);
	}
	catch (std::ofstream::failure& e) {
		std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
	}
	ifstream src;
	ofstream dst;
	src.open(Input_file_s, std::fstream::in);
	ofs << src.rdbuf();
	src.close();
	ofs << "d " << od << endl;
	size_t eSize = 0;
	for (unsigned int i = 0; i < pVector.size(); i++) {
		eSize += solution.adList[i].InNeighborhood.size();
	}
	for (unsigned int i = 0; i < pVector.size(); ++i) {
		ofs << i << ": " << endl;
		ofs << "in: ";
		for (auto itr = solution.adList[i].InNeighborhood.begin(); itr != solution.adList[i].InNeighborhood.end(); ++itr) {
			ofs << *itr << " ";
		}
		ofs << endl;
		ofs << "out: ";
		for (auto itr = solution.adList[i].OutNeighborhood.begin(); itr != solution.adList[i].OutNeighborhood.end(); ++itr) {
			ofs << *itr << " ";
		}
		ofs << endl;
	}
	ofs.close();
}

void Solver_1D::draw() {
	char file_str[400];
	strcpy(file_str, Result_folder_s.c_str());
	strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
	strcat(file_str, Algo_t.c_str());
	strcat(file_str, "solution.tex");
	double range = 18.0 / (pVector.back() - pVector[0]);
	draw_tikz(range, file_str, "every node/.append style={draw, circle}, rotate = 90");
}

