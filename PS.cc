#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

namespace TREE {
    int N;
    vector<vector<int>> spt;
    vector<vector<pi>> spM, adj, tr;
    vector<int> dep;

    void init(int _N) {
        N = _N;
        adj.resize(N + 1), spt.resize(N + 1), tr.resize(N + 1);
        spM.resize(N + 1);
        dep.resize(N + 1);
    }

    void emplace_edge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    //tr, dep gen
    void dfs1(int h, int p) {
        if (p == -1) dep[h] = 0;
        else dep[h] = dep[p] + 1;

        for (auto[t, w]:adj[h]) {
            if (p == t) continue;

            tr[h].emplace_back(t, w);
            dfs1(t, h);
        }
    }

    pi mer(pi a, pi b) {
        vector<int> v = {a.first, a.second, b.first, b.second};
        sort(iterall(v), greater<>());
        v.erase(unique(iterall(v)), v.end());
        return {v[0], v[1]};
    }

    //spt, spM gen
    void dfs2(int h, int p, int w) {
        if (p != -1) {
            spt[h].emplace_back(p);
            spM[h].emplace_back(w, -1);
            for (size_t i = 1; (1u << i) <= dep[h]; i++) {
                spt[h].emplace_back(spt[spt[h][i - 1]][i - 1]);
                spM[h].emplace_back(mer(spM[h][i - 1], spM[spt[h][i - 1]][i - 1]));
            }
        }

        for (auto[t, nw]:tr[h]) dfs2(t, h, nw);
    }

    ti lca(int u, int v) {
        if (dep[u] > dep[v]) return lca(v, u);

        pi ret = {-1, -1};
        if (dep[u] < dep[v]) {
            size_t p = spt[v].size() - 1;
            while (dep[u] < dep[v]) {
                while (dep[v] - (1u << p) < dep[u]) --p;
                ret = mer(ret, spM[v][p]);
                v = spt[v][p];
                p = min(spt[v].size() - 1, p);
            }
        }

        size_t p = spt[v].size() - 1;
        while (true) {
            if (u == v) return {u, ret.first, ret.second};
            if (spt[u][0] == spt[v][0]) {
                ret = mer(ret, spM[u][0]);
                ret = mer(ret, spM[v][0]);
                return {u, ret.first, ret.second};
            }

            while (spt[u][p] == spt[v][p]) --p;
            ret = mer(ret, spM[u][p]);
            ret = mer(ret, spM[v][p]);
            u = spt[u][p], v = spt[v][p];
            p = min(spt[v].size() - 1, p);
        }
    }

    bool isAdj(int u, int v) {
        if (dep[u] == dep[v]) return false;
        if (dep[u] > dep[v]) return isAdj(v, u);
        return spt[v][0] == u;
    }
}

class disjointSet {
public:
    int N{};
    vector<int> p;

    explicit disjointSet(int _N) {
        N = _N;
        p.resize(N + 1);
        for (int i = 0; i <= N; i++) p[i] = i;
    }

    int find(int u) {
        return p[u] = (p[u] == u ? u : find(p[u]));
    }

    void mer(int u, int v) {
        p[find(u)] = find(v);
    }

    bool sset(int u, int v) {
        return find(u) == find(v);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int V, E;
    cin >> V >> E;

    vector<ti> edges;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, u, v);
    }

    sort(iterall(edges));

    int totalW = 0, trE = 0;
    auto dS = disjointSet(V);
    TREE::init(V);
    for (auto[w, u, v]:edges) {
        if (dS.sset(u, v)) continue;
        totalW += w;
        ++trE;
        dS.mer(u, v);
        TREE::emplace_edge(u, v, w);
    }

    if (trE != V - 1) {
        cout << -1 << endl;
        return 0;
    }

    TREE::dfs1(1, -1);
    TREE::dfs2(1, -1, -1);

    int ans = numeric_limits<int>::max();
    for (auto[w, u, v]:edges) {
        if (TREE::isAdj(u, v)) continue;
        auto[L, M, sM] = TREE::lca(u, v);
        if (M == w) {
            if (sM == -1) continue;
            ans = min(ans, totalW + w - sM);
        } else {
            ans = min(ans, totalW + w - M);
        }
    }

    if (ans == numeric_limits<int>::max()) ans = -1;
    cout << ans << endl;

    return 0;
}