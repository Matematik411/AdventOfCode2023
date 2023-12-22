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


template <typename T, typename A>
int arg_max(std::vector<T, A> const& vec) {
  return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
}

template <typename Out>
void split(const string &s, char delim, Out result) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, delim)) {
        *result++ = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


int isItBelow(vector<int> moving, vector<int> other) {
    if (moving[2] <= other[5]) {
        return -1;
    }
    if (moving[0] == moving[3]) {
        for (int j = moving[1]; j <= moving[4]; j++) {
            if ((moving[0] >= other[0]) && (moving[0] <= other[3]) && (j >= other[1]) && (j <= other[4])) {
                // cout << "hjererer" << moving[2] << " -- " << other[5] << endl;
                return moving[2] - other[5] - 1;
            }
        }
    }
    if (moving[1] == moving[4]) {
        for (int i = moving[0]; i <= moving[3]; i++) {
            if ((i >= other[0]) && (i <= other[3]) && (moving[1] >= other[1]) && (moving[1] <= other[4])) {
                return moving[2] - other[5] - 1;
            }
        }
    }
    return -1;
}


int main() {
    string filename;
    filename = "inputs/22.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    // x1, y1, z1, ... x2, y2, z2, ... inFinalPos
    vector< vector<int> > bricks;
    vector<string> info, vals;

    int total = 0, areFinal = 0, inFinalPos;
    while (getline(inputFile, line)) {
        info = split(line, '~');
        vals = split(info[0], ',');
        bricks.push_back({});
        inFinalPos = 0;
        for (int i = 0; i<3; i++) {
            bricks[total].push_back(stoi(vals[i]));
            if (i == 2) {
                if (stoi(vals[i]) == 1) {
                    inFinalPos = 1;
                }
            }
        }
        vals = split(info[1], ',');
        for (int i = 0; i<3; i++) {
            bricks[total].push_back(stoi(vals[i]));
            if (i == 2) {
                if (stoi(vals[i]) == 1) {
                    inFinalPos = 1;
                }
            }
        }
        bricks[total].push_back(inFinalPos);
        total += 1;
        areFinal += inFinalPos;
    }
    inputFile.close();


    // sort bricks by z coordinate
    std::sort(bricks.begin(), bricks.end(),
          [](const std::vector<int>& a, const std::vector<int>& b) {
  return a[2] < b[2];
});




    map<int, vector<int>> dependencies, holdingUp;
    vector<int> brick;
    int minChange, touchingFinal, changeHere;

    for (int i = 0; i < total; i++) {
        brick = bricks[i];
        if (brick[6]) {
            continue;
        }
        minChange = brick[2]-1;
        touchingFinal = 1;

        for (int j = 0; j < total; j++) {
            if (j == i) {
                continue;
            }

            changeHere = isItBelow(brick, bricks[j]);

            
            if (changeHere >= 0) {
                if (changeHere < minChange) {
                    minChange = changeHere;
                    dependencies[i].clear();
                }
                if (changeHere <= minChange) {
                    if (bricks[j][6]) {
                        touchingFinal = 1;
                        dependencies[i].push_back(j);
                    }
                }
            }
        }
        if (minChange >= 0) {
            brick[2] -= minChange;
            brick[5] -= minChange;
            if (touchingFinal) {
                brick[6] = 1;
                areFinal += 1;
            }
            if (brick[2] == 0) {
                brick[6] = 1;
            }
            bricks[i] = brick;
        }


    }
    

    for (auto const& [key, val] : dependencies) {
        for (auto brk : val) {
            holdingUp[brk].push_back(key);
        }
    }

    int areSafe = 0, isSafe;
    vector<int> thisOnly;
    for (int i = 0; i < bricks.size(); i++) {
        isSafe = 1;
        thisOnly = {i};
        for (auto const& [key, val] : dependencies) {
            if (val == thisOnly) {
                isSafe = 0;
                break;
            }
        }
        areSafe += isSafe;

    }
    cout << "a: " << areSafe << endl;


    int bricksMoved = 0, curr, allDepMoved;
    vector<int> moved, active;


    // move over the dependencies and holdingUp graphs I already have constructed
    for (int r = 0; r < bricks.size(); r++) {
        moved.clear();
        active = {r};

        while (active.size()) {
            curr = active[0];
            active.erase(active.begin());
            moved.push_back(curr);
            for (int above : holdingUp[curr]) {
                if (find(moved.begin(), moved.end(), above) != moved.end()) {
                    continue;
                }

                allDepMoved = 1;
                for (int below : dependencies[above]) {
                    if (find(moved.begin(), moved.end(), below) == moved.end()) {
                        allDepMoved = 0;
                        break;
                    }
                }
                if (allDepMoved) {
                    active.push_back(above);
                }
            }
        }
        bricksMoved += moved.size() - 1;
        
    }
    cout << "b: " << bricksMoved << endl;
    

    
    return 0;
}