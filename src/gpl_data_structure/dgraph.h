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
#include <set>
#include <iostream>
#include<fstream>
#include <unordered_set>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include "miscellaneous.h"
using namespace std;
struct Node {
    Node(size_t i) {
        index = i;
    };
    size_t index;
    set<unsigned int> InNeighborhood;
    set<unsigned int> OutNeighborhood;


};
class DGraph {
public:
    vector<Node> adList;
    DGraph();
    DGraph(int n);
    void addEdge(unsigned int source, unsigned int target);
    bool containEdge(unsigned int source, unsigned int target);
    void removeEdge(unsigned int source, unsigned int target);

    size_t get_edges_size();
    size_t get_vertices_size();
    void print();
    void debug();
    void output();

    void merge(const DGraph& G2);

    double get_dilation(const vector<double>& pVector);
    double get_dilation_dijkstra(const vector<double>& pVector);
    double get_dilation_dijkstra(const vector<double>& pVector, size_t s);
    int minDistance(const vector<double>& pVector, const vector<double>& dist, const vector<bool>& sptSet);
    double get_shortest_path_complete(const vector<double>& pVector, size_t s, size_t t);

    size_t start_index;
    size_t end_index;
    void set_start(size_t start_t);
    void set_end(size_t end_t);
};