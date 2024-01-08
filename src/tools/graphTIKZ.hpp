/*
 * This is an example header file that visualizes edges and points. You can just include this file in your project, don't forget to include the file in your CMakeLists.txt (although you shouldn't need to worry about this if you set up the project correctly)
 * Author: Antonia Kalb
 * Date: 23-05-2023
 */

#pragma once

#include <vector>
#include <fstream>
#include "../directed_graph_adj_list.hpp"

// Here we use very simple structures for points and edges, as mentioned before you should probably use boost. Modify the code accordingly
struct Point
{
    int x;
    int y;
};

struct Edge
{
    Point s;
    Point t;
};


/**
 * path represents the location where the file will be stored, should end with .tex
 */
void visualize(std::string path, std::vector<Point> points, std::vector<Edge> edges, std::string optional_parameters)
{
    std::ofstream o(path);

      // Enviroment
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o  << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (Point p : points)
    {
        o  << "\\node[] at ("<< p.x << ","<< p.y <<") ("<< p.x << "-"<< p.y <<") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (Edge e : edges)
    {
        o  << "\\draw ("<< e.s.x << "-"<< e.s.y << ") edge ("<< e.t.x << "-"<< e.t.y << ");" << std::endl;
    }

     // END of File
    o << "  \\end{tikzpicture}\n";

    o.close();
}

void generate_tikz_graph(std::string path, std::vector<std::vector<uint64_t>> coordinates, directed_graph_adj_list adj_list, std::string optional_parameters)
{
    uint64_t num_nodes = coordinates.size();
    std::ofstream o(path);

    // Enviroment
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o  << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o  << "\\node[] at ("<< coordinates[i][0] << ","<< coordinates[i][1] <<") ("<< coordinates[i][0] << "-"<< coordinates[i][1] <<") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            if (adj_list.is_outneighbour(i, j)){
                o << "\\draw ("<< coordinates[i][0] << "-"<< coordinates[i][1] <<") edge ("<< coordinates[j][0] << "-"<< coordinates[j][1] <<");" << std::endl;
            }
        }
    }

    // END of File
    o << "  \\end{tikzpicture}\n";

    o.close();
}

void generate_tikz_graph(std::string path, std::vector<uint64_t> coordinates, directed_graph_adj_list adj_list, std::string optional_parameters)
{
    uint64_t num_nodes = coordinates.size();
    std::ofstream o(path);

    // Enviroment
    o << "\\begin{tikzpicture}[";
    o << optional_parameters;
    o  << "]" << std::endl;


    // if you want to highligt points, just create another list of points and output them in a similar fashion as below but change stroke (color), size, and name (shape)
    for (int i = 0; i < num_nodes; ++i) {
        o  << "\\node[] at ("<< coordinates[i] << ","<< 0 <<") ("<< coordinates[i]<<") {} ;" << std::endl;
    }

    // if you want to highligt edges, just create another list of edges and output them in a similar fashion as below but change stroke (color) and pen (thickness)
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            if (adj_list.is_outneighbour(i, j)){
                o << "\\draw ("<< coordinates[i] <<") edge";
                if (j!=i+1){// baseline is straight
                    o << "[bend right]";
                }
                o << " ("<< coordinates[j] <<");" << std::endl;
            }
        }
    }

    // END of File
    o << "  \\end{tikzpicture}\n";

    o.close();
}