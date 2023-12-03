#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <ctype.h>
#include <map>

using namespace std;

pair<pair<int, int>, int> checkAround(vector<string> grid, int i, int j) {
    int h = grid.size();
    int w = grid[0].size();


    pair<pair<int, int>, int> around = {{-1, -1}, 0};

    vector<int> DX = {-1, 0, 1};
    vector<int> DY = {-1, 0, 1};

    int x, y;
    char ch;
    for (int dx : DX) {
        for (int dy : DY) {
            x = i + dx;
            y = j + dy;

            if ((0 <= y) &&  (y <= (h-1)) && (0 <= x) && (x <= (w-1))) {
                ch = grid[y][x];
                if (ch != '.') {
                    if (not isdigit(ch)) {
                        around.first = {x, y};
                        around.second = 2;
                        if (ch == '*') {
                            around.second = 1;
                        }
                    }
                }
            }
        }
    }

    return around;
}




int main() {
    string filename;
    filename = "inputs/03.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > data;

    int h, w;
    while (getline(inputFile, line)) {
        data.push_back(line);
    }
    inputFile.close();
    h = data.size();
    w = data[0].size();


    string nr;
    int partNr = 0, solA = 0, symbol;
    pair<int, int> loc;
    pair<pair<int, int>, int> around;
    map<pair<int, int>, vector<int>> gears;

    for (int j = 0; j < h; j++) {
        string line = data[j];
        for (int i = 0; i < h; i++) {
            char x = line[i];
            if (isdigit(x)) {
                nr += x;
                around = checkAround(data, i, j); 
                if (around.second) {
                    partNr = 1;
                    symbol = around.second;
                    loc = around.first;
                }
            }
            else {
                if (nr.size()) {
                    if (partNr) {
                        solA += stoi( nr );
                    }
                    if (symbol == 1) {
                        gears[loc].push_back(stoi(nr));
                    }
                }

                nr = "";
                partNr = 0;
                symbol = -1;
            }


        }
        if (nr.size()) {
            if (partNr) {
                solA += stoi( nr );
            }
            if (symbol == 1) {
                gears[loc].push_back(stoi(nr));
            }
        }
        nr = "";
        partNr = 0;
        symbol = -1;
    }

    cout << "a: " << solA << endl;


    int solB = 0;
    for (auto const& [key, val] : gears) {
        if (val.size() == 2) {
            solB += val[0] * val[1];
        }
    }
    cout << "b: " << solB << endl;



    return 0;
}