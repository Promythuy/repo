#include "WeatherBot.h"
#include <iostream>
#include <string>
#include <fstream>

std::string getApiKey() {
    // Try to read from file first
    std::ifstream file("api_key.txt");
    if (file.is_open()) {
        std::string key;
        std::getline(file, key);
        file.close();
        if (!key.empty()) {
            return key;
        }
    }
    
    // If not found in file, prompt user
    std::string apiKey;
    std::cout << "Please enter your OpenWeatherMap API key: ";
    std::getline(std::cin, apiKey);
    
    // Optionally save to file for future use
    if (!apiKey.empty()) {
        std::ofstream outFile("api_key.txt");
        if (outFile.is_open()) {
            outFile << apiKey;
            outFile.close();
        }
    }
    
    return apiKey;
}

int main() {
    std::cout << "Initializing Weather Bot..." << std::endl;
    
    std::string apiKey = getApiKey();
    
    if (apiKey.empty()) {
        std::cerr << "Error: API key is required to use the weather service." << std::endl;
        std::cerr << "Please get your free API key from: https://openweathermap.org/api" << std::endl;
        return 1;
    }
    
    try {
        WeatherBot bot(apiKey);
        bot.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

