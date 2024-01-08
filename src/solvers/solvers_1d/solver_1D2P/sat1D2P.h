#pragma once
#include <assert.h>
#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <cassert>
#include <iomanip>
#include <iostream>
#include <istream>
#include <set>
#include <string>
#include <vector>
#include "solver1D2P.h"
#include "dgraph.h"
// binary search


class Sat2P :public Solver_1D2P {
public:
    double solve() override;
    const string Input_file_s;
    int base;

protected:
    vector<double> get_candidate();
    bool sat_solve( bool only_short, double test_v);
    bool read_solution(double test_v);
    void write_solver_input(double test_v);
private:
    void write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges,
        int C, ofstream& outdata,  double test_v);
    void write_clauses_3(vector<pair<unsigned int, unsigned int>>& candidate_edges,
        int C, ofstream& outdata,double test_v);
    void verify(const vector<unsigned int>& solution_indices, double test_v);
};