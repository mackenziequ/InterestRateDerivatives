#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

#include "GraphGenerator.h"

void saveGraph(const std::string &filename, const std::vector<double> &x, const std::vector<double> &y, const std::string &title, const std::string &xlabel, const std::string &ylabel) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }

    outFile << "# " << title << "\n";
    for (size_t i = 0; i < x.size(); ++i) {
        outFile << x[i] << " " << y[i] << "\n";
    }
    outFile.close();

    std::string plotCommand = "gnuplot -e \"set terminal png; set output '";
    plotCommand += filename + ".png'; ";
    plotCommand += "set title '" + title + "'; ";
    plotCommand += "set xlabel '" + xlabel + "'; ";
    plotCommand += "set ylabel '" + ylabel + "'; ";
    plotCommand += "plot '" + filename + "' using 1:2 with lines title '";
    plotCommand += title + "'\"";
    system(plotCommand.c_str());
}

void generateSpotCurve(const std::string &outputPath, const std::vector<double> &years, const std::vector<double> &spotRates) {
    saveGraph(outputPath + "spot_curve", years, spotRates, "Spot Curve", "Years", "Spot Rate");
}

void generateForwardCurve(const std::string &outputPath, const std::vector<double> &years, const std::vector<double> &forwardRates) {
    saveGraph(outputPath + "forward_curve", years, forwardRates, "Forward Curve", "Years", "Forward Rate");
}
