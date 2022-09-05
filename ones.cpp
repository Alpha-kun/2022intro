#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int a = 0;
        int cnt = 0;
        while (true) {
            a = (10 * a + 1) % n;
            cnt++;
            if (a == 0) break;
        }
        cout << cnt << endl;
    }
    return 0;
}
