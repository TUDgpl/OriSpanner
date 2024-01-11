#include "solver1D1P.h"



 void Arc_1D::print() const{
	cout << "Arc (" << s << ", " << t << "), " << l << std::endl;
}

void Arc_1D::debug(vector<RationalNumber>& pVector) {
	assert(pVector.size() > t);
	assert(pVector.size() > s);
	assert(abs(pVector[t] - pVector[s]) == l);

}


bool Solver_1D1P::is_planarity() {
	std::set<unsigned int>::iterator it;
	std::set<unsigned int>::iterator iv;
	for (unsigned int i = 0; i < solution.adList.size(); i++) {
		it = solution.adList[i].InNeighborhood.begin();
		while (it != solution.adList[i].InNeighborhood.end()) {
			for (unsigned int j = i + 1; j < solution.adList.size(); j++) {
				iv = solution.adList[j].InNeighborhood.begin();
				while (iv != solution.adList[j].InNeighborhood.end()) {
					if (find_cross(*it, i, *iv, j)) return false;
					iv++;
				}
			}
			it++;
		}
	}

	return true;
};


void Solver_1D1P::draw_tikz(double range, std::string path,  std::string optional_parameters = "every node/.append style={draw, circle}, rotate = 90")
{
    uint64_t num_nodes = pVector.size();
    std::ofstream o(path);

    // Enviroment
    o << "\\documentclass{article}" << std::endl;
    o << "\\usepackage{tikz}" << std::endl;
    o << "\\begin{document}" << std::endl;
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o << "\\node[] at (" << range * boost::rational_cast<double>(pVector[i])<< "," << 0 << ") (" << i << ") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (int i = 0; i < num_nodes; ++i) {
        for (auto j: solution.adList[i].OutNeighborhood) {
            o << "\\draw (" << i << ") edge";
                o << "[bend right]";
            o << " (" << j << ");" << std::endl;
        }
    }
    for (int i = 0; i < num_nodes-1; ++i) {
        o << "\\draw (" << i << ") edge";
        o << " (" << i+1 << ");" << std::endl;
    }
        // END of File
        o << "  \\end{tikzpicture}\n";
        o << "  \\end{document}\n";

    o.close();
}

