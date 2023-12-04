#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <algorithm>
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
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    // if any is empty
    for (int i = 0; i < elems.size(); i++) {
        if (elems[i] != "") {
            real.push_back(elems[i]);
        }
    }
    return real;
}


int main() {
    string filename;
    filename = "inputs/04.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< int > data;
    map<int, int> multiplier;

    int c, solA = 0, solB = 0, id = 1;
    while (getline(inputFile, line)) {
        line = line.substr(line.find(':') + 2);
        
        vector<string> parts = split(line, '|');
        vector<string> winners = split(parts[0],  ' ');
        vector<string> mine = split(parts[1], ' ');

        int correct = 0;
        for (string v : mine) {
            int val = stoi( v );
            if (find(winners.begin(), winners.end(), v) != winners.end()) {
                correct += 1;
            }
        }

        // a)
        if (correct) {
            int toAdd = 1;
            for (int i = 0; i < (correct-1); i++) {
                toAdd *= 2;
            }
            solA += toAdd;
        }
        // b)
        multiplier[id] += 1;
        for (int i = 0; i < correct; i++) {
            multiplier[id+i+1] += multiplier[id];
        }
        solB += multiplier[id];
    
        id += 1;
    }
    inputFile.close();

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;



    return 0;
}