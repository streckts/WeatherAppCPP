#include <iostream>
#include <curl/curl.h>
#include <string>
#include <ctime>

// Include the header file for the declaration
#include "weather.h"

// Callback to process API response
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to fetch weather data
void fetchWeatherData() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    // Temp hardcoded coordinates
    double lat = 42.3601;
    double lon = -71.0589;
    // Current Unix time stamp
    auto now = std::time(nullptr);

    std::string url = "https://api.openweathermap.org/data/3.0/onecall/timemachine";
    url += "?lat=" + std::to_string(lat) + "&lon=" + std::to_string(lon);
    url += "&dt=" + std::to_string(now) + "&appid=dc7097b3d067d48b9ffc0965341d49b8";

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