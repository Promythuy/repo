#ifndef WEATHER_SERVICE_H
#define WEATHER_SERVICE_H

#include <string>
#include <memory>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

struct WeatherData {
    std::string city;
    std::string description;
    double temperature;
    double feelsLike;
    double humidity;
    double windSpeed;
    std::string country;
    std::string icon;
    bool isValid;
};

class WeatherService {
public:
    WeatherService(const std::string& apiKey);
    ~WeatherService();
    
    WeatherData getWeatherByCity(const std::string& cityName);
    WeatherData getWeatherByCoordinates(double latitude, double longitude);
    std::string formatWeatherReport(const WeatherData& data);
    
private:
    std::string apiKey_;
    CURL* curl_;
    
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data);
    std::string performRequest(const std::string& url);
    WeatherData parseWeatherJson(const nlohmann::json& json);
    void initializeCurl();
};

#endif // WEATHER_SERVICE_H

