#ifndef WEATHER_BOT_H
#define WEATHER_BOT_H

#include <string>
#include <memory>
#include "WeatherService.h"
#include "NotificationManager.h"

class WeatherBot {
public:
    WeatherBot(const std::string& apiKey);
    ~WeatherBot();
    
    void start();
    void processCommand(const std::string& command);
    void showHelp();
    void showWelcome();
    
private:
    std::unique_ptr<WeatherService> weatherService_;
    std::unique_ptr<NotificationManager> notificationManager_;
    bool running_;
    
    void handleWeatherQuery(const std::string& city);
    void handleLocationQuery(const std::string& lat, const std::string& lon);
    void handleHelpCommand();
    void handleExitCommand();
    std::string trim(const std::string& str);
    std::vector<std::string> splitCommand(const std::string& command);
};

#endif // WEATHER_BOT_H

