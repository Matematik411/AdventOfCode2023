#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template <typename Out>
void split(const string &s, char delim, Out result) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, delim)) {
        *result++ = item;
    }
}

vector<long long int> split(const string &s, char delim) {
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));

    vector<long long int> final;
    for (long long int i = 0; i < elems.size(); i++) {
        long long int x = stoll( elems[i] );
        final.push_back(x);
    }
    return final;
}



int main() {
    string filename;
    filename = "inputs/05.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;

    getline(inputFile, line);
    line = line.substr(line.find(':') + 2);
    vector<long long int> seeds = split(line,  ' ');

    // seeed to soil
    getline(inputFile, line);
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> seedToSoil;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        seedToSoil[{data[1], data[2]}] = data[0] - data[1];
    }

    
    // soil to fertilizer
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> soilToFertilizer;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        soilToFertilizer[{data[1], data[2]}] = data[0] - data[1];
    }
    
    // fertilizer to water
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> fertilizerToWater;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        fertilizerToWater[{data[1], data[2]}] = data[0] - data[1];
    }
    
    // water to light
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> waterToLight;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        waterToLight[{data[1], data[2]}] = data[0] - data[1];
    }
    
    // light  to temperature
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> lightToTemperature;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        lightToTemperature[{data[1], data[2]}] = data[0] - data[1];
    }

    // temperature to humidity
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> temperatureToHumidity;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        temperatureToHumidity[{data[1], data[2]}] = data[0] - data[1];
    }

    // humidity to location
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> humidityToLocation;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        humidityToLocation[{data[1], data[2]}] = data[0] - data[1];
    }


    long long int lowestLoc = 999999999;
    for (long long int seed : seeds) {

        // soil
        long long int soil = -1; 
        for (auto const& [key, val] : seedToSoil) {
            if ((seed >= key.first) && (seed < (key.first + key.second))) {
                soil = seed + val;
            }
        }
        if (soil == -1) {
            soil = seed;
        }

        // fertilizer
        long long int fertilizer = -1; 
        for (auto const& [key, val] : soilToFertilizer) {
            if ((soil >= key.first) && (soil < (key.first + key.second))) {
                fertilizer = soil + val;
            }
        }
        if (fertilizer == -1) {
            fertilizer = soil;
        }

        // water
        long long int water = -1; 
        for (auto const& [key, val] : fertilizerToWater) {
            if ((fertilizer >= key.first) && (fertilizer < (key.first + key.second))) {
                water = fertilizer + val;
            }
        }
        if (water == -1) {
            water = fertilizer;
        }

        // light
        long long int light = -1; 
        for (auto const& [key, val] : waterToLight) {
            if ((water >= key.first) && (water < (key.first + key.second))) {
                light = water + val;
            }
        }
        if (light == -1) {
            light = water;
        }

        // temperature
        long long int temperature = -1; 
        for (auto const& [key, val] : lightToTemperature) {
            if ((light >= key.first) && (light < (key.first + key.second))) {
                temperature = light + val;
            }
        }
        if (temperature == -1) {
            temperature = light;
        }

        // humidity
        long long int humidity = -1; 
        for (auto const& [key, val] : temperatureToHumidity) {
            if ((temperature >= key.first) && (temperature < (key.first + key.second))) {
                humidity = temperature + val;
            }
        }
        if (humidity == -1) {
            humidity = temperature;
        }

        // location
        long long int location = -1; 
        for (auto const& [key, val] : humidityToLocation) {
            if ((humidity >= key.first) && (humidity < (key.first + key.second))) {
                location = humidity + val;
            }
        }
        if (location == -1) {
            location = humidity;
        }

        if (location < lowestLoc) {
            lowestLoc = location;
        }
    }

    cout << "a: " << lowestLoc << endl;



    inputFile.close();

    return 0;
}