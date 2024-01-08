#include "sat1D2P.h"
using namespace std;
// binary search

/*
(i, i+2)
c1 or c2 or c3 or c4
c1: just (i, i+2)
c2: left (l,i+2), l < i
c3: right (i, r), r > i+2
c4: cut va:(l,i+1) and vb:(i+1, r), l < i and r > i+2
*/
void Sat2P:: write_clauses_2(vector<pair<unsigned int, unsigned int>>& candidate_edges, int C, ofstream& outdata, double test_v) {
    for (unsigned int i = 0; i < pVector.size() - 2; i++) {
        unsigned int j = i + 2;
        double maxD = test_v * (pVector[j] - pVector[i]);
        // c1
        outdata << decode(j, i, 0, base) << " " << decode(j, i, 1, base) << " ";
        candidate_edges.push_back(pair<unsigned int, unsigned int>(j, i));
        // c2
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] <= maxD) {
                outdata << decode(j, l, 0, base) << " " << decode(j, l, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(j, l));
            }
            else
                break;
        }
        // c3
        for (int r = j + 1; r < pVector.size(); r++) {
            if (pVector[r] - pVector[i] <= maxD) {
                outdata << decode(r, i, 0, base) << " " << decode(r, i, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(r, i));
            }
            else
                break;
        }
        // c4
        vector<pair<unsigned int, unsigned int>> candidates_ende_pairs;
        int C_start = C;
        // collect all the c4s
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] > maxD) {
                break;
            }
            for (unsigned int r = j + 1; r < pVector.size(); r++) {
                if (pVector[r] - pVector[l] <= maxD) {
                    outdata << C << " ";
                    C++;
                    candidates_ende_pairs.push_back(
                        pair<unsigned int, unsigned int>(l, r));
                }
                else {
                    break;
                }
            }
        }
        outdata << "0" << std::endl;
        // add c4 clauses
        for (int index = 0; index < candidates_ende_pairs.size(); index++) {
            outdata << -C_start << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 0, base)
                << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                i + 1, candidates_ende_pairs[index].first));
            outdata << -C_start << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                candidates_ende_pairs[index].second, i + 1));
            C_start++;
        }
    }
}

void Sat2P::write_clauses_3( vector<pair<unsigned int, unsigned int>>& candidate_edges, int C,
    ofstream& outdata, double test_v) {
    //  consider all pairs <i, i+3>
    /*
    c1 or c2 or c3 or c41 or c42 or c43
    c1: just (i, i+3)
    c2: left (l,i+3), l < i
    c3: right (i, r), r > i+3
    c41: cut va:(l,i+1) and vb:(i+1, r), l < i and r > i+2
    c42: cut va:(l,i+2) and vb:(i+2, r), l < i+1 and r > i+3
    c43: cut va:(l,i+2) and vb:(i+1, r), l < i+1 and r > i+2
    */
    for (unsigned int i = 0; i < pVector.size() - 3; i++) {
        unsigned j = i + 3;
        double maxD = test_v * (pVector[j] - pVector[i]);
        // c1
        outdata << decode(j, i, 0, base) << " " << decode(j, i, 1, base) << " ";
        candidate_edges.push_back(pair<unsigned int, unsigned int>(j, i));
        // c2
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] <= maxD) {
                outdata << decode(j, l, 0, base) << " " << decode(j, l, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(j, l));
            }
            else
                break;
        }
        // c3
        for (int r = j + 1; r < pVector.size(); r++) {
            if (pVector[r] - pVector[i] <= maxD) {
                outdata << decode(r, i, 0, base) << " " << decode(r, i, 1, base) << " ";
                candidate_edges.push_back(pair<unsigned int, unsigned int>(r, i));
            }
            else
                break;
        }
        // c4
        vector<bool> candidates_ende_pairs_valid_c43;
        vector<pair<unsigned int, unsigned int>> candidates_ende_pairs;
        int C_start = C;
        for (int l = i - 1; l >= 0; l--) {
            if (pVector[j] - pVector[l] > maxD) break;
            for (unsigned int r = j + 1; r < pVector.size(); r++) {
                if (pVector[r] - pVector[l] <= maxD) {
                    // for c41
                    outdata << C << " ";
                    C++;
                    // for c42
                    outdata << C << " ";
                    C++;
                    candidates_ende_pairs.push_back(
                        pair<unsigned int, unsigned int>(l, r));
                    // for c43
                    if (pVector[r] - pVector[l] + pVector[i + 2] - pVector[i + 1] <=
                        maxD) {
                        candidates_ende_pairs_valid_c43.push_back(true);
                        outdata << C << " ";
                        C++;
                    }
                    else {
                        candidates_ende_pairs_valid_c43.push_back(false);
                    }
                }
                else {
                    break;
                }
            }
        }
        outdata << "0" << std::endl;
        // add c4 clauses
        for (int index = 0; index < candidates_ende_pairs.size(); index++) {
            // c41
            outdata << -C_start << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 0, base)
                << " "
                << decode(i + 1, candidates_ende_pairs[index].first, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                i + 1, candidates_ende_pairs[index].first));
            outdata << -C_start << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                << " "
                << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                candidates_ende_pairs[index].second, i + 1));
            C_start++;
            // c42
            outdata << -C_start << " "
                << decode(i + 2, candidates_ende_pairs[index].first, 0, base)
                << " "
                << decode(i + 2, candidates_ende_pairs[index].first, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                i + 2, candidates_ende_pairs[index].first));
            outdata << -C_start << " "
                << decode(candidates_ende_pairs[index].second, i + 2, 0, base)
                << " "
                << decode(candidates_ende_pairs[index].second, i + 2, 1, base)
                << " 0" << endl;
            candidate_edges.push_back(pair<unsigned int, unsigned int>(
                candidates_ende_pairs[index].second, i + 2));
            C_start++;
            // c3
            if (candidates_ende_pairs_valid_c43[index] == true) {
                outdata << -C_start << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 0, base)
                    << " "
                    << decode(i + 2, candidates_ende_pairs[index].first, 1, base)
                    << " 0" << endl;
                outdata << -C_start << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 0, base)
                    << " "
                    << decode(candidates_ende_pairs[index].second, i + 1, 1, base)
                    << " 0" << endl;
                C_start++;
            }
        }
    }
}
void Sat2P::write_solver_input(double test_v) {
    ofstream outdata;
    int count = 0;
    string filename = tmp_dictionary + "/" + Input_file_s + +"_" +
        to_string(test_v) + "_DIMACS.txt";

    outdata.open(filename.c_str());
    if (!outdata) {
        // file couldn't be opened
        cerr << filename << " Error: (write_solver_input) file could not be opened"
            << endl;
        exit(1);
    }
    outdata << "c  SAT for 1D 1PPB  " << filename << endl;
    outdata << std::setprecision(0);
    vector<pair<unsigned int, unsigned int>> edges;
    // Todo: write candidate clauses
    //  consider all pairs <i, i+2>
    // cut edge
    /*not v_S(c4) or v_1a or v2a --- put va and vb to the edge sets
      not v_S or v_1b or v2b
      for each c4, S++;
    */
    //// tuple(a,b,c) -----> edge (a,b) on page c
    int C = 2 * pVector.size() * pVector.size() + 2;
    base = pVector.size();

    vector<pair<unsigned int, unsigned int>> candidate_edges;
    write_clauses_2( candidate_edges,  C, outdata, base);
    write_clauses_3(candidate_edges, C, outdata, base);

    // Todo: first write all candidate clauses (store all edges into a vector
    // edges)
    //       write conflict clauses of crossing edges
    // if edges x and y have crossing --> (not x1) or (not x2) or (not y0) or (not
    // y1)
    for (int i = 0; i < candidate_edges.size(); i++) {
        for (int j = i + 1; j < candidate_edges.size(); j++) {
            if (find_cross(candidate_edges[i], candidate_edges[j])) {
                outdata << -decode(candidate_edges[i].first, candidate_edges[i].second,
                    0, base)
                    << " "
                    << -decode(candidate_edges[i].first, candidate_edges[i].second,
                        1, base)
                    << " "
                    << -decode(candidate_edges[j].first, candidate_edges[j].second,
                        0, base)
                    << " "
                    << -decode(candidate_edges[j].first, candidate_edges[j].second,
                        1, base)
                    << " 0" << endl;
            }
        }
    }

    outdata << flush;
    outdata.close();
}
// Todo: check if it is a valid solution
//      check if it is crossing-free
//      compute the dilation (<= test_v)

//// tuple(a,b,c) -----> edge (a,b) on page c
void Sat2P::verify(const vector<unsigned int>& solution_indices, double test_v) {
    vector<pair<unsigned int, unsigned int>> page_0;
    vector<pair<unsigned int, unsigned int>> page_1;
    unsigned int base = pVector.size();
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
    // planarity check
    assert(is_planar(page_0));
    assert(is_planar(page_1));
    // compute dilation and check if it is <= test_v
    // set up the graph
    solution= DGraph(pVector.size());
    solution.addEdges(page_0);
    solution.addEdges(page_1);
    double od = solution.get_dilation(pVector);
    assert(od <= test_v);
}
bool Sat2P::read_solution(double test_v) {
    vector<unsigned int> solution_indices;
    string file_d =
        tmp_dictionary + "/" + Input_file_s + +"_" + to_string(test_v);
    string solution_d = file_d + "_DIMACS_solution.txt";
    ifstream solution_file;
    solution_file.open(solution_d.c_str());
    if (!solution_file) {
        // file couldn't be opened
        cerr << "Error: solution file could not be opened" << endl;
        cerr << "Error:" << solution_d << endl;
        exit(1);
    }
    string line;
    char head;
    int i;
    getline(solution_file, line);
    char* str = strdup(line.c_str());
    const char s[2] = " ";
    char* token = strtok(str, s);
    while (token != NULL) {
        i = atoi(token);
        if (i > 0) {
            // Todo: how to know if it is satisfiing and how to encode the index as
            // tripe
            solution_indices.push_back(i);
        }
        token = strtok(NULL, s);
    }
    solution_file.close();
    if (remove((file_d + "_DIMACS_solution.txt").c_str()) != 0)
        perror("Error deleting solution file");
    verify(solution_indices, test_v);
    return true;
};

bool Sat2P::sat_solve(bool only_short, double test_v) {
    // remove the datas
    string file_d =
        tmp_dictionary + "/" + Input_file_s + +"_" + to_string(test_v);
    write_solver_input(test_v);
    string o = sat_solver_PATH + file_d + "_DIMACS.txt " + file_d +
        "_DIMACS_solution.txt";
    int success = system(o.c_str());
    if (remove((file_d + "_DIMACS.txt").c_str()) != 0)
        perror("Error deleting instance file");

    return read_solution(test_v);
}
vector<double> Sat2P::get_candidate() {
    std::set<double> candidate_ods;
    for (int i = 0; i < pVector.size() - 2; i++) {
        // consider all pairs <i, i+2>
        int j = i + 2;
        double sp = pVector[j] - pVector[i];
        for (int k = 0; k <= i; k++) {
            for (int m = j; m < pVector.size(); m++) {
                double sc = pVector[m] - pVector[k];
                if (sc / sp <= teo_g) candidate_ods.insert(sc / sp);
            }
        }
    }
    for (int i = 0; i < pVector.size() - 2; i++) {
        // consider all pairs <i, i+3>
        int j = i + 3;
        double sp = pVector[j] - pVector[i];
        double rp = pVector[i + 2] - pVector[i + 1];
        for (int k = 0; k <= i; k++) {
            for (int m = j; m < pVector.size(); m++) {
                double sc = pVector[m] - pVector[k];
                if (sc / sp <= teo_g) candidate_ods.insert(sc / sp);
                if ((sc + rp) / sp <= teo_g) candidate_ods.insert((sc + rp) / sp);
            }
        }
    }
    vector<double> vc(candidate_ods.begin(), candidate_ods.end());
    return vc;
}


double Sat2P::solve() {
    vector<double> candidate_ods = get_candidate();
    int l = 0;
    int r = candidate_ods.size() - 1;
    double best_od = 2.0;
    while (r >= l) {
        int mid = l + (r - l) / 2;
        bool found = sat_solve(candidate_ods[mid], false);
        best_od = candidate_ods[mid];
        if (found) {
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    assert(best_od <= teo_g)
    return best_od;
}
