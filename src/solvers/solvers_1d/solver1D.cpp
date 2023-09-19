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
	for (vector<unsigned int>::iterator it = pVector.begin(); it != pVector.end(); ++it) {
		cout << i << ": "<< *it << endl;
		i++;
	
	}

};
void Solver_1D::debug(vector<unsigned int>& points) {
	for (vector<unsigned int>::iterator it = pVector.begin(); it != pVector.end()-1; ++it) {
		assert((*it) < *(it + 1));
	}
};

void Solver_1D::read_point(char* str) {
	pVector.push_back(atoi(strtok(str, " ")));
}

void Solver_1D::set(size_t point_size) {
	pVector.reserve(point_size);
}

bool Solver_1D::check_planarity() {
	for (auto it = solution.begin(); it != solution.end();  it++) {
		for (auto iv = next(it,1); iv != solution.end(); iv++) {
			if (find_cross(*it, *iv)) {

				return false;
			}
		}
	}
	return true;


};
bool find_cross(const Arc_1D& a1, const Arc_1D& a2)
{
	if (a1.s < a2.s) return (a1.t < a2.t && a1.t > a2.s);
	else {
		if(a1.s > a2.s) return (a2.t < a1.t && a2.t > a1.s);
	}
	return false;
}