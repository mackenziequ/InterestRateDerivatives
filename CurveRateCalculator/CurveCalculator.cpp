#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include "CurveCalculator.h"
#include "CurveReader.h"

using namespace std;

double disc_rate(bool is_discrete, const double spot_rate, const double T){
    if (is_discrete){
        return pow( 1+spot_rate, -T);
    }
    else{
        return exp(-spot_rate * T);
        }
}

double fwd_rate(bool is_discrete, const double rate0, const double rate1,const double T){
    if (T == 1){
        return 0.0;
    }
    else if (is_discrete){
        return rate0/rate1 -1;
    }
    else
        return (rate1 * T) - (rate0*(T-1));
}

double disc_spot_rate(bool is_discrete, const double disc_rate, const double T){
    if (is_discrete){
        return pow(disc_rate, -1/T) -1;
    }
    else{
        return -log(disc_rate)/T;
    }
}

double fwd_spot_rate(bool is_discrete, const double fwd, const double prev_spot, const double T){
    if (is_discrete){
        return pow(pow(prev_spot, T-1)* fwd, 1/T);
    }
    else{
        return (prev_spot*(T-1)+fwd)/T;
    }
}

int calculate_rate(unordered_map<string, vector<double>> &curves_discrete, 
    unordered_map<string, vector<double>> &curves_continuous, 
    string &curve_type, vector<double>&Ts, const int num_years){

    // if given spot
    if (curve_type == "spot"){
        for (int i = 0; i < num_years; i++){
            curves_discrete["disc"][i] = disc_rate(true, curves_discrete["spot"][i], Ts[i]);
            curves_continuous["disc"][i] =  disc_rate(false, curves_continuous["spot"][i], Ts[i]);

            curves_discrete["fwd"][i] = fwd_rate(true, curves_discrete["disc"][i-1], curves_discrete["disc"][i], Ts[i]);
            curves_continuous["fwd"][i] = fwd_rate(false, curves_discrete["spot"][i-1], curves_discrete["spot"][i], Ts[i]);
        }
    }

    // if given disc
    else if (curve_type == "disc"){
        for (int i = 0; i < num_years; i++){
            curves_discrete["spot"][i] = disc_spot_rate(true, curves_discrete["disc"][i], Ts[i]);
            curves_continuous["spot"][i] =  disc_spot_rate(false, curves_continuous["disc"][i], Ts[i]);

            curves_discrete["fwd"][i] = fwd_rate(true, curves_discrete["disc"][i-1], curves_discrete["disc"][i], Ts[i]);
            curves_continuous["fwd"][i] = fwd_rate(false, curves_continuous["spot"][i-1], curves_continuous["spot"][i], Ts[i]);
        }
    }

    // if given fwd
    else if (curve_type == "fwd"){
        for (int i = 0; i < num_years; i++){
            if (i == 0){
                curves_discrete["spot"][i] = curves_discrete["fwd"][i];
                curves_continuous["spot"][i] = curves_continuous["fwd"][i];
            }
            else{
                curves_discrete["spot"][i] = fwd_spot_rate(true,curves_discrete["fwd"][i],curves_discrete["spot"][i-1], Ts[i]);
                curves_continuous["spot"][i] =  fwd_spot_rate(false,curves_continuous["fwd"][i],curves_continuous["spot"][i-1], Ts[i]);
            }

            curves_discrete["disc"][i] = disc_rate(true, curves_discrete["spot"][i], Ts[i]);
            curves_continuous["disc"][i] =  disc_rate(false, curves_continuous["spot"][i], Ts[i]);
        }
    }

    return 0;
}



