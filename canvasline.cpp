#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, p;
    cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    cin >> p;
    vector<int> peg(p);
    for (int i = 0; i < p; ++i) {
        cin >> peg[i];
    }
    vector<int> cvs[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            if (l[i] <= peg[j] && peg[j] <= r[i]) cvs[i].push_back(peg[j]);
        }
        if (cvs[i].size() > 2) {
            cout << "impossible" << endl;
            return 0;
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (cvs[i].size() == 2) {
            continue;
        } else if (cvs[i].size() == 1) {
            if (cvs[i][0] == r[i]) {
                ans.push_back(r[i] - 1);
            } else {
                if (i < n - 1 && cvs[i + 1].size() < 2) {
                    ans.push_back(r[i]);
                    if (r[i] == l[i + 1])
                        cvs[i + 1].push_back(r[i]);
                } else {
                    ans.push_back(cvs[i][0] == r[i] - 1 ? r[i] - 2 : r[i] - 1);
                }
            }
        } else {
            if (i < n - 1 && cvs[i + 1].size() < 2) {
                ans.push_back(r[i] - 1);
                ans.push_back(r[i]);
                if (r[i] == l[i + 1])
                    cvs[i + 1].push_back(r[i]);
            } else {
                ans.push_back(r[i] - 2);
                ans.push_back(r[i] - 1);
            }
        }
    }
    cout << ans.size() << endl;
    for (int num: ans) {
        cout << num << endl;
    }
    return 0;
}
