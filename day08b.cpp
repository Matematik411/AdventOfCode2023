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

 
// Utility function to find
// GCD of 'a' and 'b'
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
 
// Returns LCM of array elements
long long int findlcm(vector<long long int> arr)
{
    // Initialize result
    long long int ans = arr[0];
    // ans contains LCM of arr[0], ..arr[i]
    // after i'th iteration,
    for (int i = 1; i < arr.size(); i++)
        ans = (((arr[i] * ans)) /
                (gcd(arr[i], ans)));
    return ans;
}


int main() {
    string filename;
    filename = "inputs/08.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< int > data;
    string moves, node;
    vector<string> info;
    getline(inputFile, moves);
    getline(inputFile, line);

    map<string, pair<string, string>> graph;
    vector<string> locs;
    int c;
    while (getline(inputFile, line)) {
        info = split(line, '=');
        node = info[0].substr(0, 3);
        info = split(info[1].substr(1, 8), ',');
        graph[node] = {info[0], info[1]};
        if (node[2] == 'A') {
            locs.push_back(node);
        }
    }
    
    vector<long long int> steps;
    for (string loc : locs) {
        int i = 0, N = moves.size();
        char move;

        while (loc[2] != 'Z') {
            move = moves[i%N];
            if (move == 'L') {
                loc = graph[loc].first;
            }
            else {
                loc = graph[loc].second;
            }
            i += 1;
        }
        steps.push_back(i);
        cout << "steps needed here: " << i << endl;
    }

    long long int resB = 1;
    for (int x : steps) {
        resB *= x;
    }
    cout << "b: " << findlcm(steps) << endl;
    inputFile.close();

    return 0;
}