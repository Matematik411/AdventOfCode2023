#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>

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
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    // if any is empty
    for (int i = 0; i < elems.size(); i++) {
        if (elems[i] != "") {
            real.push_back(elems[i]);
        }
    }
    // if whitespace after delim
    for (int i = 1; i < real.size(); i++) {
        real[i] = real[i].substr(1);
    }
    return real;
}

pair<long double, long double> calculate(long double x1, long double y1, long double vx1, long double vy1,
    long double x2, long double y2, long double vx2, long double vy2) {
        long double val1 = (vy1 / vx1) - (vy2 / vx2);
        long double val2 = y2 - y1 + (vy1 / vx1)*x1 - (vy2 / vx2)*x2;

        long double x = val2 / val1;
        long double y = (vy1 / vx1) * (x - x1) + y1;
        return {x, y};
    }


int main() {
    string filename;
    filename = "inputs/24.txt";


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    vector< vector<long long int> > data;

    vector<string> info, left, right;
    long long int k = 0;
    while (getline(inputFile, line)) {
        info = split(line, '@');
        left = split(info[0], ',');
        right = split(info[1], ',');
        data.push_back({});
        for (long long int i = 0; i < 3; i++) {
            data[k].push_back(stoll(left[i]));
        }
        for (long long int i = 0; i < 3; i++) {
            data[k].push_back(stoll(right[i]));
        }
        k += 1;
    }


    int N = data.size();

    vector<long long int> fst, snd;
    long double solA = 0;
    long double posMin = 200000000000000, posMax = 400000000000000;
    long double val1, val2, x, y;


    pair<long double, long double> res;
    for ( int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            fst = data[i];
            snd = data[j];

            res = calculate(fst[0], fst[1], fst[3], fst[4], snd[0], snd[1], snd[3], snd[4]);
            x = res.first;
            y = res.second;

            if ((x < posMin) || (x > posMax) || (y < posMin) || (y > posMax)) {
                continue;
            }

            if ( fst[3] > 0 ) {
                if (x < fst[0]) {
                    continue;
                }
            }
            if ( fst[3] < 0 ) {
                if (x > fst[0]) {
                    continue;
                }
            }
            if ( fst[4] > 0 ) {
                if (y < fst[1]) {
                    continue;
                }
            }
            if ( fst[4] < 0 ) {
                if (y > fst[1]) {
                    continue;
                }
            }
            if ( snd[3] > 0 ) {
                if (x < snd[0]) {
                    continue;
                }
            }
            if ( snd[3] < 0 ) {
                if (x > snd[0]) {
                    continue;
                }
            }
            if ( snd[4] > 0 ) {
                if (y < snd[1]) {
                    continue;
                }
            }
            if ( snd[4] < 0 ) {
                if (y > snd[1]) {
                    continue;
                }
            }

            solA += 1;


            
        }
    }
    cout << "a: " << solA << endl;
    cout << "part 2 in mathematica notebook :)" << endl;
    // this is only part 1
    // part 2 system solved in mathematica notebook

    inputFile.close();

    
    return 0;
}