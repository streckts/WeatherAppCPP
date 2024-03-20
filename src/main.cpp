#include <iostream>
#include "weather.h"
#include "../lib/json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // Check for API key
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <API_KEY>" << std::endl;
        return 1; // Exit if the API key is not provided
    }

    std::string apiKey = argv[1]; // Assign the API key to a variable
    std::cout << "Using API Key: " << apiKey << std::endl;

    string city, state, country;

    cout << "Enter a city: ";
    getline(cin, city);
    cout << "Enter the state code (ISO 3166-2, e.g. 'CA' for California): ";
    getline(cin, state);
    cout << "Enter the country code (ISO 3166-2 e.g.v'US' for the United States): ";
    getline(cin, country);

    // Assume getCoordinates is defined and implemented as discussed
    Coordinates coords = getCoordinates(city, state, country, apiKey);

    // retrieve data
    auto parsedJSON = json::parse(fetchWeatherData(coords.latitude, coords.longitude, apiKey));

    double tempKelvin = parsedJSON["data"][0]["temp"];
    std::string description = parsedJSON["data"][0]["weather"][0]["description"];

    std::cout << "The weather in " << city << " is " << parsedJSON["data"][0]["weather"][0]["description"];
    //std::cout << "The temperature is approximately " << std::to_string(parsedJSON["data"][0]["temp"]).get<double>();

    return 0;
}

// USE g++ -o weather main.cpp weather.cpp -I../include -lcurl -std=c++17 TO COMPILE
// RUN ./weather "api_key_here"