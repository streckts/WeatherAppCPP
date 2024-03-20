#include <iostream>
#include <curl/curl.h>
#include <string>
#include <ctime>

// Include the header file for the declaration
#include "weather.h"
#include "../lib/json.hpp"

using json = nlohmann::json;

// Callback to process API response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch weather data
void fetchWeatherData(double lat, double lon, const std::string& apiKey) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // Current Unix timestamp 
    auto now = std::time(nullptr);

    std::string url = "https://api.openweathermap.org/data/3.0/onecall/timemachine";
    url += "?lat=" + std::to_string(lat) + "&lon=" + std::to_string(lon);
    url += "&dt=" + std::to_string(now) + "&appid=" + apiKey;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Make the request
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Weather data: " << readBuffer << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}


Coordinates getCoordinates(const std::string& city, const std::string& state, const std::string& country, const std::string& apiKey) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    Coordinates coords = {0, 0}; 

    std::string url = "http://api.openweathermap.org/geo/1.0/direct?q=" + city + "," + state + "," + country + "&limit=1&appid=" + apiKey;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse JSON and extract coordinates
            auto jsonResponse = json::parse(readBuffer);
            if(!jsonResponse.empty()) {
                coords.latitude = jsonResponse[0]["lat"];
                coords.longitude = jsonResponse[0]["lon"];
            }
        }
        curl_easy_cleanup(curl);
    }
    return coords;
}