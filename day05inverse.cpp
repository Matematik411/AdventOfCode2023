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

    // seeed to soil INVERSE
    getline(inputFile, line);
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> soilToSeed;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        soilToSeed[{data[0], data[2]}] = data[1] - data[0];
    }

    // soil to fertilizer INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> fertilizerToSoil;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        fertilizerToSoil[{data[0], data[2]}] = data[1] - data[0];
    }

    // fertilizer to water INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> waterToFertilizer;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        waterToFertilizer[{data[0], data[2]}] = data[1] - data[0];
    }

    // water to light INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> lightToWater;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        lightToWater[{data[0], data[2]}] = data[1] - data[0];
    }

    // light  to temperature INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> temperatureToLight;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        temperatureToLight[{data[0], data[2]}] = data[1] - data[0];
    }

    // temperature to humidity INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> humidityToTemperature;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        humidityToTemperature[{data[0], data[2]}] = data[1] - data[0];
    }

    // humidity to location INVERSE
    getline(inputFile, line);
    map<pair<long long int, long long int>, long long int> locationToHumidity;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        vector<long long int> data = split(line, ' ');
        locationToHumidity[{data[0], data[2]}] = data[1] - data[0];
    }

    long long int lowestLoc = 579439039;
    cout << "a: " << lowestLoc << endl;

    int found = 0;
    for (int loc = 0; loc < lowestLoc; loc++) {

        // humidity
        long long int humidity = -1; 
        for (auto const& [key, val] : locationToHumidity) {
            if ((loc >= key.first) && (loc < (key.first + key.second))) {
                humidity = loc + val;
            }
        }
        if (humidity == -1) {
            humidity = loc;
        }
        
        // temperature
        long long int temperature = -1; 
        for (auto const& [key, val] : humidityToTemperature) {
            if ((humidity >= key.first) && (humidity < (key.first + key.second))) {
                temperature = humidity + val;
            }
        }
        if (temperature == -1) {
            temperature = humidity;
        }

        // light
        long long int light = -1; 
        for (auto const& [key, val] : temperatureToLight) {
            if ((temperature >= key.first) && (temperature < (key.first + key.second))) {
                light = temperature + val;
            }
        }
        if (light == -1) {
            light = temperature;
        }

        // water
        long long int water = -1; 
        for (auto const& [key, val] : lightToWater) {
            if ((light >= key.first) && (light < (key.first + key.second))) {
                water = light + val;
            }
        }
        if (water == -1) {
            water = light;
        }

        // fertilizer
        long long int fertilizer = -1; 
        for (auto const& [key, val] : waterToFertilizer) {
            if ((water >= key.first) && (water < (key.first + key.second))) {
                fertilizer = water + val;
            }
        }
        if (fertilizer == -1) {
            fertilizer = water;
        }

        // soil
        long long int soil = -1; 
        for (auto const& [key, val] : fertilizerToSoil) {
            if ((fertilizer >= key.first) && (fertilizer < (key.first + key.second))) {
                soil = fertilizer + val;
            }
        }
        if (soil == -1) {
            soil = fertilizer;
        }

        // seed
        long long int seed = -1; 
        for (auto const& [key, val] : soilToSeed) {
            if ((soil >= key.first) && (soil < (key.first + key.second))) {
                seed = soil + val;
            }
        }
        if (seed == -1) {
            seed = soil;
        }

        for (int j = 0; j < (seeds.size() / 2); j++) {
            long long left = seeds[2*j];
            long long right = left + seeds[2*j + 1];


            if ((seed >= left) && (seed < right)) {
                cout << "b: " << loc << endl;
                found = 1;
            }
        }
        
        if (loc % 100000 == 0) {
            cout << loc << endl;
        }
        if (found) {
            break;
        }
    }



    inputFile.close();

    return 0;
}