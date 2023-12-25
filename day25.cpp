#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
#include <set>
#include <queue>
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
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

map< string, vector<string> > graph;
vector<string> nodes;
vector<pair<string, string>> edges;

pair<int, int> divideGraph(int fst, int snd, int thrd) {
    string current;
    set<string> visited;
    queue<string> active;
    int groups = 0, solA;
    pair<string, string> e;

    for (int i = 0; i < nodes.size(); i++) {
        current = nodes[i];

        if (visited.find(current) != visited.end()) {
            continue;
        }

        visited.insert(current);
        active.push(current);

        while (not active.empty()) {
            current = active.front();
            active.pop();

            for (string neigh : graph[current]) {
                e = {current, neigh};
                if (e == edges[fst]) {
                    continue;
                }
                if (e == edges[snd]) {
                    continue;
                }
                if (e == edges[thrd]) {
                    continue;
                }
                e = {neigh, current};
                if (e == edges[fst]) {
                    continue;
                }
                if (e == edges[snd]) {
                    continue;
                }
                if (e == edges[thrd]) {
                    continue;
                }
                if (visited.find(neigh) == visited.end()) {
                    active.push(neigh);
                    visited.insert(neigh);
                }
            }
        }
        groups += 1;
        if (groups == 1) {
            solA = visited.size() * (nodes.size() - visited.size());
        }

    }
    return {groups, solA};
}

int main() {
    string filename;
    filename = "inputs/test.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector<string> info;
    int nrOfNodes = 0;

    while (getline(inputFile, line)) {
        info = split(line, ':');
        for (string n : split(info[1].substr(1), ' ')) {
            graph[info[0]].push_back(n);
            graph[n].push_back(info[0]);
            edges.push_back({n, info[0]});
            if (find(nodes.begin(), nodes.end(), n) == nodes.end()) {
                nodes.push_back(n);
            }
        }
        nrOfNodes += 1;
        if (find(nodes.begin(), nodes.end(), info[0]) == nodes.end()) {
            nodes.push_back(info[0]);
        }

    }
    inputFile.close();

    // does not end
    bool foundIt = 0;
    cout << edges.size() << endl;
    for (int i = 0; i < edges.size(); i++) {
        for (int j = i+1; j < edges.size(); j++) {
            for (int k = j+1; k < edges.size(); k++) {
                pair<int, int> nrOfGroups = divideGraph(i, j, k);
                if (nrOfGroups.first == 2) {
                    cout << "found ! solution is " << nrOfGroups.second << endl;
                    foundIt = 1;
                    break;
                }
            }
            if (foundIt) {
                break;
            }
        }
        if (foundIt) {
            break;
        }
    }

    // does not work
    pair<string, string> p;
    long long int val1 = 0, val2 = 0, val3 = 0, val;
    int i1, i2, i3;
    for ( int i = 0; i < edges.size(); i++) {
        p = edges[i];
        val = graph[p.first].size() + graph[p.second].size();

        if (val > val1) {
            i1 = i;
            val1 = val;
            cout << i1 << " --- " << val1 << endl;
        }
        else if (val > val2) {
            i2 = i;
            val2 = val;
            cout << i2 << " --- " << val2 << endl;
        }
        else if (val > val3) {
            i3 = i;
            val3 = val;
            cout << i3 << " --- " << val3 << endl;
        }
    }
    cout << i1 << "  " << val1 << endl;
    cout << i2 << "  " << val2 << endl;
    cout << i3 << "  " << val3 << endl;
    pair<int, int> nrOfGroups = divideGraph(i1, i2, i3);

    cout << "a: " << nrOfGroups.first << "   " << nrOfGroups.second << endl;

    cout << "actual solution in python with a library" << endl;

    // solved in python with a library
    
    return 0;
}