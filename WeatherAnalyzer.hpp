#pragma once
#include <string>

class WeatherAnalyzer {
public:
    static double fetchTemperature(const std::string& city, const std::string& apiKey);
};
