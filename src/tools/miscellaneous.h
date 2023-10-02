/*
 * miscellaneous.h 
 * OriSpanner
 *  Created on: Sep 15, 2013
 *      Author: guangping
 */

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include<vector>
#include<cassert>
#include <boost/heap/priority_queue.hpp>
#include <set>





#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>


#include "cxxopts.hpp"
#include "jsonM.h"

using namespace std;
extern jsonM Measures;
extern string Result_folder_s;
extern string Input_file_s;
extern string Algo_t;
extern double W;
extern double H;
extern double epsilon;

void hello();


//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



void printArgs(int argc, char* argv[]);
void parseInitOptions(int argc, char* argv[]);
void outputMeasure(const char* append);
void printInitUsage();

struct Arc_1D {
	// s: source index 
	// t: target index
	//l: length
	Arc_1D() { s = 0;  t = 0; l = 0; };
	Arc_1D(unsigned int source, unsigned int target, int len) {
		s = source;
		t = target;
		l = len;
	}
	void print() const;
	void debug(vector<unsigned int>& points);

	unsigned s;
	unsigned t;
	unsigned l;
};



bool find_cross(const Arc_1D& a1, const Arc_1D& a2);

bool find_cross(unsigned int s1, unsigned int t1, unsigned int s2, unsigned int t2);

inline string get_file_name(const std::string& file) {
	const std::size_t found = file.find_last_of("/\\");
	return  file.substr(found + 1);
}


inline string get_file_name_no_extension(const std::string& file) {
	string file_name = get_file_name(file);
	const std::size_t found = file_name.find_last_of(".");
	return  file_name.substr(0, found - 1);

}
