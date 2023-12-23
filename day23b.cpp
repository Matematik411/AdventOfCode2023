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
#include <map>
#include <algorithm>

using namespace std;

vector<pair<int, int>> dirs;
vector< string > maze;
int H, W;
map<int, vector<pair<int, int>>> graph;

vector<int> getNeigh(int i, int j) {
    vector<int> neighDirs;

    for (int dir = 0; dir < 4; dir++) {
        int x = i + dirs[dir].first;
        int y = j + dirs[dir].second;
        if ((x < 0) || (y < 0) || (x >= W) || (y >= H)) {
            continue;
        }
        if (maze[y][x] != '#') {
            neighDirs.push_back(dir);
        }
    }
    return neighDirs;
}


int main() {
    string filename;
    filename = "inputs/23.txt";

    dirs.push_back({1, 0});
    dirs.push_back({0, 1});
    dirs.push_back({-1, 0});
    dirs.push_back({0, -1});



    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {
        maze.push_back(line);
        H += 1;
    }
    inputFile.close();
    W = maze[0].size();
    pair<int, int> starting = {1, 0}, ending = {W-2, H-1};

    vector<pair<int, int>> crossroads;
    crossroads.push_back({1, 0});
    cout << "asd" << endl;

    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            if (maze[j][i] == '#') {
                continue;
            }
            if (getNeigh(i, j).size() > 2) {
                crossroads.push_back({i, j});
            }
        }
    }
    crossroads.push_back({W-2, H-1});
    
    int x, y, id = 0, dist, idDirFrom, dirN, idOther;
    vector<int> neigh;
    pair<int, int> other;
    for (pair<int, int> p : crossroads) {

        for (int dir : getNeigh(p.first, p.second)) {
            x = p.first + dirs[dir].first;
            y = p.second + dirs[dir].second;
            dist = 1;
            dirN = dir;

            neigh = getNeigh(x, y);
            while (neigh.size() == 2) {
                idDirFrom = find(neigh.begin(), neigh.end(), (dirN+2)%4) - neigh.begin();
                dirN = neigh[1-idDirFrom];

                x = x + dirs[dirN].first;
                y = y + dirs[dirN].second;
                dist += 1;
                neigh = getNeigh(x, y);
            }

            other = {x, y};
            idOther = find(crossroads.begin(), crossroads.end(), other) - crossroads.begin();
            graph[id].push_back({idOther, dist});
        }
        id += 1;
    }

    int startId = 0, endId = crossroads.size()-1;
    queue<
        pair<
            pair<
                int,
                int
            >,
            set<int>
        >
    > active;
    active.push({{startId, 0}, {}});

    pair<
        pair<
            int,
            int
        >,
        set<int>
    > current;
    int thisNode, distToHere, solB = 0;
    set<int> visited;

    while (not active.empty()) {

        current = active.front();
        active.pop();
        thisNode = current.first.first;
        distToHere = current.first.second;
        visited = current.second;
        visited.insert(thisNode);

        if (thisNode == endId) {
            // takes a few minutes .. solB = 6406 
            if (distToHere > solB) {
                solB = distToHere;
                cout << solB << "   " << active.size() << endl;
            }
        }

        for (pair<int, int> neigh : graph[thisNode]) {
            if (visited.find(neigh.first) == visited.end()) {
                active.push({{neigh.first, distToHere + neigh.second}, visited});
            }
        }
    }

    cout << "b: " << solB << endl;

    return 0;
}