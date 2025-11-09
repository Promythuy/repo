#ifndef OUTFIT_ADVISOR_HPP
#define OUTFIT_ADVISOR_HPP

#include "WeatherAnalyzer.hpp"

class OutfitAdvisor {
public:
    static void giveAdvice(const WeatherAnalyzer& weather);
};

#endif
