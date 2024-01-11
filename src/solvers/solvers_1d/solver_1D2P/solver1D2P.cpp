#include "solver1D2P.h"
// Todo: check if it is a valid solution
//      check if it is crossing-free
//      compute the dilation (<= test_v)

//// tuple(a,b,c) -----> edge (a,b) on page c


bool Solver_1D2P::is_planarity() {
    // planarity check
    return (is_planar(page_0) && is_planar(page_1));
}

void Solver_1D2P::draw_tikz(double range, std::string path, std::string optional_parameters) {
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
        o << "\\node[minimum size=1mm] at (" << range * boost::rational_cast<double>(pVector[i]) << "," << 0 << ") (" << i << ") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)


    // page 0
    for (auto i :page_0) {
            o << "\\draw (" << i.first << ") edge";
            o << "[bend right]";
            o << " (" << i.second << ");" << std::endl;
    }
    //page 1
    for (auto i : page_1) {
        o << "\\draw (" << i.first << ") edge";
        o << "[bend left]";
        o << " (" << i.second << ");" << std::endl;
    }

      
    for (int i = 0; i < num_nodes - 1; ++i) {
        o << "\\draw (" << i << ") edge";
        o << " (" << i + 1 << ");" << std::endl;
    }
    // END of File
    o << "  \\end{tikzpicture}\n";
    o << "  \\end{document}\n";

    o.close();
};

void Solver_1D2P::set_pages() {
    page_0.clear();
    page_1.clear();
    // set the pages
    for (int i = 0; i < solution_indices.size(); i++) {
        tuple<unsigned int, unsigned int, unsigned int> index =
            encode(solution_indices[i], base);
        if (get<2>(index) == 0) {
            page_0.push_back(
                pair<unsigned int, unsigned int>(get<0>(index), get<1>(index)));
        }
        else {
            assert(get<2>(index) == 1);
            page_1.push_back(
                pair<unsigned int, unsigned int>(get<0>(index), get<1>(index)));
        }
    }
    solution = DGraph(pVector.size());
    solution.addEdges(page_0);
    solution.addEdges(page_1);
}

void Solver_1D2P::set(int point_size) {
    base = point_size;
}

