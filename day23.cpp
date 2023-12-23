#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <queue>
#include <set>

using namespace std;


int main() {
    string filename;
    filename = "inputs/23.txt";

    vector<pair<int, int>> dirs;
    dirs.push_back({1, 0});
    dirs.push_back({0, 1});
    dirs.push_back({-1, 0});
    dirs.push_back({0, -1});
    string slopes = ">v<^";



    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > maze;

    int H, W;
    while (getline(inputFile, line)) {
        maze.push_back(line);
        H += 1;
    }
    inputFile.close();
    W = maze[0].size();
    pair<int, int> starting = {1, 0}, ending = {W-2, H-1};

    queue<
        pair<
            pair<
                pair<int, int>,
                pair<int, int>
            >,
            pair<
                int,
                set<pair<int, int>>
            >
        >> active, fromCurrent;

    pair<
            pair<
                pair<int, int>,
                pair<int, int>
            >,
            pair<
                int,
                set<pair<int, int>>
            >
        > current;
    int x, y, d, nrOfOpen, xN, yN, solA = 0;
    set<pair<int, int>> prevDecisions;
    pair<int, int> prevPos, thisPos, newPos;


    active.push({{starting, starting}, {0, {}}});
    while (not active.empty()) {
        current = active.front();
        active.pop();
        thisPos = current.first.first;
        prevPos = current.first.second;
        x = thisPos.first;
        y = thisPos.second;
        d = current.second.first;
        prevDecisions = current.second.second;


        if (thisPos == ending) {
            // solA = 2018
            if (d > solA) {
                solA = d;
                cout << "a: " << solA << endl;
            }
            continue;
        }

        fromCurrent = {};
        nrOfOpen = 0;
        for (int dir = 0; dir < 4; dir++) {
            xN = x + dirs[dir].first;
            yN = y + dirs[dir].second;
            newPos = {xN, yN};

            if ((xN < 0) || (yN < 0) || (xN >= W) || (yN >= H)) {
                continue;
            }
            if (maze[yN][xN] == '#') {
                continue;
            }
            if (newPos == prevPos) {
                continue;
            }
            nrOfOpen += 1;
            if ((maze[yN][xN] == '.') || (maze[yN][xN] == slopes[dir])) {
                
                if (prevDecisions.find(newPos) != prevDecisions.end()) {
                    continue;
                }
                fromCurrent.push({{newPos, thisPos}, {d+1, prevDecisions}});
            }
        }
        while (not fromCurrent.empty()) {
            current = fromCurrent.front();
            fromCurrent.pop();
            if (nrOfOpen > 1) {
                current.second.second.insert(thisPos);
            }
            active.push(current);
        }

    } 



    
    return 0;
}