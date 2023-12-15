#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>

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
    filename = "inputs/13.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< string > data;
    int H, W, solA = 0, d, solB = 0; 
    bool isOver = false;

    int nr = 0;
    getline(inputFile, line);
    while (not isOver) {
        nr += 1;
        data = {line};
        while (getline(inputFile, line)) {
            if (line == "") {
                break;
            }
            data.push_back(line);
        }
        H = data.size();
        W = data[0].size();

        // vertical line
        bool equal, oneDiff;
        int diff;
        for (int i = 1; i < W; i++) {
            d = min(i, W-i);
            equal = true;
            diff = 0;
            for (int k = 0; k < d; k++) {
                for (int j = 0; j < H; j++) {
                    if (data[j][i - k - 1] != data[j][i + k]) {
                        equal = false;
                        diff += 1;
                    }
                }
            }
            if (equal) {    
                solA += i;
            }
            if (diff == 1) {
                solB += i;
            }
        }
        // horizontal line
        for (int j = 1; j < H; j++) {
            d = min(j, H-j);
            equal = true;
            diff = 0;
            for (int k = 0; k < d; k++) {
                for (int i = 0; i < W; i++) {
                    if (data[j - k - 1][i] != data[j + k][i]) {
                        equal = false;
                        diff += 1;
                    }
                }
            }
            if (equal) {    
                solA += 100 * j;
            }
            if (diff == 1) {
                solB += 100 * j;
            }
        }

        if (not getline(inputFile, line)) {
            isOver = true;
        }
    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;

    inputFile.close();

    return 0;
}