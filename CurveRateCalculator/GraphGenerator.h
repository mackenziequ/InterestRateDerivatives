#pragma once

#include <string>
#include <vector>

void generateSpotCurve(const std::string &outputPath, const std::vector<double> &years, const std::vector<double> &spotRates);
void generateForwardCurve(const std::string &outputPath, const std::vector<double> &years, const std::vector<double> &forwardRates);

