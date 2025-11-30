# Weather Forecast Chatbot

A C++ chatbot application that provides quick access to meteorological data and convenient user notifications within a single application.

## Features

- 🌤️ **Real-time Weather Data**: Get current weather information for any city worldwide
- 📍 **Location-based Queries**: Query weather by city name or GPS coordinates
- 🔔 **Smart Notifications**: Receive alerts for extreme weather conditions
- 💬 **Interactive Chat Interface**: User-friendly command-line interface
- 📊 **Detailed Weather Reports**: Comprehensive meteorological data display

## Requirements

- CMake 3.15 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- libcurl (for HTTP requests)
- nlohmann/json (automatically fetched via CMake)

### Installing Dependencies

#### Windows (using vcpkg)
```bash
vcpkg install curl
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libcurl4-openssl-dev
```

#### macOS
```bash
brew install curl
```

## Building the Project

1. Clone or navigate to the project directory:
```bash
cd "project weather bot"
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Configure and build with CMake:
```bash
cmake ..
cmake --build .
```

4. On Windows (Visual Studio):
```bash
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

## Configuration

### API Key Setup

You need an OpenWeatherMap API key to use this application:

1. Sign up for a free API key at: https://openweathermap.org/api
2. The application will prompt you for the API key on first run
3. The key will be saved in `api_key.txt` for future use

Alternatively, create a file named `api_key.txt` in the project root with your API key.

## Usage

Run the executable:
```bash
./WeatherBot    # Linux/macOS
WeatherBot.exe  # Windows
```

### Available Commands

- `weather <city>` - Get weather forecast for a city
  - Example: `weather London`
  - Example: `weather New York`

- `location <latitude> <longitude>` - Get weather by coordinates
  - Example: `location 51.5074 -0.1278`

- `help` - Display help message with all commands

- `notifications` - View notification history

- `clear` - Clear all notifications

- `exit` or `quit` - Exit the application

### Example Session

```
WeatherBot> weather Tokyo
[i] Fetching weather data for Tokyo...
╔════════════════════════════════════════╗
║        WEATHER FORECAST REPORT        ║
╠════════════════════════════════════════╣
║ Location: Tokyo, JP                    ║
║ Condition: clear sky                   ║
║ Temperature: 22°C                     ║
║ Feels Like: 21°C                      ║
║ Humidity: 65%                         ║
║ Wind Speed: 5 m/s                     ║
╚════════════════════════════════════════╝
[✓] Weather data retrieved successfully!
```

## Project Structure

```
project weather bot/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── include/                # Header files
│   ├── WeatherBot.h
│   ├── WeatherService.h
│   └── NotificationManager.h
└── src/                    # Source files
    ├── main.cpp
    ├── WeatherBot.cpp
    ├── WeatherService.cpp
    └── NotificationManager.cpp
```

## Architecture

- **WeatherBot**: Main chatbot class handling user interaction and command processing
- **WeatherService**: Handles API communication with OpenWeatherMap
- **NotificationManager**: Manages user notifications and alerts

## License

This project is provided as-is for educational purposes.

## Support

For issues or questions, please check:
- OpenWeatherMap API documentation: https://openweathermap.org/api
- CMake documentation: https://cmake.org/documentation/

