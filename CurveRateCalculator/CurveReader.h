#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int parse_curves(const string &curve_file,
                string &curve_type, 
                vector<double> & Ts, 
                vector<double> & rates,
                int &num_years);

// issue 1: dynamically allocate memories(not sure len of data)
// solution: read file len before reading data 