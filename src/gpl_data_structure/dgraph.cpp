/*
 * dgraph.cpp
 *
 *  Created on: Sep 22, 2023
 *      Author: guangping
 */
#include "dgraph.h"
DGraph::DGraph() {
    start_index = 0;
    end_index = 0;
}
DGraph::DGraph(int n) {
    adList.reserve(n);
    for (int i = 0; i < n; i++) {
        adList.push_back(Node(i));
    }
    start_index = 0;
    end_index = n - 1;
}
void DGraph::set_start(size_t start_t) {
    start_index = start_t;
}

void DGraph::set_end(size_t end_t) {
    end_index = end_t;
}

size_t DGraph::get_edges_size()
{
    size_t eSize = 0;
    for (unsigned int i = start_index; i <=end_index; i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    return eSize / 2;
}

size_t DGraph::get_vertices_size() {
    return end_index-start_index+1 ;
}
// add edge (v1, v2)
void DGraph::addEdge(unsigned int v1, unsigned int v2) {
    assert(v1<= end_index);
    assert(v2 <= end_index);
    assert(v1 >= start_index);
    assert(v2 >= start_index);
    assert(v1 > v2 + 1);
    adList[v1].OutNeighborhood.insert(v2);
    adList[v2].InNeighborhood.insert(v1);
};
void DGraph::removeEdge(unsigned int v1, unsigned int v2) {
    assert(v1 <= end_index);
    assert(v2 <= end_index);
    assert(v1 >= start_index);
    assert(v2 >= start_index);
    adList[v1].OutNeighborhood.erase(v2);
    adList[v2].InNeighborhood.erase(v1);

}

// check if one edge between two vertices exists
//v1: vertexID
//v2: vertexID

bool DGraph::containEdge(unsigned int v1, unsigned int v2) {
    assert(v1 <= end_index);
    assert(v2 <= end_index);
    assert(v1 >= start_index);
    assert(v2 >= start_index);
    return (adList[v1].OutNeighborhood.count(v2) != 0 && adList[v2].InNeighborhood.count(v1) != 0);
};
// check vertexID<< numV
// check if no edge bidirected 
void DGraph::debug() {
    set<unsigned int>::iterator it;
    for (unsigned int i = start_index; i <=end_index; i++) {
        it = adList[i].InNeighborhood.begin();
        while (it != adList[i].InNeighborhood.end()) {
            assert(!containEdge(i, *it));
            //index < numV
            assert(*it <= adList.size());
            it++;
        }
        it = adList[i].OutNeighborhood.begin();
        while (it != adList[i].OutNeighborhood.end()) {
            //undirected graph (u,v)->(v,u)
            assert(!containEdge(*it, i));
            //index < numV
            assert(*it <= adList.size());
            it++;
        }
    }
};

// print adjecency list
void DGraph::print() {
    size_t eSize = 0;
    for (unsigned int i = start_index; i <=end_index; i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    for (unsigned int i = start_index; i <= end_index; ++i) {
        cout << i << ": " << endl;
        cout << "in: ";
        for (auto itr = adList[i].InNeighborhood.begin(); itr != adList[i].InNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
        cout << "out: ";
        for (auto itr = adList[i].OutNeighborhood.begin(); itr != adList[i].OutNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
};

void DGraph::output() {

    size_t eSize = 0;
    for (unsigned int i = start_index; i <= end_index; i++) {
        eSize += adList[i].InNeighborhood.size();
    }
    for (unsigned int i = start_index; i <= end_index; ++i) {
        cout << i << ": " << endl;
        cout << "in: ";
        for (auto itr = adList[i].InNeighborhood.begin(); itr != adList[i].InNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
        cout << "out: ";
        for (auto itr = adList[i].OutNeighborhood.begin(); itr != adList[i].OutNeighborhood.end(); ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }
}







double  DGraph::get_dilation(const vector<double>& pVector) {
    double tmax = 0;
    size_t inD = 0;
    size_t outD = 0;
    size_t l = 0;
    size_t r = 0;
    for (int i = start_index + 1; i <= end_index-1; i++) {
        inD = adList[i].InNeighborhood.size();
        outD = adList[i].OutNeighborhood.size();
        //case a and case c
        if (inD == 0) {
            //a (p_i-1, p_i+1)
            if (outD == 0) tmax = std::max(tmax, 1.0);
            //c left flip
            else {
                l = *(adList[i + 1].OutNeighborhood.rbegin());
                tmax = max(tmax, (pVector[i + 1] - pVector[l]) / (pVector[i + 1] -pVector[i - 1]));
            }


        }
        // case b and d
        else {
            //right flip
            if (outD == 0) {
                r = *(adList[i - 1].InNeighborhood.begin());
                tmax = max(tmax, double(pVector[r] - pVector[i - 1]) / double(pVector[i + 1] - pVector[i - 1]));
            }
            // both side flips
            else {
                l = *(adList[i].OutNeighborhood.rbegin());
                r = *(adList[i].InNeighborhood.begin());
                tmax = max(tmax, double(pVector[r] - pVector[l]) / double(pVector[i + 1] - pVector[i - 1]));
            }

        }
    }
/*
    assert(end_index - start_index >= 2);
    // consider the edge cases of a sub-instance (pl, p_l+1) and (p_r-1, pr)
    if (start_index > 0) {
        unsigned int back_r = *adList[start_index].InNeighborhood.begin();
        assert(back_r > start_index+1 && back_r <= end_index);
        double  start_odil =  2*(pVector[back_r] - pVector[start_index])/ get_shortest_path_complete(pVector, start_index, start_index + 1);
        tmax = max(tmax, start_odil);
    
    }
    if (end_index  <  pVector.size() -1) {
        unsigned int back_l = *adList[end_index].OutNeighborhood.rbegin();
        assert(back_l >= start_index && back_l < end_index -1);
        double end_odil = 2*(pVector[end_index] - pVector[back_l])/ get_shortest_path_complete(pVector, end_index, end_index -1);
        tmax = max(tmax, end_odil);

    }
    assert(tmax >= 1);
    assert(tmax <= pVector[end_index] - pVector[start_index] + 1);
    //double od = get_dilation_dijkstra(pVector);
    //assert(tmax == get_dilation_dijkstra(pVector));
    */
    return tmax;
};

double DGraph::get_dilation_dijkstra(const vector<double>& pVector, size_t src) {
    size_t V = pVector.size();
    vector<double> dist;
    vector<bool> processed;
    for (int i = 0; i < V; i++) {
        dist.push_back(INT_MAX);
        processed.push_back(false);
    }
    dist[src] = 0;
    for (int count = 0; count < V; count++) {
        int u = minDistance(pVector, dist, processed);
        processed[u] = true;
        for (size_t v = start_index; v <= end_index; v++) {
            bool  A = !processed[v];
            bool B = !processed[v] && (adList[u].OutNeighborhood.contains(v) || u < v);
            bool C = !processed[v] && (adList[u].OutNeighborhood.contains(v) || u < v)
                && dist[u] != INT_MAX;
            bool D = dist[u] + std::abs((double)(pVector[u] - pVector[v])) < dist[v];
            double X = std::abs((double)((double)pVector[u] - (double)pVector[v]));
            double E = dist[u] + std::abs((double)(pVector[u] - pVector[v]));
            if (!processed[v] && (adList[u].OutNeighborhood.contains(v) || u < v)
                && dist[u] != INT_MAX
                && dist[u] + std::abs((double)((double)pVector[u] - (double)pVector[v])) < dist[v]) {
                dist[v] = dist[u] + std::abs((double)((double)pVector[u] - (double)pVector[v]));
            }
        }
    }
    double tmax = 1.0;
    double od = 0;
    for (int i = start_index; i < src; i++) {
        // coumpute od
        od = (dist[i] + (pVector[src] - pVector[i])) / get_shortest_path_complete(pVector, src, i);
        assert(od >= 1);
        assert(od <= pVector[end_index] - pVector[start_index] + 1);
        tmax = std::max(tmax, od);
    }
    assert(tmax >= 1);
    assert(tmax <= pVector[end_index]- pVector[start_index] + 1);
    return tmax;
}

double DGraph::get_dilation_dijkstra(const vector<double>& pVector) {
    double tmax = 0;
    double od = 0;
    for (int i = start_index; i <= end_index; i++) {
        od = get_dilation_dijkstra(pVector, i);
        tmax = std::max(tmax, od);
    }
    return tmax;
}

double DGraph::get_shortest_path_complete(const vector<double>& pVector, size_t s, size_t t) {
    if (s > t) swap(s, t);
    if (t > s + 1) return 2 * (pVector[t] - pVector[s]);
    // searching for the nearst point
    else {
        double  prev = -INT_MAX;
        double suss = INT_MAX;
        if (s > 0) prev = pVector[s - 1];
        if (t < pVector.size() - 1) suss = pVector[t + 1];
        double dis = pVector[s] - prev;
        if (dis > suss - pVector[t]) dis = suss - pVector[t];
        return 2 * (pVector[t] - pVector[s] + dis);
    }
}




int DGraph::minDistance(const vector<double>& pVector, const vector<double>& dist, const vector<bool>& processed)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < pVector.size(); v++)
        if (processed[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void DGraph::merge(const DGraph& G2) {
    set<unsigned int>::iterator it;
    start_index = min(start_index, G2.start_index);
    end_index = max(end_index, G2.end_index);
    for (unsigned int i = G2.start_index; i <= G2.end_index; i++) {
        it = G2.adList[i].InNeighborhood.begin();
        while (it != G2.adList[i].InNeighborhood.end()) {
            assert(*it <= G2.end_index);
            assert(i <= G2.end_index);
            assert(*it >= G2.start_index);
            assert(i >= G2.start_index);
            addEdge(*it, i);
            //index < numV
            it++;
        }
    }

};