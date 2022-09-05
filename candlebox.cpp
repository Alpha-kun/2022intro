#include <bits/stdc++.h>

using namespace std;

int main() {
    int d, r, t;
    cin >> d >> r >> t;
    for (int i = max(4, d); i < 1000; ++i) {
        int rc = i * (i + 1) / 2 - 6;
        int tc = (i - d) * (i - d + 1) / 2 - 3;
        if (tc > 0) {
            if (r - rc == tc - t) {
                cout << r - rc << endl;
            }
        }
    }
    return 0;
}
