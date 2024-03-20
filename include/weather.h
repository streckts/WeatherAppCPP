struct Coordinates {
    double latitude;
    double longitude;
};

void fetchWeatherData(double lat, double lon, const std::string&apiKey);

Coordinates getCoordinates(const std::string& city, const std::string& state, const std::string& country, const std::string&apiKey);