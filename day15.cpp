#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>

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
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

vector<pair<string, int>> removeLabel(vector<pair<string, int>> old, string label) {
    for (int i = 0; i < old.size(); i++) {
        if (old[i].first == label) {
            old.erase(old.begin() + i);
            break;
        }
    }
    return old;
}
vector<pair<string, int>> replaceLens(vector<pair<string, int>> old, string label, int lens) {
    int changed = 0;
    for (int i = 0; i < old.size(); i++) {
        if (old[i].first == label) {
            old[i].second = lens;
            changed = 1;
            break;
        }
    }
    if (changed == 0) {
        old.push_back({label, lens});
    }
    return old;
}

int main() {
    string filename;
    filename = "inputs/15.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    inputFile.close();
    vector<string> cases = split(line, ',');

    int solA = 0, single;

    for (string s : cases) {
        single = 0;
        for (char c : s) {
            single += int(c);
            single = (single * 17) % 256;
        }
        solA += single;
    }
    cout << "a: " << solA << endl;

    // b ----------------------
    map<int, vector<pair<string, int>>> boxes;
    string box;
    int val;
    for (string s : cases) {
        box = "";
        single = 0;
        for (char c : s) {
            if (c == '-') {
                boxes[single] = removeLabel(boxes[single], box);
            }
            else if (c == '=') {
                val = int( s.back() ) - int('0');
                boxes[single] = replaceLens(boxes[single], box, val);
            }
            else {
                single += int(c);
                single = (single * 17) % 256;
                box += c;
            }
        }
    }
    int solB = 0;
    for (int i = 0; i < 256; i++) {
        for (int k = 0; k < boxes[i].size(); k++) {
            solB += (i+1) * (k+1) * boxes[i][k].second;
        }
    }
    cout << "b: " << solB << endl;

    return 0;
}