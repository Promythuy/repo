#include "OutfitAdvisor.hpp"

std::string OutfitAdvisor::recommend(double temp) {
    if (temp < -5) return "Очень холодно: теплая куртка, шапка, шарф.";
    if (temp < 5) return "Прохладно: куртка и свитер.";
    if (temp < 15) return "Немного прохладно: легкая куртка или худи.";
    if (temp < 25) return "Комфортно: футболка и джинсы.";
    return "Жарко: шорты и майка.";
}
