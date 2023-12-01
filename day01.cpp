#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctype.h>
#include <algorithm>

using namespace std;



int main() {
    string filename;
    filename = "inputs/01.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    std::vector< string > data;
    while (getline(inputFile, line)) {
        data.push_back(line);

    }
    inputFile.close();

    vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int sumA = 0, sumB = 0, fstA, sndA, fst, snd;
    string word = "------", here;
    for (auto x : data) {
        fstA = -1;
        sndA = -1;
        fst = -1;
        snd = -1;
        for (auto y  : x) {
            if (isdigit(y)) {
                if (fstA == -1) {
                    fstA = y - '0';
                }
                if (fst == -1) {
                    fst = y - '0';
                }
                sndA = y - '0';
                snd = y - '0';
            }
            else {
                word += y;
                here = "";

                if (std::find(numbers.begin(), numbers.end(), word.substr(word.size() - 3)) != numbers.end() ) {
                    here = word.substr(word.size() - 3);
                }
                if (std::find(numbers.begin(), numbers.end(), word.substr(word.size() - 4)) != numbers.end()  ) {
                    here = word.substr(word.size() - 4);
                }
                if (std::find(numbers.begin(), numbers.end(), word.substr(word.size() - 5)) != numbers.end()  ) {
                    here = word.substr(word.size() - 5);
                }
                if (here.size()) {
                    auto curr = find(numbers.begin(), numbers.end(), here);
                    int val = curr - numbers.begin() + 1;
                    if (fst == -1) {
                        fst = val;
                    }
                    snd = val;
                }
            }

        }

        sumA += 10*fstA + sndA;
        sumB += 10*fst + snd;
    }

    cout << "a: " << sumA << endl;
    cout << "b: " << sumB << endl;



    return 0;
}