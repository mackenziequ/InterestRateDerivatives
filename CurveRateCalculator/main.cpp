#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include "CurveCalculator.h"
#include "CurveReader.h"

int main(int argc, const char*argv[]){
    if (argc != 2){
        cout << "Usage: " << argv[0];
        cout<<" <cruve data file>" << endl;
        return 1;
    }
    string curve_file = argv[1];
    string curve_type;
    vector<double> Ts;
    vector<double> rates;
    int num_years;

    if (parse_curves(curve_file, curve_type, Ts, rates, num_years) !=0 ){
        cerr << "Error parsing curve file" << endl;
        return 1;
    }

    cout << "Rate type: "<< curve_type << endl;
    for (int i = 0; i < num_years; i++){
        cout << Ts[i] << ", " << rates[i] << endl;
    }

    // create unordered map
    unordered_map<string, vector<double>> curves_discrete {
            {"spot", vector<double>(num_years, 0.0)},
            {"fwd", vector<double>(num_years, 0.0)},
            {"disc", vector<double>(num_years, 0.0)}};
    unordered_map<string, vector<double>> curves_continuous {
            {"spot", vector<double>(num_years, 0.0)},
            {"fwd", vector<double>(num_years, 0.0)},
            {"disc", vector<double>(num_years, 0.0)}};

    curves_discrete[curve_type] = rates;
    curves_continuous[curve_type] = rates;

    // calculate rates
    if (calculate_rate(curves_discrete, curves_continuous, curve_type, Ts, num_years) != 0){
        cerr << "Error calculating " << curve_type << endl;
        return 1;
    }

    // calculate additional rates
    unordered_map<string, vector<double>> fwds_continuous;
    unordered_map<string, vector<double>> fwds_discrete;
    for (int i =1; i<num_years; i++){
        string key = "fwd" + to_string(i) + "yr";
        fwds_discrete[key] = vector<double>(num_years, 0.0); 
        fwds_continuous[key] = vector<double>(num_years, 0.0); 
    }

    fwds_discrete["fwd1yr"] = curves_discrete["fwd"];
    fwds_continuous["fwd1yr"] = curves_continuous["fwd"];

    for (int period = 2; period < num_years; period++) {
        std::string key = "fwd" + std::to_string(period) + "yr";
        for (int start_year = 1; start_year + period <= num_years; start_year++) {
            int end_year = start_year + period;

            double product = 1.0;
            for (int k = start_year; k < end_year; k++) {
                product *= (1 + fwds_discrete["fwd1yr"][k]);
            }
            fwds_discrete[key][start_year] = pow(product, 1.0 / period) - 1;

            double sum = 0.0;
            for (int k = start_year; k < end_year; k++) {
                sum += fwds_continuous["fwd1yr"][k];
            }
            fwds_continuous[key][start_year] = sum / period;
        }
    }
    


    cout << "Discrete:" << endl;
    cout << "Year, spot, disc, fwd" << endl;
    for (int i = 0; i < num_years; i++){
        cout << Ts[i] << ", " << curves_discrete["spot"][i] << ", " 
            << curves_discrete["disc"][i] << ", " << curves_discrete["fwd"][i]<< endl;
    } 

    std::cout << "Discrete Forward Rates (Columnar):" << std::endl;

    // Print column headers
    std::cout << std::setw(8) << "Year";
    for (const auto &pair : fwds_discrete) {
        std::cout << std::setw(12) << pair.first;
    }
    std::cout << std::endl;

    // Print row data
    for (int row = 0; row < num_years; row++) {
        std::cout << std::setw(8) << (row + 1); // Row header (year)
        for (const auto &pair : fwds_discrete) {
            std::cout << std::setw(12) << pair.second[row];
        }
        std::cout << std::endl;
    }

    cout << "\nContinuous:" << endl;
    cout << "Year, spot, disc, fwd" << endl;
    for (int i = 0; i < num_years; i++){
        cout << Ts[i] << ", " << curves_continuous["spot"][i] << ", " 
            << curves_continuous["disc"][i] << ", " << curves_continuous["fwd"][i]<< endl;
    } 
    

    std::cout << "\nContinuous Forward Rates (Columnar):" << std::endl;

    // Print column headers
    std::cout << std::setw(8) << "Year";
    for (const auto &pair : fwds_continuous) {
        std::cout << std::setw(12) << pair.first;
    }
    std::cout << std::endl;

    // Print row data
    for (int row = 0; row < num_years; row++) {
        std::cout << std::setw(8) << (row + 1); // Row header (year)
        for (const auto &pair : fwds_continuous) {
            std::cout << std::setw(12) << pair.second[row];
        }
        std::cout << std::endl;
    }
    return 0;
}