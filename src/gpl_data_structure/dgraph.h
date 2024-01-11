/*
 * graph.h
 *
 *  Created on: Sep 24, 2019
 *  Author: guangping
 *  Self-defined graph representation.
 *  Considering the extern algorithms we choose may be sensitive to the size of verices, we use this way.
 *
 *
 * adapted 2021
 * remove the dynamic part
 * add vertex weights
 */
#pragma once
 //#include <assert.h>
#include "graph.h"

class DGraph: public Graph{
public:
    DGraph() {};
    DGraph(int n);
    void addEdges(const vector<pair<unsigned int, unsigned int>>& edges);
    void addEdge(unsigned int source, unsigned int target) override;
    bool containEdge(unsigned int source, unsigned int target) override;
    RationalNumber get_dilation(const vector<RationalNumber>& pVector);
    RationalNumber get_dilation_dijkstra(const vector<RationalNumber>& pVector);
    RationalNumber get_dilation_dijkstra(const vector<RationalNumber>& pVector, size_t s);
    int minDistance(const vector<RationalNumber>& pVector, const vector<RationalNumber>& dist, const vector<bool>& sptSet);
    RationalNumber get_shortest_path_complete(const vector<RationalNumber>& pVector, size_t s, size_t t);
    void draw_tikz(double range, std::string path, const vector<RationalNumber>& pVector, std::string optional_parameters);
};