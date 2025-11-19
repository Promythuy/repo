<<<<<<< HEAD
#pragma once
#include <string>

class WeatherAnalyzer {
public:
    static double fetchTemperature(const std::string& city, const std::string& apiKey);
};
=======
#ifndef WEATHER_ANALYZER_HPP
#define WEATHER_ANALYZER_HPP

#include <string>
using namespace std;

class WeatherAnalyzer {
private:
    double temperature;
    int humidity;
    string condition;

public:
    WeatherAnalyzer();
    WeatherAnalyzer(double temp, int hum, string cond);
    string getConditionAdvice() const;
    string getTemperatureAdvice() const;
    string getHumidityAdvice() const;
};

#endif
>>>>>>> acdf2e35dc21d2503e78f5494348323aeeedc7c3
