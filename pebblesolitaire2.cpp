#include <bits/stdc++.h>

using namespace std;

int dp[1 << 23];

int f(int S) {
    if (dp[S] != -1) return dp[S];
    dp[S] = __builtin_popcount(S);
    for (int i = 0; i < 21; ++i) {
        if ((S & (1 << i)) != 0 && (S & (1 << (i + 1))) != 0 && (S & (1 << (i + 2))) == 0) {
            dp[S] = min(dp[S], f(S - (1 << i) - (1 << (i + 1)) + (1 << (i + 2))));
        }
        if ((S & (1 << i)) == 0 && (S & (1 << (i + 1))) != 0 && (S & (1 << (i + 2))) != 0) {
            dp[S] = min(dp[S], f(S + (1 << i) - (1 << (i + 1)) - (1 << (i + 2))));
        }
    }
    return dp[S];
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        int q = 0;
        for (int j = 0; j < 23; ++j) {
            q <<= 1;
            q += (s[j] == 'o' ? 1 : 0);
        }
        cout << f(q) << endl;
    }
    return 0;
}
