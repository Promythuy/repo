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
    WeatherAnalyzer(double temp, int hum, string cond);
    string getConditionAdvice() const;
    string getTemperatureAdvice() const;
    string getHumidityAdvice() const;
};

#endif
