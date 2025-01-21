#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

// Function to calculate discount rate from spot rate
double disc_rate(bool is_discrete, const double spot_rate, const double T);

// Function to calculate forward rate from rates at two times
double fwd_rate(bool is_discrete, const double rate0, const double rate1, const double T);

// Function to calculate spot rate from discount rate
double disc_spot_rate(bool is_discrete, const double disc_rate, const double T);

// Function to calculate spot rate from forward rate and previous spot rate
double fwd_spot_rate(bool is_discrete, const double fwd, const double prev_spot, const double T);

// Function to calculate missing rates (forward, discount, spot) based on input type
int calculate_rate(
    std::unordered_map<std::string, std::vector<double>> &curves_discrete,
    std::unordered_map<std::string, std::vector<double>> &curves_continuous,
    std::string &curve_type, 
    std::vector<double> &Ts, 
    const int num_years);