#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>

enum class NotificationType {
    INFO,
    WARNING,
    ERROR,
    SUCCESS
};

struct Notification {
    std::string message;
    NotificationType type;
    std::chrono::system_clock::time_point timestamp;
};

class NotificationManager {
public:
    NotificationManager();
    ~NotificationManager();
    
    void showNotification(const std::string& message, NotificationType type = NotificationType::INFO);
    void showWeatherAlert(const std::string& city, const std::string& condition);
    void displayNotifications();
    void clearNotifications();
    
private:
    std::vector<Notification> notifications_;
    std::string getNotificationSymbol(NotificationType type);
    std::string getNotificationColor(NotificationType type);
    void printColored(const std::string& text, const std::string& color);
};

#endif // NOTIFICATION_MANAGER_H

