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



int main() {
    string filename;
    filename = "inputs/11.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > data;
    vector<pair<int, int>> stars;
    int H = 0, W;

    while (getline(inputFile, line)) {
        data.push_back(line);
        H += 1;
    }
    inputFile.close();
    W = data[0].size();

    vector<int> rowsEmpty, columnsEmpty;

    for (int i = 0; i < H; i++) {
        int points = 0;
        for (int j = 0; j < W; j++) {
            if (data[i][j] == '#') {
                stars.push_back({i, j});
                points += 1;
            }
        }
        if (points == 0) {
            rowsEmpty.push_back(i);
        }
        points = 0;
    }
    for (int j = 0; j < W; j++) {
        int points = 0;
        for (int i = 0; i < H; i++) {
            if (data[i][j] == '#') {
                points += 1;
            }
        }
        if (points == 0) {
            columnsEmpty.push_back(j);
        }
        points = 0;
    }

    int sumA = 0;
    long long int sumB = 0;
    pair<int, int> fst, snd;
    int verticalExp = 0, horizontalExp = 0, vert, hor;

    for (int m = 0; m < stars.size(); m++) {
        fst = stars[m];
        for (int n = m+1; n < stars.size(); n++) {
            snd = stars[n];
            verticalExp = 0;
            horizontalExp = 0;

            vert = abs(fst.first - snd.first);
            hor = abs(fst.second - snd.second);

            for (int i = min(fst.first, snd.first); i < max(fst.first, snd.first); i++) {
                if (find(
                    rowsEmpty.begin(), 
                    rowsEmpty.end(), 
                    i ) != rowsEmpty.end()) {
                        verticalExp += 1;
                }
            }
            for (int i = min(fst.second, snd.second); i < max(fst.second, snd.second); i++) {
                if (find(
                    columnsEmpty.begin(), 
                    columnsEmpty.end(), 
                    i ) != columnsEmpty.end()) {
                        horizontalExp += 1;
                }
            }
            sumA += (vert + hor + horizontalExp + verticalExp);
            sumB += vert + hor + (horizontalExp + verticalExp) * (1000000 - 1);
        }
    }

    cout << "a: " << sumA << endl;
    cout << "b: " << sumB << endl;



    return 0;
}