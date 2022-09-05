#include <bits/stdc++.h>

#define INF INT_MAX

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct Edge {
    int v, w, cap, cost, f;

    Edge(int a, int b, int c, int d) : v(a), w(b), cap(c), cost(d), f(0) {}

    int other(int s) { return s == v ? w : v; }

    int getRez(int s) {
        return s == v ? cap - f : f;
    }

    int getCost(int s) {
        return s == v ? cost : -cost;
    }

    void addFlow(int s, int d) {
        if (s == v) f += d;
        else f -= d;
    }
};

int N;
vector<Edge *> G[205];
vector<int> dist;
vector<int> from;
vector<Edge *> arc;

void spfa(int s) {
    dist = vector<int>(N, INF);
    from = vector<int>(N, -1);
    arc = vector<Edge *>(N, nullptr);
    vector<bool> inq(N, false);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (Edge *uv: G[u]) {
            int v = uv->other(u);
            if (uv->getRez(u) > 0 && dist[u] + uv->getCost(u) < dist[v]) {
                dist[v] = dist[u] + uv->getCost(u);
                from[v] = u;
                arc[v] = uv;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

pll MCMF(int s, int t, int p) {
    ll maxflow = 0, mincost = 0;
    while (true) {
        spfa(s);
        if (dist[t] == INF) break;
        //find bottleneck flow
        int flow = INF, cur = t;
        while (cur != s) {
            int pre = from[cur];
            flow = min(flow, arc[cur]->getRez(pre));
            cur = pre;
        }
        //add flow
        cur = t;
        while (cur != s) {
            int pre = from[cur];
            arc[cur]->addFlow(pre, flow);
            cur = pre;
        }
        maxflow += flow;
        mincost += flow * dist[t];
        if (maxflow >= p) break;
    }
    return make_pair(maxflow, mincost);
}

int main() {
    //try KACTL's min cost max flow after this
    int n;
    cin >> n;
    N = 2 * n + 3;
    vector<pii> ppl;
    int s, d;
    for (int i = 0; i < n; ++i) {
        cin >> s >> d;
        ppl.push_back({s, d});
    }
    sort(ppl.begin(), ppl.end());

    vector<Edge *> elst;
    for (int i = 1; i <= n; ++i) {
        Edge *e = new Edge(0, i, ppl[i - 1].second - (i == n ? 0 : 1), 0);
        G[0].push_back(e);
        G[i].push_back(e);
        elst.push_back(e);
    }
    for (int i = 1; i <= n; ++i) {
        Edge *e = new Edge(n + i, 2 * n + 1, 1, 0);
        G[n + i].push_back(e);
        G[2 * n + 1].push_back(e);
        elst.push_back(e);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j) {
            Edge *e = new Edge(i, n + j, 1, ppl[i - 1].first ^ ppl[j - 1].first);
            G[i].push_back(e);
            G[n + j].push_back(e);
            elst.push_back(e);
        }
    }

    //min cost
    pll mcmf = MCMF(0, 2 * n + 1, INF);
    if (mcmf.first != n - 1) assert(false);
    cout << mcmf.second << ' ';

    //max cost
    for (Edge *e: elst) {
        e->f = 0;
        if (e->v <= n && e->w >= n + 1) e->cost = -e->cost;
    }
    mcmf = MCMF(0, 2 * n + 1, INF);
    if (mcmf.first != n - 1) assert(false);
    cout << -mcmf.second << endl;

    return 0;
}
