cmake_minimum_required(VERSION 3.20)
project(weather_bot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исходники
add_executable(weather_bot
    main.cpp
    WeatherAnalyzer.cpp
    OutfitAdvisor.cpp
)

# Для Windows можно подключить WinHTTP, если используем API
if(WIN32)
    target_link_libraries(weather_bot
        winhttp
    )
endif()
