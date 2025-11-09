#include "OutfitAdvisor.hpp"
#include <iostream>
using namespace std;

void OutfitAdvisor::giveAdvice(const WeatherAnalyzer& weather) {
    cout << "\n--- Bot's advice ---" << endl;
    cout << weather.getConditionAdvice() << endl;
    cout << weather.getTemperatureAdvice() << endl;
    cout << weather.getHumidityAdvice() << endl;
    cout << "\nHave a nice day! :)" << endl;
}
