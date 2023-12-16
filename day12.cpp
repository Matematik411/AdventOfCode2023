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
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

vector<int> splitInt(const string &s, char delim) {
    vector<string> elems;
    vector<int> real;
    split(s, delim, back_inserter(elems));
    for (int i = 0; i < elems.size(); i++) {
        real.push_back(stoi(elems[i]));
    }
    return real;
}

map<
    pair<
        vector<string>,
        vector<int>
        >,
    long long int
    > memoMap;

long long int nrOfWays(vector<string> allSections, vector<int> allSizes);
long long int nrOfWaysMemo(vector<string> s, vector<int> n) {
    long long int sol;
    pair<vector<string>, vector<int>> data = {s, n};
    

    if (memoMap.find(data) == memoMap.end()) {
        sol = nrOfWays(s, n);
        memoMap[data] = sol;
    }
    else {
        sol = memoMap[data];
    }

    return sol;

}


long long int nrOfWays(vector<string> allSections, vector<int> allSizes) {
    if (allSizes.size() == 0) {
        for (string s : allSections) {
            for (char c : s) {
                if (c == '#') {
                    return 0;
                }
            }
        }
        return 1;
    }

    
    
    long long int res = 0;
    int i = 0, ways, thisOne = allSizes[0];
    bool end = false, deleted;
    allSizes.erase(allSizes.begin());
    string section;


    while (allSections.size()) {
        section = allSections[0];
        ways = (section.size() + 1) - thisOne;
        deleted = false;
        for (int i = 0; i < ways; i++) {
            if ((i > 0) && (section[i-1] == '#')) {
                end = true;
                break;
            }
            else if ((i < (ways-1)) && (section[i+thisOne] == '#')) {
                continue;
            }
            else {
                if (i == (ways - 1)) {
                    allSections.erase(allSections.begin());
                    deleted = true;
                }
                else {
                    allSections[0] = section.substr(i + thisOne + 1);
                    
                }
                res += nrOfWaysMemo(allSections, allSizes);
            }
        }

        if (section.find('#') < section.size()) {
            end = true;
        }


        if (end) {
            break;
        }
        if (not deleted) {
            allSections.erase(allSections.begin());
        }
    }
    

    return res;
}




vector<string> createSections(string s) {
    string section = "";
    vector<string> sections;

    for (char c : s) {
        if (c == '.') {
            if (section != "") {
                sections.push_back(section);
                section = "";
            }
        }
        else {
            section += c;
        }
    }
    if (section != "") {
        sections.push_back(section);
    }
    return sections;
}



int main() {
    string filename;
    filename = "inputs/12.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line, creating, springsB;
    vector< string > info, sections;
    vector< int > values, valuesB;
    int len;



    int solA = 0;
    long long int solB = 0;
    while (getline(inputFile, line)) {
        info = split(line, ' ');
        sections = createSections(info[0]);
        values = splitInt(info[1], ',');

        solA += nrOfWaysMemo(sections, values);

        // part 2
        springsB = info[0];
        valuesB = values;
        for (int i = 0; i < 4; i++) {
            springsB += '?';
            springsB += info[0];
            for (int x : values) {
                valuesB.push_back(x);
            }
        }
        sections = createSections(springsB);
        solB += nrOfWaysMemo(sections, valuesB);

    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;




    inputFile.close();

    return 0;
}