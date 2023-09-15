#include "graph.h"
void Arc::print() {
	cout << "Arc (" << s << ", " << t << "), " << l << std::endl;
}

void Arc::debug(vector<unsigned int>& points) {
	assert(points.size() > t);
	assert(points.size() > s);
	assert(points[t] - points[s] == l);

}