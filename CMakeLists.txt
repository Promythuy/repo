cmake_minimum_required(VERSION 3.15)
project(WeatherBot VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler options
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Find required packages
find_package(CURL REQUIRED)
find_package(nlohmann_json QUIET)

# If nlohmann_json is not found, use FetchContent
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.2
    )
    FetchContent_MakeAvailable(json)
    set(JSON_LIB nlohmann_json::nlohmann_json)
else()
    set(JSON_LIB nlohmann_json::nlohmann_json)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/WeatherBot.cpp
    src/WeatherService.cpp
    src/NotificationManager.cpp
)

# Header files
set(HEADERS
    include/WeatherBot.h
    include/WeatherService.h
    include/NotificationManager.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries - use modern CMake target-based approach
if(TARGET CURL::libcurl)
    target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${JSON_LIB})

# Include directories for target
target_include_directories(${PROJECT_NAME} 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Installation (optional)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

