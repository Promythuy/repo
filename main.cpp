#include <iostream>
#include "WeatherAnalyzer.hpp"
#include "OutfitAdvisor.hpp"

int main() {
    std::string city;
    std::string apiKey = "0412b68a092f85a0032917b6ec7354c4";

    std::cout << "Введите город: ";
    std::cin >> city;

    double temp = WeatherAnalyzer::fetchTemperature(city, apiKey);

    std::cout << "Температура в " << city << ": " << temp << "°C\n";
    std::cout << OutfitAdvisor::recommend(temp) << std::endl;

    return 0;
}
