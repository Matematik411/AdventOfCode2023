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
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    for (int i = 1; i < elems.size(); i++) {
        elems[i] = elems[i].substr(1);
    }
    return elems;
}




int main() {
    string filename;
    filename = "inputs/08.txt";


    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line, moves, node;
    vector< int > data;
    vector<string> info;
    getline(inputFile, moves);
    getline(inputFile, line);

    map<string, pair<string, string>> graph;
    while (getline(inputFile, line)) {
        info = split(line, '=');
        node = info[0].substr(0, 3);
        info = split(info[1].substr(1, 8), ',');
        graph[node] = {info[0], info[1]};
    }
    inputFile.close();

    string loc = "AAA";
    int i = 0, N = moves.size();
    char move;

    while (loc != "ZZZ") {
        move = moves[i%N];
        if (move == 'L') {
            loc = graph[loc].first;
        }
        else {
            loc = graph[loc].second;
        }
        i += 1;
    }
    cout << "a: " << i << endl;


    return 0;
}