#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;


int main() {
    
    string line;
    vector< long long int > times = {50, 74, 86, 85, 50748685};
    vector< long long int > records = {242, 1017, 1691, 1252, 242101716911252};
    int solA = 1;

    for (int i = 0; i < 5; i++) {
        long long int T = times[i];

        // --------------------------------------------
        // with formula
        double t1 = (T + sqrt(T*T - 4*records[i]))/2;
        double t2 = (T - sqrt(T*T - 4*records[i]))/2;
        int t1Int = floor(t1);
        int t2Int = ceil(t2);
        int wins = t1Int - t2Int + 1;
        // --------------------------------------------
        // long long int wins = 0;
        // for (long long int charging = 0; charging < T; charging++) {
        //     long long int result = (T-charging)*charging;
        //     if (result > records[i]) {
        //         wins += 1;
        //     }
        // }
        if (i < 4) {
            solA *= wins;
        }
        else {
            cout << "b: " << wins << endl;
        }
    }
    cout << "a: " << solA << endl;

    return 0;
}
