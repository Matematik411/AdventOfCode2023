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



vector<vector<int>> pq;
void addNode(vector<int> node) {
    bool added = false;
    for (int i = 0; i < pq.size(); i++) {
        if (node[2] < pq[i][2]) {
            pq.insert(pq.begin()+i, node);
            added = true;
            break;
        }
    }
    if (not added) {
        pq.push_back(node);
    }
    return ;
}

void addNodeStar(vector<int> node) {
    bool added = false;
    int nodeVal = node[2] - node[0] - node[1];
    for (int i = 0; i < pq.size(); i++) {
        if (nodeVal < (-pq[i][0] + -pq[i][1] + pq[i][2]) ) {
            pq.insert(pq.begin()+i, node);
            added = true;
            break;
        }
    }
    if (not added) {
        pq.push_back(node);
    }
    return ;
}


int main() {
    string filename;
    filename = "inputs/17.txt";


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
    vector<int> start = {0, 0}, goal = {W-1, H-1};


    vector<pair<int, int>> dirs;
    dirs.push_back({1, 0});
    dirs.push_back({0, 1});
    dirs.push_back({-1, 0});
    dirs.push_back({0, -1});

    vector<int> info;
    pair<int, int> movingInfo;
    vector<pair<int, int>> visitedHere;
    map<pair<int, int>, vector<pair<int, int>>> visited;

    int x, y, cost, dir, dirAmount, xN, yN, dirN;

    int step = 0;
    // around 910.000 steps
    
    pq.push_back({0, 0, 0, 0, 0});
    while (pq.size()) {
        step += 1;
        if (step % 1000 == 0) {
            cout << step << " -- " << cost << endl;
        }
        info = pq[0];
        pq.erase(pq.begin());
        x = info[0];
        y = info[1];
        cost = info[2];
        dir = info[3];
        dirAmount = info[4];

        movingInfo = {dir, dirAmount};
        visitedHere = visited[{x, y}]; 
        if (find(visitedHere.begin(), visitedHere.end(), movingInfo) != visitedHere.end()) {
            continue;
        }
        visited[{x, y}].push_back(movingInfo);

        info = {x, y};
        if (goal == info) {
            if (dirAmount < 4) {
                continue;
            }
            cout << "b: " << cost << endl;
            break;
        }

        for (int i = 0; i < 4; i++) {
            if (((i+2)%4) == dir) {
                continue;
            }
            else if ((i == dir) && (dirAmount == 10)) {
                continue;
            }
            else {
                xN = x + dirs[i].first;
                yN = y + dirs[i].second;
                if ((xN < 0) || (yN < 0) || (xN >= W) || (yN >= H)) {
                    continue;
                }
                if ((i != dir) && (dirAmount < 4)) {
                    continue;
                }
                if (i == dir) {
                    dirN = dirAmount + 1;
                }
                else {
                    dirN = 1;
                }
                movingInfo = {i, dirN};
                visitedHere = visited[{xN, yN}];
                if (find(visitedHere.begin(), visitedHere.end(), movingInfo) != visitedHere.end()) {
                    continue;
                }
                else {
                    addNode({xN, yN, cost + data[yN][xN] - '0', i, dirN});
                }


            }
        }

    }
    
    return 0;
}