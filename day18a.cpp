#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
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

vector<string> split(const string &s, char delim) {
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    return elems;
}



int main() {
    string filename;
    filename = "inputs/18.txt";

    map<string, pair<int, int>> dirs;
    dirs["R"] = {1, 0};
    dirs["L"] = {-1, 0};
    dirs["D"] = {0, 1};
    dirs["U"] = {0, -1};


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int dirId = 0;
    string line, options = "RDLU", chosenOption;
    vector<pair<long long int, long long int>> points;
    points.push_back({0, 0});

    vector<string> info;
    long long int edgeLen, x = 0, y = 0, xN, yN, pointsOnBoundary = 0;

    while (getline(inputFile, line)) {
        info = split(line, ' ');
        edgeLen = stoi( info[1] );
        chosenOption = info[0];

        xN = x + dirs[chosenOption].first * edgeLen;
        yN = y + dirs[chosenOption].second * edgeLen;
        
        points.push_back({xN, yN});
        x = xN;
        y = yN;
        pointsOnBoundary += edgeLen;
        
    }
    inputFile.close();
    int N = points.size() - 1;

    long long int area = 0;
    for (int i = 0; i < N; i++) {
        area += (points[i].second + points[i+1].second) * (points[i].first - points[i+1].first);
    }
    area = area/2;

    long long int solB = area + 1 + (pointsOnBoundary / 2);

    cout << "a: " << solB << endl;
    
    return 0;
}