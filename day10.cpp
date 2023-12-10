#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
#include <algorithm>
using namespace std;


int main() {
    string filename;
    filename = "inputs/10.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > data;
    pair<int, int> animal;

    int j = 0, W, H;
    while (getline(inputFile, line)) {
        data.push_back(line);
        if (line.find('S') < line.size()) {
            animal = {line.find('S'), j};
        }
        j += 1;
    }
    inputFile.close();
    W = data[0].size();
    H = data.size();


    vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    map<char, vector<int>> parts;
    parts['|'] = {1, 3};
    parts['-'] = {0, 2};
    parts['L'] = {0, 3};
    parts['J'] = {2, 3};
    parts['7'] = {1, 2};
    parts['F'] = {0, 1};

    vector<pair<int, int>> cycle;
    cycle.push_back(animal);

    pair<int, int> position;
    position = animal;
    int move, x, y;
    char pipe, animalPipe;

    if (filename == "inputs/test.txt") {
        pipe = 'F';
        animalPipe = 'F';
        move = 3;
    }
    else {
        pipe = 'L';
        animalPipe = 'L';
        move = 1;
    }

    while (true) {

        x = position.first;
        y = position.second;
        move = (move + 2) % 4;

        if (move == parts[pipe][0]) {
            move = parts[pipe][1];
        }
        else {
            move = parts[pipe][0];
        }

        x = x + dirs[move].first;
        y = y + dirs[move].second;
        position = {x, y};

        if (position == animal) {
            break;
        }
        cycle.push_back(position);
        pipe = data[y][x];

    }
    std::cout << "a: " << cycle.size() / 2 << endl;

    int resB = 0, inside;
    pair<int, int> loc;
    vector<char> openings;
    char op, symbol;
    for (int y = 0; y < H; y++) {
        inside = 0;
        openings = {};
        for (int x = 0; x < W; x++) {
            loc = {x, y};
            
            auto it = find_if(
                cycle.begin(), 
                cycle.end(), 
                [&](const auto& pair) { return pair == loc ; });
            if (it != cycle.end()) {

                symbol = data[y][x];

                if (symbol == '|') { 
                    inside = 1 - inside;
                }
                else {
                    if (symbol == 'S') {
                        openings.push_back(animalPipe);
                    }
                    if (symbol == 'F') {
                        openings.push_back(symbol);
                    }
                    if (symbol == 'L') {
                        openings.push_back(symbol);
                    }
                    if (symbol == '7') {
                        op = openings[openings.size()-1];
                        openings.pop_back();
                        if (op == 'L') {
                            inside = 1 - inside;
                        }
                    }
                    if (symbol == 'J') {
                        op = openings[openings.size()-1];
                        openings.pop_back();
                        if (op == 'F') {
                            inside = 1 - inside;
                        }
                    }
                    
                }
            }
            else {
                resB += inside;
            }
            
        }
    }


    std::cout << "b: " << resB << endl;

    return 0;
}