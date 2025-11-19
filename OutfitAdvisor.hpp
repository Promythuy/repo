<<<<<<< HEAD
#pragma once
#include <string>

class OutfitAdvisor {
public:
    static std::string recommend(double temp);
};
=======
#ifndef OUTFIT_ADVISOR_HPP
#define OUTFIT_ADVISOR_HPP

#include "WeatherAnalyzer.hpp"

class OutfitAdvisor {
public:
    static void giveAdvice(const WeatherAnalyzer& weather);
};

#endif
>>>>>>> acdf2e35dc21d2503e78f5494348323aeeedc7c3
