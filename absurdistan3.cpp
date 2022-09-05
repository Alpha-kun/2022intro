#include<bits/stdc++.h>

#define watch(x) cout << (#x) << " is " << (x) << endl
using namespace std;

vector<pair<int, int>> G[100001];

bool marked[100001] = {false}, incircle[100001] = {false};
int from[100001];
int circlex, circley;

void dfs(int s, int edgeid) {
    marked[s] = true;
    for (int i = 0; i < G[s].size(); ++i) {
        int t = G[s][i].first;
        int edge = G[s][i].second;
        if (edge == edgeid) continue;
        if (s == circlex && t == circley) continue;
        if (marked[t]) {
            circlex = t;
            circley = s;
        } else {
            from[t] = s;
            dfs(t, edge);
        }
    }
}

void dfstree(int s) {
    marked[s] = true;
    for (int i = 0; i < G[s].size(); ++i) {
        if (!marked[G[s][i].first] && !incircle[G[s][i].first]) {
            cout << G[s][i].first << " " << s << endl;
            dfstree(G[s][i].first);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int u, v;
    for (int i = 0; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(make_pair(v, i));
        G[v].push_back(make_pair(u, i));
    }

    for (int i = 1; i < n; ++i) {
        if (!marked[i]) {
            dfs(i, -1);
            v = circley;
            while (true) {
                cout << v << " " << from[v] << endl;
                incircle[v] = true;
                v = from[v];
                if (v == circlex) {
                    cout << circlex << " " << circley << endl;
                    incircle[v] = true;
                    break;
                }
            }
        }

    }

    memset(marked, 0, sizeof(marked));
    for (int i = 1; i <= n; ++i) {
        if (incircle[i]) dfstree(i);
    }

    return 0;
}