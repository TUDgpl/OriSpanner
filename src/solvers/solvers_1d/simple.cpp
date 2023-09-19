#include "simple.h"
void Simple::solve() {
	DList L;
	for (int i = 0; i < pVector.size(); i++) 
	{
		L.insert(i);
	}

	// set initial priority queue
	int i = 0;
	for (vector<unsigned int>::iterator it = pVector.begin(); it != pVector.end()-2; ++it) {
		T.push(Arc_1D(i, i+2, *(it+2)-*it));
		i++;
	}
	Arc_1D Cover_min;
	while (!T.empty()) {
		Cover_min = T.top();
		std::cout <<"   Cover_min: "<< Cover_min.s << Cover_min.t << std::endl;
		T.pop();
		// get predecessor and successor
		DList::iterator prev = L.find(Cover_min.s);
		DList::iterator suss = L.find(Cover_min.t);
		if (prev != L.end() && suss != L.end()) {
			L.erase(*(next(prev,1)));
			solution.push_back(Cover_min);
			std::cout << *prev <<", "<< *suss << std::endl;
			DList::iterator prev_v = std::prev(prev,1);
			DList::iterator suss_s = std::next(suss,1);
			//add (i-2, i+1)
			if(prev_v != L.end()) T.push(Arc_1D(*prev_v, *suss, pVector[*suss]- pVector[*prev_v]));
			//add (i-1, i+2)
			if (suss_s != L.end()) T.push(Arc_1D(*prev, *suss_s, pVector[*suss_s]-pVector[*prev]));
		}
	}


	for (auto& i : T) {
		std::cout << i.s <<", "<< i.t << std::endl;
	}
	assert(check_planarity()== true);
	printf("Simple solved");
}
