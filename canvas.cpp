#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void testcase() {
    int n, s;
    cin >> n;
    priority_queue<ll, vector<ll>, greater<>> pq;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        pq.push(s);
    }
    ll ans = 0;
    while (pq.size() >= 2) {
        ll a = pq.top();
        pq.pop();
        ll b = pq.top();
        pq.pop();
        ans += a + b;
        pq.push(a + b);
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        testcase();
    }
    return 0;
}
