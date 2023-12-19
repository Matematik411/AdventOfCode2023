#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
#include <regex>

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


map<string, vector<vector<string>> > workflows;
string process(string workflow, map<char, int> item) {
    for (auto cond : workflows[workflow]) {
        if (cond.size() == 1) {
            return cond[0];
        }
        else {
            char letter = cond[0][0], operation = cond[0][1];
            
            if (operation == '<') {
                if ( item[letter] < stoi(cond[0].substr(2)) ) {
                    return cond[1];
                }
            }
            else { // operation == '>'
                if ( item[letter] > stoi(cond[0].substr(2)) ) {
                    return cond[1];
                }
            }
        }
    }

    return "ERROR";
}

vector< pair< string, map<char, pair<int, int>> >> processRange(string workflow, map<char, pair<int, int>> item) {
    vector< pair< string, map<char, pair<int, int>> >> res;
    map<char, pair<int, int>> newItem;

    for (auto cond : workflows[workflow]) {
        if (cond.size() == 1) {
            res.push_back( { cond[0] , item } );
            return res;
        }
        else {
            char letter = cond[0][0], operation = cond[0][1];
            int checkAgainst = stoi(cond[0].substr(2));
            
            if (operation == '<') {
                if (checkAgainst <= item[letter].first) {
                    continue;
                }
                else if (checkAgainst > item[letter].second) {
                    res.push_back( { cond[1] , item } );
                    return res;
                }
                else {
                    newItem[letter] = { item[letter].first, checkAgainst-1 };
                    for (char lt : "xmas") {
                        if (lt == '\0') {
                            continue;
                        }
                        if (lt != letter) {
                            newItem[lt] = item[lt];
                        }
                    }
                    res.push_back( { cond[1] , newItem } );
                    item[letter].first = checkAgainst;
                }

            }
            else { // operation == '>'
                if (checkAgainst >= item[letter].second) {
                    continue;
                }
                else if (checkAgainst < item[letter].first) {
                    res.push_back( { cond[1] , item } );
                    return res;
                }
                else {
                    newItem[letter] = { checkAgainst + 1, item[letter].second };
                    for (char lt : "xmas") {
                        if (lt == '\0') {
                            continue;
                        }
                        if (lt != letter) {
                            newItem[lt] = item[lt];
                        }
                    }
                    res.push_back( { cond[1] , newItem } );
                    item[letter].second = checkAgainst;
                }

            }
        }
    }

    cout << "ERRRORRRRRRRRRR" << endl;
    return res;
}


int main() {
    string filename;
    filename = "inputs/19.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line, name;
    map<char, int> ratings;
    vector<string> conditions, cases;

    int c;
    while (getline(inputFile, line)) {
        if (line == "") {
            break;
        }
        name = line.substr(0, line.find('{'));
        conditions = split(line.substr(line.find('{')+1), ',');
        for (string cond : conditions) {
            if (cond.find(':') != string::npos) {
                cases = split(cond, ':');
                cases = {cases[0], cases[1]};
            }
            else {
                cases = {cond.substr(0, cond.size()-1)};
            }
            workflows[name].push_back(cases);
        }
    }
    

    vector<string> one, two;
    string letters = "xmas", flow;
    long long int solA = 0, solB = 0;
    bool finalized;
    map<char, pair<int, int>> ratingsRange;
    vector< map<char, pair<int, int>> > ratingsAll;
    vector< pair< string, map<char, pair<int, int>> >> active;
    while (getline(inputFile, line)) {

        one = split(line.substr(1, line.size()-2), ',');
        for (int i = 0; i < 4; i++) {
            ratings[letters[i]] = stoi( one[i].substr(2) );
        }

        finalized = false;
        flow = "in";

        while (not finalized) {
            flow = process(flow, ratings);

            if (flow == "A") {
                for (char letter : "xmas") {
                    if (letter == '\0') {
                        continue;
                    }
                    solA += ratings[letter];
                }
                finalized = true;
            }
            else if (flow == "R") {
                finalized = true;
            }

        }
    }
    inputFile.close();


    // part b)
    for (char letter : "xmas") {
        if (letter == '\0') {
            continue;
        }
        ratingsRange[letter] = {1, 4000};
    }

    active.push_back({"in", ratingsRange});

    pair< string, map<char, pair<int, int>> > current;
    string currName;

    while (active.size()) {
        current = active.back();
        active.pop_back();

        currName = current.first;
        ratingsRange = current.second;

        long long int product = 1;
        if (currName == "R") {
            continue;
        }
        else if (currName == "A") {
            for (char letter : "xmas") {
                if (letter == '\0') {
                    continue;
                }
                product *= (ratingsRange[letter].second - ratingsRange[letter].first + 1);
            }
            solB += product;
            continue;
        }

        // calculate how the ranges are split
        for (auto r : processRange(currName, ratingsRange)) {
            active.push_back(r);
        }

    }

    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;

    return 0;
}