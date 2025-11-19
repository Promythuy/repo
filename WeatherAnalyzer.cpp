#include "WeatherAnalyzer.hpp"
<<<<<<< HEAD
#include <windows.h>
#include <winhttp.h>
#include <string>
#include <iostream>
#include <sstream>
#pragma comment(lib, "winhttp.lib")

// простая функция для получения температуры из JSON
double extractTemperature(const std::string& json) {
    size_t pos = json.find("\"temp\":");
    if (pos == std::string::npos) return 0.0;

    pos += 7;
    return std::stod(json.substr(pos, json.find(",", pos) - pos));
}

double WeatherAnalyzer::fetchTemperature(const std::string& city, const std::string& apiKey) {
    std::wstring host = L"api.openweathermap.org";
    std::wstring path = L"/data/2.5/weather?q=" +
        std::wstring(city.begin(), city.end()) +
        L"&units=metric&appid=" +
        std::wstring(apiKey.begin(), apiKey.end());

    HINTERNET hSession = WinHttpOpen(L"WeatherBot/1.0",
                                     WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                     NULL, NULL, 0);

    if (!hSession) return 0.0;

    HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
    if (!hConnect) { WinHttpCloseHandle(hSession); return 0.0; }

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect, L"GET", path.c_str(),
        NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
    );

    if (!hRequest) { 
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 0.0; 
    }

    BOOL sent = WinHttpSendRequest(
        hRequest,
        WINHTTP_NO_ADDITIONAL_HEADERS, 0,
        NULL, 0,
        0, 0
    );

    if (!sent) { 
        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        return 0.0;
    }

    WinHttpReceiveResponse(hRequest, NULL);

    DWORD size = 0;
    std::string result;

    do {
        WinHttpQueryDataAvailable(hRequest, &size);
        if (size == 0) break;

        char* buffer = new char[size + 1];
        ZeroMemory(buffer, size + 1);

        DWORD downloaded = 0;
        WinHttpReadData(hRequest, buffer, size, &downloaded);

        result.append(buffer, downloaded);
        delete[] buffer;
    } while (size > 0);

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);

    return extractTemperature(result);
=======

WeatherAnalyzer::WeatherAnalyzer(double temp, int hum, string cond)
    : temperature(temp), humidity(hum), condition(cond) {
}

string WeatherAnalyzer::getConditionAdvice() const {
    if (condition == "rainy")
        return "Take an umbrella and wear waterproof shoes.";
    else if (condition == "snowy")
        return "Wear warm boots, a hat and gloves.";
    else if (condition == "sunny")
        return "Don't forget sunglasses and a cap.";
    else if (condition == "cloudy")
        return "A light jacket will be perfect.";
    else
        return "I don�t recognize this weather condition.";
}

string WeatherAnalyzer::getTemperatureAdvice() const {
    if (temperature < 0)
        return "It�s freezing! Dress very warmly.";
    else if (temperature < 10)
        return "Wear a warm coat.";
    else if (temperature < 20)
        return "A light jacket should be fine.";
    else if (temperature < 30)
        return "You can wear something light and comfortable.";
    else
        return "It�s very hot! Don�t forget water and sunscreen.";
}

string WeatherAnalyzer::getHumidityAdvice() const {
    if (humidity > 80)
        return "Humidity is high � it might feel warmer than it is.";
    else if (humidity < 30)
        return "The air is dry � stay hydrated.";
    else
        return "Humidity level is comfortable.";
>>>>>>> acdf2e35dc21d2503e78f5494348323aeeedc7c3
}
