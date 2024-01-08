#include "solver1D1P.h"



 void Arc_1D::print() const{
	cout << "Arc (" << s << ", " << t << "), " << l << std::endl;
}

void Arc_1D::debug(vector<unsigned int>& pVector) {
	assert(pVector.size() > t);
	assert(pVector.size() > s);
	assert(fabs(pVector[t] - pVector[s]) == l);

}


bool Solver_1D1P::isPlanarity() {
	std::set<unsigned int>::iterator it;
	std::set<unsigned int>::iterator iv;
	for (unsigned int i = 0; i < solution_g.adList.size(); i++) {
		it = solution_g.adList[i].InNeighborhood.begin();
		while (it != solution_g.adList[i].InNeighborhood.end()) {
			for (unsigned int j = i + 1; j < solution_g.adList.size(); j++) {
				iv = solution_g.adList[j].InNeighborhood.begin();
				while (iv != solution_g.adList[j].InNeighborhood.end()) {
					if (find_cross(*it, i, *iv, j)) return false;
					iv++;
				}
			}
			it++;
		}
	}

	return true;
};

void Solver_1D::output( double od) {
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
	ofs << "d " <<od<< endl;
	size_t eSize = 0;
	for (unsigned int i = solution_g.start_index; i <= solution_g.end_index; i++) {
		eSize += solution_g.adList[i].InNeighborhood.size();
	}
	for (unsigned int i = solution_g.start_index; i <= solution_g.end_index; ++i) {
		ofs << i << ": " << endl;
		ofs << "in: ";
		for (auto itr = solution_g.adList[i].InNeighborhood.begin(); itr != solution_g.adList[i].InNeighborhood.end(); ++itr) {
			ofs << *itr << " ";
		}
		ofs << endl;
		ofs << "out: ";
		for (auto itr = solution_g.adList[i].OutNeighborhood.begin(); itr !=  solution_g.adList[i].OutNeighborhood.end(); ++itr) {
			ofs << *itr << " ";
		}
		ofs << endl;
	}
	ofs.close();
}
void Solver_1D::draw() {
	std::string filename = "D:/GIT/OriSpannerP/OSpanner/drawSolution.py ";
	std::string command = "d:/GIT/OriSpannerP/.venv/Scripts/python.exe ";
	command += filename;
	char file_str[400];
	strcpy(file_str, Result_folder_s.c_str());
	strcat(file_str, get_file_name_no_extension(Input_file_s).c_str());
	strcat(file_str, Algo_t.c_str());
	strcat(file_str, "solution.tex");
	command += file_str;
	system(command.c_str());
}