#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename Out>
void split(const string &s, char delim, Out result) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, delim)) {
        *result++ = item;
    }
}

pair<string, int> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    pair<string, int> res;
    res.first = elems[0];
    res.second = stoi(elems[1]);
    return res;
}

int greaterHand(string fst, string snd) {
    string values = "AKQJT98765432";
    int N = values.size();
    vector<int> commonFst(N, 0), commonSnd(N, 0);
    for (char x : fst) {
        int i = values.find(x);
        commonFst[i] += 1;
    } 
    sort(commonFst.begin(), commonFst.end(), greater<int>());
    for (char x : snd) {
        int i = values.find(x);
        commonSnd[i] += 1;
    } 
    sort(commonSnd.begin(), commonSnd.end(), greater<int>());


    for (int i = 0; i < N; i++) {
        if (commonFst[i] != commonSnd[i]) {
            return (commonFst[i] > commonSnd[i]);
        }
    }

    for (int i = 0; i < 5; i++) {
        if (fst[i] != snd[i]) {
            return (values.find(fst[i]) < values.find(snd[i]));
        }
    }

    cout << "ERROR: something went wrong with sorting!" << endl;
    return -1;
}

int greaterHandJokers(string fst, string snd) {
    string values = "AKQT98765432J";
    int N = values.size(), jokersFst = 0, jokersSnd = 0;
    vector<int> commonFst(N, 0), commonSnd(N, 0);
    for (char x : fst) {
        if (x == 'J') {
            jokersFst += 1;
        }
        else {
            int i = values.find(x);
            commonFst[i] += 1;
        }
    } 
    sort(commonFst.begin(), commonFst.end(), greater<int>());
    commonFst[0] += jokersFst;
    for (char x : snd) {
        if (x == 'J') {
            jokersSnd += 1;
        }
        else {
            int i = values.find(x);
            commonSnd[i] += 1;
        }
    } 
    sort(commonSnd.begin(), commonSnd.end(), greater<int>());
    commonSnd[0] += jokersSnd;


    for (int i = 0; i < N; i++) {
        if (commonFst[i] != commonSnd[i]) {
            return (commonFst[i] > commonSnd[i]);
        }
    }

    for (int i = 0; i < 5; i++) {
        if (fst[i] != snd[i]) {
            return (values.find(fst[i]) < values.find(snd[i]));
        }
    }

    cout << "ERROR: something went wrong with sorting!" << endl;
    return -1;

}



vector<pair<string, int>> insertHand(vector<pair<string, int>> hands, pair<string, int> newOne, int part) {

    int k = 0;
    for (int i = 0; i < hands.size(); i++) {
        if (part == 1) {
            if (greaterHand(hands[i].first, newOne.first)) {
                hands.insert(hands.begin()+i, newOne);
                k = 1;
                break;
            }
        }
        else {
            if (greaterHandJokers(hands[i].first, newOne.first)) {
                hands.insert(hands.begin()+i, newOne);
                k = 1;
                break;
            }
        }
    }
    if (k == 0) {
        hands.push_back(newOne);
    }

    return hands;
    
}


int main() {
    string filename;
    filename = "inputs/07.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    pair<string, int> p;
    vector<pair<string, int>> orderedA, orderedB;

    int c;
    while (getline(inputFile, line)) {
        p = split(line, ' ');
        orderedA = insertHand(orderedA, p, 1);
        orderedB = insertHand(orderedB, p, 2);
    }
    inputFile.close();

    int solA = 0, solB = 0;
    for (int k = 0; k < orderedA.size(); k++) {
        solA += orderedA[k].second * (k+1);
        solB += orderedB[k].second * (k+1);
    }
    cout << "a: " << solA << endl;
    cout << "b: " << solB << endl;



    return 0;
}