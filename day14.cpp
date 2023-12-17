#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <algorithm>


using namespace std;

int H, W;
vector< vector<char> > platform;

void tilt(int vertical, int delta ) {
    int lastFree, start = 0;
    if (delta < 0) {
        if (vertical) {
            start = H-1;
        }
        else {
            start = W-1;
        }
    }

    if (vertical) {
        for (int i = 0; i < W; i++) {
            lastFree = -1;
            for (int j = start; (0 <= j) && (j < H); j += delta) {
                if (platform[j][i] == '#') {
                    lastFree = -1;
                }
                else if (platform[j][i] == 'O') {
                    if (lastFree >= 0) {
                        platform[j][i] = '.';
                        platform[lastFree][i] = 'O';
                        lastFree += delta;
                    }
                }
                else {
                    if (lastFree == -1) {
                        lastFree = j;
                    }
                }

            }
        }
    }
    else {
        for (int j = 0; j < H; j++) {
            lastFree = -1;
            for (int i = start; (0 <= i) && (i < W); i += delta) {
                if (platform[j][i] == '#') {
                    lastFree = -1;
                }
                else if (platform[j][i] == 'O') {
                    if (lastFree >= 0) {
                        platform[j][i] = '.';
                        platform[j][lastFree] = 'O';
                        lastFree += delta;
                    }
                }
                else {
                    if (lastFree == -1) {
                        lastFree = i;
                    }
                }

            }
        }
    }

    return ;
}

int countLoad() {
    int load = 0;
    for (int i = 0; i < H; i++) {
        load += (H-i) * count(platform[i].begin(), platform[i].end(), 'O');
    }
    return load;
}



int main() {
    string filename;
    filename = "inputs/14.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {
        vector<char> data(line.begin(), line.end());
        platform.push_back(data);
    }
    inputFile.close();
    H = platform.size();
    W = platform.size();


    // part a)
    // ^^
    tilt(1, 1);
    cout << "a: " << countLoad() << endl;

    // part b)
    long long int spins = 1000000000;

    // nrOfLoads loops!
    // => I calculate first 204 values, then loops with size of loop 14
    // so the result is same as after the 188 cycle
    spins = 204;
    vector<int> loads;

    // <<
    tilt(0, 1);
    // ˇˇ
    tilt(1, -1);
    // >>
    tilt(0, -1);

    loads.push_back(0);
    loads.push_back(countLoad());

    int thisLoad;
    for (int c = 2; c < spins; c++) {
        // ^^
        tilt(1, 1);
        // <<
        tilt(0, 1);
        // ˇˇ
        tilt(1, -1);
        // >>
        tilt(0, -1);

        thisLoad = countLoad();
        auto iter = find(loads.begin(), loads.end(), thisLoad);
        if (iter != loads.end()) {
            int d = distance(loads.begin(), iter);
            // cout << "this index is " << c << " already at " << d << " -- " << c-d << endl;
        }
        else {
            // cout << "NOT IT " << c << endl;;
        }
        loads.push_back(thisLoad);
    }
    cout << "b: " << loads[188] << endl;

    return 0;
}