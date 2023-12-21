#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <queue> 
#include <map>
 
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
    // if whitespace after delim
    for (int i = 1; i < elems.size(); i++) {
        elems[i] = elems[i].substr(1);
    }
    return elems;
}

// Utility function to find
// GCD of 'a' and 'b'
long long int gcd(long long int a, long long int b)
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
    filename = "inputs/20.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line, mod;
    vector<string> info, targets;

    map< string, pair<char, vector<string>> > modules;
    map< string, int > flipflops;
    map< string, map<string, int> > conjunctions;


    int c;
    while (getline(inputFile, line)) {
        info = split(line, '>');
        targets = split(info[1], ',');
        if (info[0] == "broadcaster -") {
            modules["broadcaster"] = {'!', targets};
            continue;
        }

        mod = info[0].substr(1, info[0].size()-3);
        modules[mod] = {info[0][0], targets};
        if (info[0][0] == '%') {
            flipflops[mod] = 0;
        }

    }
    for (auto const& [key, val] : modules) {
        for (string t : val.second) {
            if (modules[t].first == '&') {
                conjunctions[t][key] = 0;
            }
        }
    }
    inputFile.close();


    queue<pair<int, pair<string, string>>> signals;
    pair<int, pair<string, string>> current;
    char typeOfMod;
    string sender, receiver;
    int typeOfSignal, allHigh;

    int buttonPushesTotal = 1000;
    int lows = 0, highs = 0;
    for (int buttonPush = 0; buttonPush < buttonPushesTotal; buttonPush++) {
        
        signals.push({0, {"button", "broadcaster"}});
        while (not signals.empty()) {
            current = signals.front();
            signals.pop();

            typeOfSignal = current.first;
            sender = current.second.first;
            receiver = current.second.second;
            typeOfMod = modules[receiver].first;
            if (typeOfSignal == 0) {
                lows += 1;
            }
            else {
                highs += 1;
            }
            // // reading for part 2
            // if (receiver == "dt") {
            //     if (sender == "pm") {
            //         if (typeOfSignal == 1) {
            //             cout << "dl   " << buttonPush << endl;
            //         }
            //     }
            //     // cout << sender << " - "<< typeOfSignal << " - " << receiver << endl;
            // }


            if (typeOfMod == '%') {
                if (typeOfSignal == 1) {
                    continue;
                }
                typeOfSignal = 1 - flipflops[receiver];
                flipflops[receiver] = typeOfSignal;
            }
            else if (typeOfMod == '&') {
                conjunctions[receiver][sender] = typeOfSignal;
                allHigh = 1;
                for (auto const& [key, val] : conjunctions[receiver]) {
                    if (val == 0) {
                        allHigh = 0;
                    }
                }
                typeOfSignal = 1 - allHigh;
            }

            for (string t : modules[receiver].second) {
                signals.push({typeOfSignal, {receiver, t}});
            }

        }
    }

    cout << "a: " << lows * highs << endl;

    // for "rx" to receive a 0, all of {dl, vk, ks, pm} must send a 1
    // so I calculate their loop lengths and find their LCM
    vector<long long int> valuesForB = {3769, 3877, 3917, 3833};
    cout << "b: " << findlcm(valuesForB) << endl;

    return 0;
}