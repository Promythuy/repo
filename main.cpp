#include <iostream>
#include "WeatherAnalyzer.hpp"
#include "OutfitAdvisor.hpp"
using namespace std;

int main() {
    double temperature;
    int humidity;
    string condition;

    cout << "=== Weather Outfit Bot ===" << endl;
    cout << "Enter temperature (°C): ";
    cin >> temperature;

    cout << "Enter humidity (%): ";
    cin >> humidity;

    cout << "Enter condition (sunny, rainy, cloudy, snowy): ";
    cin >> condition;

    WeatherAnalyzer weather(temperature, humidity, condition);
    OutfitAdvisor::giveAdvice(weather);

    return 0;
}
