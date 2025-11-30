#include "WeatherBot.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

WeatherBot::WeatherBot(const std::string& apiKey) 
    : weatherService_(std::make_unique<WeatherService>(apiKey)),
      notificationManager_(std::make_unique<NotificationManager>()),
      running_(true) {
}

WeatherBot::~WeatherBot() {
}

std::string WeatherBot::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> WeatherBot::splitCommand(const std::string& command) {
    std::vector<std::string> tokens;
    std::istringstream iss(command);
    std::string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    return tokens;
}

void WeatherBot::showWelcome() {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════╗\n";
    std::cout << "║                                                       ║\n";
    std::cout << "║          🌤️  WEATHER FORECAST CHATBOT 🌤️            ║\n";
    std::cout << "║                                                       ║\n";
    std::cout << "║     Get instant weather information for any city!    ║\n";
    std::cout << "║                                                       ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════╝\n";
    std::cout << "\n";
    notificationManager_->showNotification("Welcome! Type 'help' to see available commands.", NotificationType::INFO);
}

void WeatherBot::showHelp() {
    std::cout << "\n═══════════════════════════════════════════════════════\n";
    std::cout << "                    COMMAND HELP                        \n";
    std::cout << "═══════════════════════════════════════════════════════\n";
    std::cout << "  Commands:\n";
    std::cout << "    weather <city>          - Get weather for a city\n";
    std::cout << "    location <lat> <lon>    - Get weather by coordinates\n";
    std::cout << "    help                    - Show this help message\n";
    std::cout << "    notifications           - View notification history\n";
    std::cout << "    clear                   - Clear notifications\n";
    std::cout << "    exit / quit             - Exit the application\n";
    std::cout << "\n  Examples:\n";
    std::cout << "    weather London\n";
    std::cout << "    weather New York\n";
    std::cout << "    location 51.5074 -0.1278\n";
    std::cout << "═══════════════════════════════════════════════════════\n\n";
}

void WeatherBot::handleWeatherQuery(const std::string& city) {
    if (city.empty()) {
        notificationManager_->showNotification("Please provide a city name. Usage: weather <city>", NotificationType::WARNING);
        return;
    }
    
    notificationManager_->showNotification("Fetching weather data for " + city + "...", NotificationType::INFO);
    
    WeatherData data = weatherService_->getWeatherByCity(city);
    
    if (data.isValid) {
        std::cout << weatherService_->formatWeatherReport(data);
        notificationManager_->showNotification("Weather data retrieved successfully!", NotificationType::SUCCESS);
        
        // Show weather alerts for extreme conditions
        if (data.temperature < 0) {
            notificationManager_->showWeatherAlert(data.city, "Freezing temperatures!");
        } else if (data.temperature > 35) {
            notificationManager_->showWeatherAlert(data.city, "Very hot weather!");
        }
        
        if (data.windSpeed > 15) {
            notificationManager_->showWeatherAlert(data.city, "Strong winds detected!");
        }
    } else {
        notificationManager_->showNotification("Failed to retrieve weather data. Please check the city name and try again.", NotificationType::ERROR);
    }
}

void WeatherBot::handleLocationQuery(const std::string& lat, const std::string& lon) {
    try {
        double latitude = std::stod(lat);
        double longitude = std::stod(lon);
        
        notificationManager_->showNotification("Fetching weather data for coordinates...", NotificationType::INFO);
        
        WeatherData data = weatherService_->getWeatherByCoordinates(latitude, longitude);
        
        if (data.isValid) {
            std::cout << weatherService_->formatWeatherReport(data);
            notificationManager_->showNotification("Weather data retrieved successfully!", NotificationType::SUCCESS);
        } else {
            notificationManager_->showNotification("Failed to retrieve weather data for the given coordinates.", NotificationType::ERROR);
        }
    } catch (const std::exception& e) {
        notificationManager_->showNotification("Invalid coordinates. Please provide valid latitude and longitude.", NotificationType::ERROR);
    }
}

void WeatherBot::handleHelpCommand() {
    showHelp();
}

void WeatherBot::handleExitCommand() {
    notificationManager_->showNotification("Thank you for using Weather Bot! Goodbye!", NotificationType::INFO);
    running_ = false;
}

void WeatherBot::processCommand(const std::string& command) {
    std::string trimmed = trim(command);
    if (trimmed.empty()) {
        return;
    }
    
    std::vector<std::string> tokens = splitCommand(trimmed);
    std::string cmd = tokens.empty() ? "" : tokens[0];
    
    // Convert to lowercase
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    if (cmd == "weather" || cmd == "w") {
        if (tokens.size() < 2) {
            notificationManager_->showNotification("Please provide a city name. Usage: weather <city>", NotificationType::WARNING);
        } else {
            std::string city;
            for (size_t i = 1; i < tokens.size(); ++i) {
                if (i > 1) city += " ";
                city += tokens[i];
            }
            handleWeatherQuery(city);
        }
    } else if (cmd == "location" || cmd == "loc") {
        if (tokens.size() < 3) {
            notificationManager_->showNotification("Please provide latitude and longitude. Usage: location <lat> <lon>", NotificationType::WARNING);
        } else {
            handleLocationQuery(tokens[1], tokens[2]);
        }
    } else if (cmd == "help" || cmd == "h") {
        handleHelpCommand();
    } else if (cmd == "notifications" || cmd == "notif") {
        notificationManager_->displayNotifications();
    } else if (cmd == "clear") {
        notificationManager_->clearNotifications();
    } else if (cmd == "exit" || cmd == "quit" || cmd == "q") {
        handleExitCommand();
    } else {
        notificationManager_->showNotification("Unknown command. Type 'help' to see available commands.", NotificationType::WARNING);
    }
}

void WeatherBot::start() {
    showWelcome();
    showHelp();
    
    std::string input;
    while (running_) {
        std::cout << "\nWeatherBot> ";
        std::getline(std::cin, input);
        
        if (!input.empty()) {
            processCommand(input);
        }
    }
}

