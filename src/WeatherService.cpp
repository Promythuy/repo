#include "WeatherService.h"
#include <iostream>
#include <sstream>
#include <iomanip>

WeatherService::WeatherService(const std::string& apiKey) : apiKey_(apiKey), curl_(nullptr) {
    initializeCurl();
}

WeatherService::~WeatherService() {
    if (curl_) {
        curl_easy_cleanup(curl_);
    }
}

void WeatherService::initializeCurl() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl_ = curl_easy_init();
    if (!curl_) {
        std::cerr << "Error: Failed to initialize CURL" << std::endl;
    }
}

size_t WeatherService::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t totalSize = size * nmemb;
    data->append((char*)contents, totalSize);
    return totalSize;
}

std::string WeatherService::performRequest(const std::string& url) {
    if (!curl_) {
        return "";
    }
    
    std::string response;
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
    
    CURLcode res = curl_easy_perform(curl_);
    
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        return "";
    }
    
    return response;
}

WeatherData WeatherService::parseWeatherJson(const nlohmann::json& json) {
    WeatherData data;
    data.isValid = false;
    
    try {
        if (json.contains("cod") && json["cod"] != 200) {
            return data;
        }
        
        if (json.contains("name")) {
            data.city = json["name"];
        }
        
        if (json.contains("sys") && json["sys"].contains("country")) {
            data.country = json["sys"]["country"];
        }
        
        if (json.contains("weather") && json["weather"].is_array() && !json["weather"].empty()) {
            data.description = json["weather"][0]["description"];
            if (json["weather"][0].contains("icon")) {
                data.icon = json["weather"][0]["icon"];
            }
        }
        
        if (json.contains("main")) {
            if (json["main"].contains("temp")) {
                data.temperature = json["main"]["temp"];
            }
            if (json["main"].contains("feels_like")) {
                data.feelsLike = json["main"]["feels_like"];
            }
            if (json["main"].contains("humidity")) {
                data.humidity = json["main"]["humidity"];
            }
        }
        
        if (json.contains("wind") && json["wind"].contains("speed")) {
            data.windSpeed = json["wind"]["speed"];
        }
        
        data.isValid = true;
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
    
    return data;
}

WeatherData WeatherService::getWeatherByCity(const std::string& cityName) {
    std::ostringstream url;
    url << "http://api.openweathermap.org/data/2.5/weather?q=" 
        << cityName 
        << "&appid=" << apiKey_ 
        << "&units=metric";
    
    std::string response = performRequest(url.str());
    
    if (response.empty()) {
        WeatherData data;
        data.isValid = false;
        return data;
    }
    
    try {
        nlohmann::json json = nlohmann::json::parse(response);
        return parseWeatherJson(json);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON response: " << e.what() << std::endl;
        WeatherData data;
        data.isValid = false;
        return data;
    }
}

WeatherData WeatherService::getWeatherByCoordinates(double latitude, double longitude) {
    std::ostringstream url;
    url << "http://api.openweathermap.org/data/2.5/weather?lat=" 
        << latitude 
        << "&lon=" << longitude
        << "&appid=" << apiKey_ 
        << "&units=metric";
    
    std::string response = performRequest(url.str());
    
    if (response.empty()) {
        WeatherData data;
        data.isValid = false;
        return data;
    }
    
    try {
        nlohmann::json json = nlohmann::json::parse(response);
        return parseWeatherJson(json);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON response: " << e.what() << std::endl;
        WeatherData data;
        data.isValid = false;
        return data;
    }
}

std::string WeatherService::formatWeatherReport(const WeatherData& data) {
    if (!data.isValid) {
        return "Error: Unable to retrieve weather data. Please check the city name or your API key.";
    }
    
    std::ostringstream report;
    report << "\n╔════════════════════════════════════════╗\n";
    report << "║        WEATHER FORECAST REPORT        ║\n";
    report << "╠════════════════════════════════════════╣\n";
    report << "║ Location: " << std::left << std::setw(26) << (data.city + ", " + data.country) << "║\n";
    report << "║ Condition: " << std::setw(25) << data.description << "║\n";
    report << "║ Temperature: " << std::setw(23) << (std::to_string(static_cast<int>(data.temperature)) + "°C") << "║\n";
    report << "║ Feels Like: " << std::setw(24) << (std::to_string(static_cast<int>(data.feelsLike)) + "°C") << "║\n";
    report << "║ Humidity: " << std::setw(26) << (std::to_string(static_cast<int>(data.humidity)) + "%") << "║\n";
    report << "║ Wind Speed: " << std::setw(23) << (std::to_string(static_cast<int>(data.windSpeed)) + " m/s") << "║\n";
    report << "╚════════════════════════════════════════╝\n";
    
    return report.str();
}

