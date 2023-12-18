#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <numeric>
#include <map>
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
    vector<string> elems, real;
    split(s, delim, back_inserter(elems));
    return elems;
}



int main() {
    string filename;
    filename = "inputs/18.txt";

    map<string, pair<int, int>> dirs;
    dirs["R"] = {1, 0};
    dirs["L"] = {-1, 0};
    dirs["D"] = {0, 1};
    dirs["U"] = {0, -1};


    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    int N = 1000;
    string line;
    vector< string > data;

    vector<string> info;
    int d, x = 0, y = 0;
    int maxX = -N, maxY = -N, minX = N, minY = N;
    while (getline(inputFile, line)) {
        data.push_back(line);
        info = split(line, ' ');
        d = stoi( info[1] );
        // cout << d << endl;
        
        for (int i = 0; i < d; i++) {
            // cout << "here" << endl;
            x = x + dirs[info[0]].first;
            y = y + dirs[info[0]].second;
            // cout << x << "-" << y << endl;
            if (x < minX) {
                minX = x;
            }
            if (x > maxX) {
                maxX = x;
            }
            if (y < minY) {
                minY = y;

            }
            if (y > maxY) {
                maxY = y;
            }
        }
    }
    cout << maxX << endl;
    cout << maxY << endl;
    cout << minX << endl;
    cout << minY << endl;

    int H = maxY - minY + 1 + 2;
    int W = maxX - minX + 1 + 2;

    vector< vector<char> > dig;
    for (int j = 0; j < H; j++) {
        vector<char> row;
        for (int i = 0; i < W; i++) {
            row.push_back('.');
        }
        dig.push_back(row);
    }
    x = -minX + 1;
    y = -minY + 1;

    for (string edge : data) {
        info = split(edge, ' ');
        d = stoi( info[1] );
        // cout << d << endl;
        
        for (int i = 0; i < d; i++) {
            // cout << "here" << endl;
            x = x + dirs[info[0]].first;
            y = y + dirs[info[0]].second;
            // cout << x << "-" << y << endl;
            dig[y][x] = '#';
        }
    }
    
    // for (auto a : dig) {
    //     for (auto b : a) {
    //         cout << b;
    //     }
    //     cout << endl;
    // }

    vector<pair<int, int>> q, visited;
    q.push_back({0, 0});
    visited.push_back({0, 0});
    pair<int, int> curr, newLoc;
    int outside = 1;

    while (q.size())
    {
        curr = q[0];
        q.erase(q.begin());

        if (outside % 1000 == 0) {
            cout << outside << endl;
        }

        for (char dir : "RLDU") {
            if (dir == '\0') {
                continue;
            }
            // cout << dir << "...." << string( 1, dir ) << "....." <<  dirs[string( 1, dir )].first << endl;
            x = curr.first + dirs[string( 1, dir )].first;
            // cout << "PRVIIIIIII " << xN << endl;
            y = curr.second + dirs[string( 1, dir )].second;
            // cout << xN << " !! " << yN << endl;

            if ((x < 0) || (y < 0) || (x >= W) || (y >= H)) {
                continue;
            }

            newLoc = {x, y};
            if (find(visited.begin(), visited.end(), newLoc) != visited.end()) {
                continue;
            }
            if (dig[y][x] == '.') {
                outside += 1;
                q.push_back(newLoc);
                visited.push_back(newLoc);
            }
        }
    }

    // ends correctly after outside > 109000
    cout << "a: " << W*H - outside << endl;
    

    inputFile.close();

    
    return 0;
}