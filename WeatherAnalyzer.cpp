#include "WeatherAnalyzer.hpp"

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
        return "I don’t recognize this weather condition.";
}

string WeatherAnalyzer::getTemperatureAdvice() const {
    if (temperature < 0)
        return "It’s freezing! Dress very warmly.";
    else if (temperature < 10)
        return "Wear a warm coat.";
    else if (temperature < 20)
        return "A light jacket should be fine.";
    else if (temperature < 30)
        return "You can wear something light and comfortable.";
    else
        return "It’s very hot! Don’t forget water and sunscreen.";
}

string WeatherAnalyzer::getHumidityAdvice() const {
    if (humidity > 80)
        return "Humidity is high — it might feel warmer than it is.";
    else if (humidity < 30)
        return "The air is dry — stay hydrated.";
    else
        return "Humidity level is comfortable.";
}
