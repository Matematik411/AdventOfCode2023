#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
#include <set>
#include <queue>

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
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    // if any is empty
    for (int i = 0; i < elems.size(); i++) {
        if (elems[i] != "") {
            real.push_back(elems[i]);
        }
    }
    // if whitespace after delim
    for (int i = 1; i < real.size(); i++) {
        real[i] = real[i].substr(1);
    }
    return real;
}

vector< vector< vector<int> > > distancesPreCalc;
long long int distSmallerThan(long long int local, long long int bound, long long int parity) {
    long long int sol = 0, W = distancesPreCalc[local].size();
    for (long long int j = 0; j < W; j++) {
        for (long long int i = 0; i < W; i++) {
            if (distancesPreCalc[local][j][i] == -1) {
                continue;
            }
            if (distancesPreCalc[local][j][i] <= bound) {
                if (distancesPreCalc[local][j][i] % 2 == parity) {
                    sol += 1;
                }
            }
        }
    }
    return sol;
}




int main() {
    string filename;
    filename = "inputs/21.txt";

    
    vector<pair<int, int>> dirs;
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
    vector< string > garden;
    // S is in the middle of the square grid
    // calculate distances to the middle point or middle of edge or corner
    // ..........................      4             1 3 5 7        0 2 6 8

    // 0 1 2
    // 3 4 5
    // 6 7 8
    // vector< vector< vector<int> > > distancesPreCalc;
    pair<int, int> center;
    int W;
    while (getline(inputFile, line)) {
        garden.push_back(line);
    }
    inputFile.close();
    W = garden[0].size();
    center = {W/2, W/2};

    vector<vector<int>> distances;
    vector<pair<int, int>> startingPoints;
    startingPoints.push_back({W-1, W-1});
    startingPoints.push_back({W/2, W-1});
    startingPoints.push_back({0, W-1});
    startingPoints.push_back({W-1, W/2});
    startingPoints.push_back({W/2, W/2});
    startingPoints.push_back({0, W/2});
    startingPoints.push_back({W-1, 0});
    startingPoints.push_back({W/2, 0});
    startingPoints.push_back({0, 0});

    queue<vector<int>> active;
    vector<int> current;
    int x, y, d, xN, yN;

    for (int k = 0; k<9; k++) {
        distances = {};
        for (int aux = 0; aux < W; aux++) {
            vector<int> row(W, -1);
            distances.push_back(row);
        }
        
        active.push({startingPoints[k].first, startingPoints[k].second, 0});
        distances[startingPoints[k].second][startingPoints[k].first] = 0;

        while (not active.empty())
        {
            current = active.front();
            active.pop();
            x = current[0];
            y = current[1];
            d = current[2];

            for (int dir = 0; dir < 4; dir++) {
                xN = x + dirs[dir].first;
                yN = y + dirs[dir].second;

                if ((xN < 0) || (yN < 0) || (xN >= W) || (yN >= W)) {
                    continue;
                }
                if (garden[yN][xN] == '#') {
                    continue;
                }
                if (distances[yN][xN] != -1) {
                    continue;
                }
                distances[yN][xN] = d+1;
                active.push({xN, yN, d+1});
            }
        }
        distancesPreCalc.push_back(distances);
    }

    // part 1
    int stepsForA = 64, solA = distSmallerThan(4, stepsForA, 0);
    cout << "a: " << solA << endl;

    // part 2
    long long int stepsForB = 26501365, k = stepsForB / W, k1 = k/2, t = stepsForB % W;
    long long int solB = 0;

    // did the calculations on paper

    // center
    solB += distSmallerThan(4, 2*W, 1);

    // cells entirely inside
    solB += k1 * distSmallerThan(1, 2*W, 1);
    solB += k1 * distSmallerThan(3, 2*W, 1);
    solB += k1 * distSmallerThan(5, 2*W, 1);
    solB += k1 * distSmallerThan(7, 2*W, 1);

    solB += (k1-1) * distSmallerThan(1, 2*W, 0);
    solB += (k1-1) * distSmallerThan(3, 2*W, 0);
    solB += (k1-1) * distSmallerThan(5, 2*W, 0);
    solB += (k1-1) * distSmallerThan(7, 2*W, 0);

    solB += (k1-1)*(k1-1) * distSmallerThan(0, 2*W, 1);
    solB += (k1-1)*(k1-1) * distSmallerThan(2, 2*W, 1);
    solB += (k1-1)*(k1-1) * distSmallerThan(6, 2*W, 1);
    solB += (k1-1)*(k1-1) * distSmallerThan(8, 2*W, 1);

    solB += (k1-1)*k1 * distSmallerThan(0, 2*W, 0);
    solB += (k1-1)*k1 * distSmallerThan(2, 2*W, 0);
    solB += (k1-1)*k1 * distSmallerThan(6, 2*W, 0);
    solB += (k1-1)*k1 * distSmallerThan(8, 2*W, 0);

    // turning points
    solB += distSmallerThan(1, W-1, 0);
    solB += distSmallerThan(3, W-1, 0);
    solB += distSmallerThan(5, W-1, 0);
    solB += distSmallerThan(7, W-1, 0);

    // edges
    solB += k * distSmallerThan(0, t-1, 0);
    solB += k * distSmallerThan(2, t-1, 0);
    solB += k * distSmallerThan(6, t-1, 0);
    solB += k * distSmallerThan(8, t-1, 0);

    solB += (k-1) * distSmallerThan(0, t+W-1, 1);
    solB += (k-1) * distSmallerThan(2, t+W-1, 1);
    solB += (k-1) * distSmallerThan(6, t+W-1, 1);
    solB += (k-1) * distSmallerThan(8, t+W-1, 1);
    

    cout << "b: " << solB << endl;

    return 0;
}