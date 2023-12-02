#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
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
    // if whitespace after delim
    for (int i = 1; i < elems.size(); i++) {
        elems[i] = elems[i].substr(1);
    }
    return elems;
}


int main() {
    string filename;
    filename = "inputs/02.txt";

    int red = 12;
    int green = 13;
    int blue = 14;


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;

    int ok, id = 1, solA = 0, solB=0;
    string nr, col;
    vector<string> cases, pulls;
    while (getline(inputFile, line)) {
        line = line.substr(line.find(':') + 2);
        ok = 0;

        map<string, int> bagMinSizes;
        bagMinSizes["red"] = 0;
        bagMinSizes["blue"] = 0;
        bagMinSizes["green"] = 0;

        cases = split(line, ';');
        for (string aCase : cases) {

            pulls = split(aCase, ',');
            for (string pull : pulls) {
                nr = pull.substr(0, pull.find(' '));
                col = pull.substr(pull.find(' ')+1);
                bagMinSizes[col] = max(bagMinSizes[col], stoi(nr));
            }

        }

        if ((bagMinSizes["red"] <= red) && (bagMinSizes["blue"] <= blue) && (bagMinSizes["green"] <= green)) {
            ok = 1;
        }

        solB += bagMinSizes["red"] * bagMinSizes["green"] * bagMinSizes["blue"];
        if (ok) {
            solA += id;
        }

        id += 1;
    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;


    inputFile.close();

    return 0;
}