#include <iostream>
#include "weather.h"

using namespace std;

int main() {
    // Placeholder for future city input and geolocation API integration
    //string city_name;
    //cout << "Enter a city: ";
    //getline(cin, city_name);

    // Directly call for now
    fetchWeatherData();

    return 0;
}

// USE "g++ -o program_name main.cpp weather.cpp -I./include -lcurl -std=c++17" TO COMPILE