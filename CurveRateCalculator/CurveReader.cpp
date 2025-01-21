#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "CurveReader.h"
using namespace std;

int parse_curves(const string &curve_file,
                string &curve_type, 
                vector<double> & Ts, 
                vector<double> & rates,
                int &num_years){

    ifstream infile(curve_file);
    if (!infile.is_open()){
        cerr << "Error opening file "<< curve_file << endl;
        return 1;
    }
    // find number of lines
    string line;
    int line_count = 0;
    while (getline(infile, line)){
        ++line_count;
    }

    if (line_count < 2){
        cerr << "Error: Insufficient data in file" << endl;
        return 1;
    }

    // allocate array mem
    num_years = line_count - 1;

    // clear
    infile.clear();
    infile.seekg(0, ios::beg);

    infile >> curve_type;

    // parce line
    double year, rate;
    while (infile >> year >> rate){
        Ts.push_back(year);
        rates.push_back(rate);
    }
    

    infile.close();
    return 0;
}

// issue 1: dynamically allocate memories(not sure len of data)
// solution: read file len before reading data 


