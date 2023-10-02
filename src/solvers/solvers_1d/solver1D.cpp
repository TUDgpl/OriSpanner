#include "solver1D.h"



 void Arc_1D::print() const{
	cout << "Arc (" << s << ", " << t << "), " << l << std::endl;
}

void Arc_1D::debug(vector<unsigned int>& pVector) {
	assert(pVector.size() > t);
	assert(pVector.size() > s);
	assert(fabs(pVector[t] - pVector[s]) == l);

}

void Solver_1D::print() {
	// print points
	int i = 0;
	for (vector<double>::iterator it = pVector.begin(); it != pVector.end(); ++it) {
		cout << i << ": "<< *it << endl;
		i++;
	
	}

};
void Solver_1D::debug() {
	for (vector<double>::iterator it = pVector.begin(); it != pVector.end()-1; ++it) {
		assert((*it) < *(it + 1));
	}
};

void Solver_1D::read_point(char* str) {
	pVector.push_back(atof(strtok(str, " ")));
};

void Solver_1D::set(size_t point_size) {
	pVector.reserve(point_size);
	solution_g = DGraph(point_size);
};
bool Solver_1D::isPlanarity() {
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

void Solver_1D::output(const char* outFile, double od) {
	std::ofstream ofs;
	std::string s(outFile);
	//outFile = "/home1/guangping/dynaMIS/RESULT/"+outFile;
	try {
		ofs.open(s, std::fstream::out);
	}
	catch (std::ofstream::failure& e) {
		std::cerr << "Exception opening file: " << std::strerror(errno) << "\n";
	}
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

