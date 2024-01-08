#include "solver_1D.h"

void Solver_1D::read_point(char* str) {
	pVector.push_back(atof(strtok(str, " ")));
};

void Solver_1D::set(size_t point_size) {
	pVector.reserve(point_size);
	solution = DGraph(point_size);
};