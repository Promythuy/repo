#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h> // библиотека для парсинга JSON
#include "WeatherAnalyzer.hpp"
#include "OutfitAdvisor.hpp"

using namespace std;

// Буфер для записи ответа cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

// Функция получения погоды через API
bool getWeatherFromAPI(const string& city, double& temperature, int& humidity, string& condition) {
    string apiKey = "0412b68a092f85a0032917b6ec7354c4";
    string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";

    CURL* curl = curl_easy_init();
    if (!curl) return false;

    string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) return false;

    // Парсим JSON
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    string errs;
    istringstream s(response);
    if (!Json::parseFromStream(readerBuilder, s, &root, &errs)) return false;

    temperature = root["main"]["temp"].asDouble();
    humidity = root["main"]["humidity"].asInt();
    condition = root["weather"][0]["main"].asString(); // Clear, Rain, Snow, Clouds

    return true;
}

int main() {
    string city;
    cout << "Enter city: ";
    cin >> city;

    double temperature;
    int humidity;
    string condition;

    if (!getWeatherFromAPI(city, temperature, humidity, condition)) {
        cout << "Failed to get weather data from API." << endl;
        return 1;
    }

    cout << "Weather in " << city << ": " << temperature << "°C, " << humidity << "%, " << condition << endl;

    WeatherAnalyzer weather(temperature, humidity, condition);
    OutfitAdvisor::giveAdvice(weather);

    return 0;
}
