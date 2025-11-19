#include "OutfitAdvisor.hpp"
<<<<<<< HEAD

std::string OutfitAdvisor::recommend(double temp) {
    if (temp < -5) return "Очень холодно: теплая куртка, шапка, шарф.";
    if (temp < 5) return "Прохладно: куртка и свитер.";
    if (temp < 15) return "Немного прохладно: легкая куртка или худи.";
    if (temp < 25) return "Комфортно: футболка и джинсы.";
    return "Жарко: шорты и майка.";
=======
#include <iostream>
using namespace std;

void OutfitAdvisor::giveAdvice(const WeatherAnalyzer& weather) {
    cout << "\n--- Bot's advice ---" << endl;
    cout << weather.getConditionAdvice() << endl;
    cout << weather.getTemperatureAdvice() << endl;
    cout << weather.getHumidityAdvice() << endl;
    cout << "\nHave a nice day! :)" << endl;
>>>>>>> acdf2e35dc21d2503e78f5494348323aeeedc7c3
}
