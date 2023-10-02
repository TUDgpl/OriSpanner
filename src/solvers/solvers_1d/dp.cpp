#include "dp.h"
double DP::solve() {
	//initialize
	/*
	oE = vector < vector<vector<vector<DGraph>>>>(pVector.size(),
		vector<vector<vector<DGraph>>>(pVector.size(),
			vector<vector<DGraph>>(pVector.size(), vector<DGraph>(pVector.size(),
				DGraph(pVector.size())
			))));
	*/
	valid = vector < vector<vector<vector<bool>>>>(pVector.size(),
		vector<vector<vector<bool>>>(pVector.size(),
			vector<vector<bool>>(pVector.size(), vector<bool>(pVector.size(), false)
			)));


	back_tracing = vector < vector<vector<vector<tuple<int, int,int>>>>>(pVector.size(),
		vector<vector<vector<tuple<int, int, int>>>>(pVector.size(),
			vector<vector<tuple<int, int, int>>>(pVector.size(), vector<tuple<int, int, int>>(pVector.size(), tuple<int, int, int>(-2, -2, -2))
			)));

	odV = vector < vector<vector<vector<double>>>>(pVector.size(),
		vector<vector<vector<double>>>(pVector.size(),
			vector<vector<double>>(pVector.size(), vector<double>(pVector.size(), INT_MAX)
			)));


	for (int s = 2; s < pVector.size(); s++) {
		for (int l = 0; l < pVector.size()-s; l++) {
			int r = l + s;
			for (int lp = l + 2; lp <= r; lp++) {
				for (int rp = l; rp < r - 1; rp++) {
					std::cout << "(" << l << ", " << lp << ", " << rp << ", " << r << ") " << std::endl;
					if (lp == r && rp == l && r == l+2) {
						//std::cout << "case ix" << std::endl;
						//oE[l][lp][rp][r].set_start(l);
						//oE[l][lp][rp][r].set_end(r);
						//oE[l][lp][rp][r].addEdge(r, l);
						valid[l][lp][rp][r] = true;

						odV[l][lp][rp][r] = 1.0;
						// mark it as an end point of the back-tracing
						back_tracing[l][lp][rp][r] = tuple<int, int,int>(-1, -1, -1);
						//assert(oE[l][lp][rp][r].get_dilation(pVector) <= 2.5);
						//assert(oE[l][lp][rp][r].start_index == l);
						//assert(oE[l][lp][rp][r].end_index == r);
						continue;
					}
					if (lp <r && rp > l && lp > rp) {
						//std::cout << "case x" << std::endl;
						valid[l][lp][rp][r] = false;
						continue;
					}
					if (lp < r && rp == l) {
						//std::cout << "case xi" << std::endl;
						int krmin = -1;
						double minOdil = INT_MAX;
						for (int kr = l; kr <= r - 3; kr++) {
							assert(valid[l][lp][kr][r - 1] || (lp <r-1 && kr > l && lp > kr) || (lp == r-1 && kr == l && r-1 != l + 2));
							if (valid[l][lp][kr][r - 1]) {
								//oE[l][lp][kr][r - 1].set_end(r);
								//oE[l][lp][kr][r - 1].addEdge(r, l);
								//assert(oE[l][lp][kr][r - 1].start_index == l);
								//assert(oE[l][lp][kr][r - 1].end_index == r);
								double tempOdil = max(odV[l][lp][kr][r - 1], (pVector[r] - pVector[l]) / (pVector[r] - pVector[r - 2]));
								//assert(tempOdil == oE[l][lp][kr][r - 1].get_dilation(pVector));
								if (tempOdil < minOdil) {
									minOdil = tempOdil;
									krmin = kr;
								}
								//oE[l][lp][kr][r - 1].removeEdge(r, l);
								//oE[l][lp][kr][r - 1].set_end(r - 1);
							}
						};
						//oE[l][lp][rp][r] = oE[l][lp][krmin][r - 1];
						//oE[l][lp][rp][r].set_start(l);
						//oE[l][lp][rp][r].set_end(r);
						//oE[l][lp][rp][r].addEdge(r, l);
						odV[l][lp][rp][r] = minOdil;
						//odV[l][lp][rp][r] = oE[l][lp][rp][r].get_dilation(pVector);
						assert(odV[l][lp][rp][r] = minOdil );
						valid[l][lp][rp][r] = true;
						back_tracing[l][lp][rp][r] = tuple<int, int,int>(-3,-1, krmin);
						//assert(oE[l][lp][rp][r].start_index == l);
						//assert(oE[l][lp][rp][r].end_index == r);
						//assert(oE[l][lp][rp][r].get_dilation(pVector) <= pVector[r]- pVector[l]+1);
						continue;
					}

					if (lp == r && rp > l) {
						//std::cout << "case xii" << std::endl;
						int klmin = -1;
						double minOdil = INT_MAX;
						double tempOdil;
						for (int kl = l + 3; kl <= r; kl++) {
							assert(valid[l + 1][kl][rp][r] || (kl < r && rp > l + 1 && kl > rp) || (kl == r && rp == l+1 && r != l + 3));
							if (valid[l + 1][kl][rp][r]) {
								//oE[l + 1][kl][rp][r].set_start(l);
								//oE[l + 1][kl][rp][r].addEdge(r, l);
								//assert(oE[l + 1][kl][rp][r].start_index == l);
								//assert(oE[l + 1][kl][rp][r].end_index == r);
								tempOdil = max(odV[l + 1][kl][rp][r], (pVector[r] - pVector[l]) / (pVector[l+2] - pVector[l]));
 								//tempOdil = oE[l + 1][kl][rp][r].get_dilation(pVector);
								//assert(tempOdil == max(odV[l + 1][kl][rp][r], (pVector[r] - pVector[l]) / (pVector[l + 2] - pVector[l])));
								if (tempOdil < minOdil) {
									minOdil = tempOdil;
									klmin = kl;
								}
								//oE[l + 1][kl][rp][r].removeEdge(r, l);
								//oE[l + 1][kl][rp][r].set_start(l + 1);
							}
						};
						//oE[l][lp][rp][r] = oE[l + 1][klmin][rp][r];
						//oE[l][lp][rp][r].set_start(l);
						//oE[l][lp][rp][r].set_end(r);
						//oE[l][lp][rp][r].addEdge(r, l);
						valid[l][lp][rp][r] = true;
						odV[l][lp][rp][r] = minOdil;
						//odV[l][lp][rp][r] = oE[l][lp][rp][r].get_dilation(pVector);
						//assert(odV[l][lp][rp][r] == minOdil);
						back_tracing[l][lp][rp][r] = tuple<int, int,int>(-4,klmin,-1);
						//assert(oE[l][lp][rp][r].start_index == l);
						//assert(oE[l][lp][rp][r].end_index == r);
						//assert(oE[l][lp][rp][r].get_dilation(pVector) <= pVector[r] - pVector[l] + 1);
						continue;
					}

					if (lp < r && rp > l && lp <= rp) {
						//std::cout << "case xiii" << std::endl;
						int klmin = -1;
						int krmin = -1;
						int kmin = -1;
						double minOdil = INT_MAX;
						double tempOdil;
						for (int k = max(l + 2, lp); k <= min(r - 2, rp); k++) {
							for (int kr = l; kr <= k - 2; kr++) {
								for (int kl = k + 2; kl <= r; kl++) {
									assert(valid[l][lp][kr][k] == true||(lp < k && kr > l && lp > kr)||(lp == k && kr == l && k != l + 2));
									assert(valid[k][kl][rp][r] == true||(kl < r && rp > k && kl > rp) || (kl == r && rp == k && r != k + 2));
									if (valid[l][lp][kr][k] && valid[k][kl][rp][r]) {
										//assert(oE[l][lp][kr][k].start_index == l);
										//assert(oE[k][kl][rp][r].end_index == r);
										tempOdil = max({ odV[l][lp][kr][k], odV[k][kl][rp][r], (pVector[kl]-pVector[kr])/ (pVector[k+1] - pVector[k-1])});
										//DGraph t = oE[l][lp][kr][k];
										//t.merge(oE[k][kl][rp][r]);
										//t.addEdge(r, l);

										//tempOdil = t.get_dilation(pVector);
										//assert(tempOdil == max({ odV[l][lp][kr][k], odV[k][kl][rp][r], (pVector[kl] - pVector[kr]) / (pVector[k + 1] - pVector[k - 1]) }));
										if (tempOdil < minOdil) {
											minOdil = tempOdil;
											klmin = kl;
											kmin = k;
											krmin = kr;
										}
									}
								}

							}

						}
						//oE[l][lp][rp][r] = oE[l][lp][krmin][kmin];
						//oE[l][lp][rp][r].merge(oE[kmin][klmin][rp][r]);
						//oE[l][lp][rp][r].set_start(l);
						//oE[l][lp][rp][r].set_end(r);
						//oE[l][lp][rp][r].addEdge(r, l);
						valid[l][lp][rp][r] = true;
						odV[l][lp][rp][r] = minOdil;
						back_tracing[l][lp][rp][r] = tuple<int, int, int>(kmin, klmin, krmin);
						//assert(oE[l][lp][rp][r].get_dilation(pVector) == odV[l][lp][rp][r]);
						//assert(oE[l][lp][rp][r].get_dilation(pVector) <= pVector[r] - pVector[l] + 1);
						continue;
					}
				}
			}
		}
	}
	int lpmin = -1;
	int rpmin = -1;
	double minOdil = INT_MAX;
	double tempOdil;
	for (int lp = 2; lp < pVector.size(); lp++) {
		for (int rp = 0; rp < pVector.size()-2; rp++) {
			assert(valid[0][lp][rp][pVector.size() - 1] == true || (lp < pVector.size() - 1 && rp > 0 && lp > rp) || (lp == pVector.size()-1 && rp == 0));
			if(valid[0][lp][rp][pVector.size() - 1] == true){
				tempOdil = odV[0][lp][rp][pVector.size() - 1];
				//tempOdil = oE[0][lp][rp][pVector.size() - 1].get_dilation(pVector);
				if (tempOdil < minOdil) {
					minOdil = tempOdil;
					lpmin = lp;
					rpmin = rp;
				}
			}
		}
	}
	assert(odV[0][lpmin][rpmin][pVector.size() - 1] == minOdil);
	//solution_g = oE[0][lpmin][rpmin][pVector.size() - 1];
	//assert(isPlanarity() == true);
	//double od = solution_g.get_dilation(pVector);
	//assert(minOdil == od);
	//solution_g.output();
	
	//get the final solution by  back tracing
	back_trace(0, lpmin, rpmin, pVector.size()-1);
	//assert(gg.get_edges_size() == solution_g.get_edges_size());
	//assert(gg.get_dilation_dijkstra(pVector) == solution_g.get_dilation_dijkstra(pVector));
	double od_dij = solution_g.get_dilation_dijkstra(pVector);
	double od = solution_g.get_dilation(pVector);
	assert(abs(od- od_dij) <= epsilon);
	assert(abs(od - odV[0][lpmin][rpmin][pVector.size() - 1]) <= epsilon);
	printf("DP solved with %f", odV[0][lpmin][rpmin][pVector.size() - 1]);
	return odV[0][lpmin][rpmin][pVector.size() - 1];

};



void DP::back_trace(int l, int lp, int rp, int r) {
	solution_g.addEdge(r, l);
	int k = get<0>(back_tracing[l][lp][rp][r]);
	int kl = get<1>(back_tracing[l][lp][rp][r]);
	int kr = get<2>(back_tracing[l][lp][rp][r]);
	if (k == -2) assert(false);
	if (k == -3) {
		assert(kl == -1);
		back_trace(l, lp, kr, r - 1);
		return;
	}
	if (k == -4) {
		assert(kr == -1);
		back_trace( l + 1, kl, rp, r);
		return;
	}
	if (k > 0) {
		assert(kl > k);
		assert(kr < k);
		assert(kr >= 0);
		back_trace(l, lp, kr, k);
		back_trace(k, kl, rp, r);
		return;
	}
	return;







}