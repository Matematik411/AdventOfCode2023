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
    filename = "inputs/16.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > data;

    int H, W;
    while (getline(inputFile, line)) {
        data.push_back(line);
    }
    inputFile.close();
    H = data.size();
    W = data[0].size();


    map<pair<int, int>, vector<int>> present;
    vector<vector<int>> active;

    vector<pair<int, int>> dirs;
    dirs.push_back({1, 0});
    dirs.push_back({0, 1});
    dirs.push_back({-1, 0});
    dirs.push_back({0, -1});


    vector<int> laser, already;
    int x, y, d, possible; 
    char symbol;

    // H = W
    int solA, solB = 0, nrActive;
    for (int startDir = 0; startDir < 4; startDir++) {
        for (int step = 0; step < H; step++) {
            x = -dirs[startDir].first;
            y = -dirs[startDir].second;

            if ((startDir % 2) == 0) {
                y = step;
            }
            else {
                x = step;
            }
            if (startDir == 2) {
                x += (W-1);
            }
            if (startDir == 3) {
                y += (H-1);
            }

            
            active.push_back({x, y, startDir});
            present = {};
            while (active.size()) {
                laser = active[0];
                active.erase(active.begin());
                x = laser[0];
                y = laser[1];
                d = laser[2];


                x = x + dirs[d].first;
                y = y + dirs[d].second;
                if ((x < 0) || (y < 0) || (x >= W) || (y >= H)) {
                    continue;
                }
                symbol = data[y][x];

                if (symbol == '.') {
                    already = present[{x, y}];
                    if ( find(already.begin(), already.end(), d) == already.end() ) {
                        present[{x, y}].push_back(d);
                        active.push_back({x, y, d});
                    }
                }
                else if (symbol == '\\') {
                    if (d == 0) {
                        d = 1;
                    }
                    else if (d == 1) {
                        d = 0;
                    }
                    else if (d == 2) {
                        d = 3;
                    }
                    else if (d == 3) {
                        d = 2;
                    }

                    already = present[{x, y}];
                    if ( find(already.begin(), already.end(), d) == already.end() ) {
                        present[{x, y}].push_back(d);
                        active.push_back({x, y, d});
                    }
                }
                else if (symbol == '/') {
                    if (d == 0) {
                        d = 3;
                    }
                    else if (d == 1) {
                        d = 2;
                    }
                    else if (d == 2) {
                        d = 1;
                    }
                    else if (d == 3) {
                        d = 0;
                    }

                    already = present[{x, y}];
                    if ( find(already.begin(), already.end(), d) == already.end() ) {
                        present[{x, y}].push_back(d);
                        active.push_back({x, y, d});
                    }
                }
                else if (symbol == '|') {
                    if ((d == 1) || (d == 3)) {
                        already = present[{x, y}];
                        if ( find(already.begin(), already.end(), d) == already.end() ) {
                            present[{x, y}].push_back(d);
                            active.push_back({x, y, d});
                        }
                    }
                    if ((d == 0) || (d == 2)) {
                        for (int dSplit = 1; dSplit < 4; dSplit+=2) {
                            already = present[{x, y}];
                            if ( find(already.begin(), already.end(), dSplit) == already.end() ) {
                                present[{x, y}].push_back(dSplit);
                                active.push_back({x, y, dSplit});
                            }
                        }
                    }
                }
                else if (symbol == '-') {
                    if ((d == 0) || (d == 2)) {
                        already = present[{x, y}];
                        if ( find(already.begin(), already.end(), d) == already.end() ) {
                            present[{x, y}].push_back(d);
                            active.push_back({x, y, d});
                        }
                    }
                    if ((d == 1) || (d == 3)) {
                        for (int dSplit = 0; dSplit < 4; dSplit+=2) {
                            already = present[{x, y}];
                            if ( find(already.begin(), already.end(), dSplit) == already.end() ) {
                                present[{x, y}].push_back(dSplit);
                                active.push_back({x, y, dSplit});
                            }
                        }
                    }
                }
                else {
                    cout << "error at " << x << " " << y  << symbol << endl;
                }

            
            }

            nrActive = 0;
            for (int j = 0; j < H; j++) {
                for (int i = 0; i < W; i++) {
                    if (present[{i, j}].size()) {
                        nrActive += 1;
                    }
                }
            }
            if (nrActive > solB) {
                solB = nrActive;
            }
            if ((startDir == 0) && (step == 0)) {
                solA = nrActive;
            }

        }
    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;


    return 0;
}