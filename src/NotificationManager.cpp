#include "NotificationManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

NotificationManager::NotificationManager() {
}

NotificationManager::~NotificationManager() {
}

void NotificationManager::printColored(const std::string& text, const std::string& color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCode = 7; // Default white
    
    if (color == "green") colorCode = 10;
    else if (color == "yellow") colorCode = 14;
    else if (color == "red") colorCode = 12;
    else if (color == "blue") colorCode = 11;
    else if (color == "cyan") colorCode = 11;
    
    SetConsoleTextAttribute(hConsole, colorCode);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 7); // Reset to default
#else
    std::cout << text;
#endif
}

std::string NotificationManager::getNotificationSymbol(NotificationType type) {
    switch (type) {
        case NotificationType::INFO:
            return "[i]";
        case NotificationType::WARNING:
            return "[!]";
        case NotificationType::ERROR:
            return "[X]";
        case NotificationType::SUCCESS:
            return "[✓]";
        default:
            return "[*]";
    }
}

std::string NotificationManager::getNotificationColor(NotificationType type) {
    switch (type) {
        case NotificationType::INFO:
            return "blue";
        case NotificationType::WARNING:
            return "yellow";
        case NotificationType::ERROR:
            return "red";
        case NotificationType::SUCCESS:
            return "green";
        default:
            return "cyan";
    }
}

void NotificationManager::showNotification(const std::string& message, NotificationType type) {
    Notification notif;
    notif.message = message;
    notif.type = type;
    notif.timestamp = std::chrono::system_clock::now();
    
    notifications_.push_back(notif);
    
    // Display immediately
    std::string symbol = getNotificationSymbol(type);
    std::string color = getNotificationColor(type);
    
    printColored(symbol + " ", color);
    std::cout << message << std::endl;
}

void NotificationManager::showWeatherAlert(const std::string& city, const std::string& condition) {
    std::ostringstream alert;
    alert << "Weather Alert for " << city << ": " << condition;
    showNotification(alert.str(), NotificationType::WARNING);
}

void NotificationManager::displayNotifications() {
    if (notifications_.empty()) {
        std::cout << "No notifications." << std::endl;
        return;
    }
    
    std::cout << "\n═══════════════════════════════════════\n";
    std::cout << "         NOTIFICATION HISTORY          \n";
    std::cout << "═══════════════════════════════════════\n";
    
    for (const auto& notif : notifications_) {
        auto time = std::chrono::system_clock::to_time_t(notif.timestamp);
        std::tm* timeinfo = std::localtime(&time);
        
        std::cout << "[" << std::put_time(timeinfo, "%H:%M:%S") << "] ";
        
        std::string symbol = getNotificationSymbol(notif.type);
        std::string color = getNotificationColor(notif.type);
        
        printColored(symbol + " ", color);
        std::cout << notif.message << std::endl;
    }
    
    std::cout << "═══════════════════════════════════════\n" << std::endl;
}

void NotificationManager::clearNotifications() {
    notifications_.clear();
    showNotification("All notifications cleared.", NotificationType::INFO);
}

