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

vector<int> split(const string &s, char delim) {
    vector<string> elems;
    vector<int> real;
    split(s, delim, back_inserter(elems));
    for (int i = 0; i < elems.size(); i++) {
        real.push_back(stoi(elems[i]));
    }
    return real;
}



int main() {
    string filename;
    filename = "inputs/09.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< int > data;

    int solA = 0, solB = 0;
    while (getline(inputFile, line)) {
        data = split(line, ' ');

        map<int, vector<int>> changes;
        changes[0] = data;

        int work = 1, allZero, line = 1;
        vector<int> newOne;
        while (work) {

            allZero = 1;
            for (int x : data) {
                if (x != 0) {
                    allZero = 0;
                }
            }
            if (allZero) {
                break;
            }
            
            for (int i = 0; i < (data.size()-1); i++) {
                newOne.push_back(data[i+1] - data[i]);
            }
            changes[line] = newOne;
            data = newOne;
            newOne.clear();
            line += 1;
        } 

        line -= 1;
        int valueLeft, valueRight;
        while (line > 0) {
            valueRight = changes[line-1][changes[line-1].size()-1] + changes[line][changes[line].size()-1];
            valueLeft = changes[line-1][0] - changes[line][0];
            changes[line-1].push_back(valueRight);
            changes[line-1].insert(changes[line-1].begin(), valueLeft);
            line -= 1;
        }
        solA += valueRight;
        solB += valueLeft;
    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;




    inputFile.close();

    return 0;
}