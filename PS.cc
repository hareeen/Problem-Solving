#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class segTree {
   private:
    vector<int> vl;

   public:
    segTree() { vl.resize(262144 + 1); }

    void update(int s, int e, int nd, const int t, const int d) {
        if (t < s || e < t) return;
        if (s == e) {
            vl[nd] = d;
            return;
        }

        update(s, (s + e) / 2, nd * 2, t, d);
        update((s + e) / 2 + 1, e, nd * 2 + 1, t, d);
        vl[nd] = vl[nd * 2] + vl[nd * 2 + 1];
    }

    int query(int s, int e, int nd, const int l, const int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[nd];
        return query(s, (s + e) / 2, nd * 2, l, r) +
               query((s + e) / 2 + 1, e, nd * 2 + 1, l, r);
    }
};

namespace HLD {

int N;
vector<vector<int>> adj, tr, spt;
vector<int> dep, sz;
vector<int> hld, hc, hld_tp;
vector<int> in, out;
segTree sT;

int hld_sz = 0, order = 0;

void init(const int _N) {
    N = _N;

    adj.resize(N + 1), tr.resize(N + 1), spt.resize(N + 1);
    dep.resize(N + 1), sz.resize(N + 1);

    hld.resize(N + 1), hc.resize(N + 1);
    in.resize(N + 1), out.resize(N + 1);

    sT = segTree();
}

void emplace_edge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
}

// Make Tree ADJ & Subtree size
void dfs1(int h, int p) {
    sz[h] = 1;
    for (auto t : adj[h]) {
        if (p == t) continue;

        dfs1(t, h);
        tr[h].emplace_back(t);
        sz[h] += sz[t];
    }
}

// Depth & Sparse Table
void dfs2(int h, int p) {
    if (p == -1) {
        dep[h] = 1;
    } else {
        dep[h] = dep[p] + 1;
        spt[h].emplace_back(p);
    }

    for (int i = 1; (1 << i) < dep[h]; i++)
        spt[h].emplace_back(spt[spt[h][i - 1]][i - 1]);

    for (auto t : tr[h]) dfs2(t, h);
}

// HLD
void dfs3(int h, bool _ini = false) {
    if (_ini) {
        order = 0, hld_sz = 0;
        hld[h] = 0;
        hld_tp.emplace_back(h);
    }

    in[h] = ++order;

    for (auto t : tr[h]) {
        if (sz[t] * 2 >= sz[h]) {
            hld[t] = hld[h];
            hc[h] = t;
            dfs3(t);
            break;
        }
    }

    for (auto t : tr[h]) {
        if (sz[t] * 2 < sz[h]) {
            hld[t] = ++hld_sz;
            hld_tp.emplace_back(t);
            dfs3(t);
        }
    }

    out[h] = order;
}

void update(int t, int d) { sT.update(1, N, 1, in[t], d); }

int lca(int a, int b) {
    if (dep[a] > dep[b]) swap(a, b);

    auto p = spt[b].size() - 1;
    while (dep[a] < dep[b]) {
        while (dep[b] - dep[a] < (1 << p)) --p;
        b = spt[b][p];
    }

    p = spt[b].size() - 1;
    while (true) {
        if (a == b) return a;
        if (spt[a][0] == spt[b][0]) return spt[a][0];

        p = min(p, spt[b].size() - 1);
        while (spt[a][p] == spt[b][p]) --p;
        a = spt[a][p], b = spt[b][p];
    }
}

int query(int a, int b, bool _ini = false) {
    if (_ini) {
        auto l = lca(a, b);
        return query(l, a) + query(l, b) - query(l, l);
    }

    if (hld[a] == hld[b]) return sT.query(1, N, 1, in[a], in[b]);

    return query(a, spt[hld_tp[hld[b]]][0]) +
           sT.query(1, N, 1, in[hld_tp[hld[b]]], in[b]);
}

};  // namespace HLD

class disjointSet {
   private:
    vector<int> uf;

   public:
    disjointSet(int N) {
        uf.clear();
        for (int i = 0; i <= N; i++) uf.push_back(i);
    }
    int find(int n) {
        if (n == uf[n]) return n;
        return uf[n] = find(uf[n]);
    }
    void merge(int u, int v) {
        uf[find(u)] = uf[find(v)];
        return;
    }
    bool isSameset(int u, int v) { return find(u) == find(v); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<int> we(N + 1);
    for (int i = 1; i <= N; i++) cin >> we[i];

    int M;
    cin >> M;

    vector<int> qryTp(M);
    vector<pi> qryPara(M);

    for (int i = 0; i < M; i++) {
        string s;
        cin >> s >> qryPara[i].first >> qryPara[i].second;
        if (s == "bridge") qryTp[i] = 0;
        if (s == "penguins") qryTp[i] = 1;
        if (s == "excursion") qryTp[i] = 2;
    }

    // adj Generation
    {
        HLD::init(N);

        auto dS = disjointSet(N);
        for (int i = 0; i < M; i++) {
            if (qryTp[i] != 0) continue;

            auto [u, v] = qryPara[i];
            if (dS.isSameset(u, v)) continue;

            dS.merge(u, v);
            HLD::emplace_edge(u, v);
        }

        for (int i = 2; i <= N; i++) {
            if (dS.isSameset(1, i)) continue;
            dS.merge(1, i);
            HLD::emplace_edge(1, i);
        }
    }

    HLD::dfs1(1, -1);
    HLD::dfs2(1, -1);
    HLD::dfs3(1, true);
    for (int i = 1; i <= N; i++) HLD::update(i, we[i]);

    auto dS = disjointSet(N);
    for (int i = 0; i < M; i++) {
        if (qryTp[i] == 0) {
            auto [u, v] = qryPara[i];

            if (dS.isSameset(u, v)) {
                cout << "no\n";
            } else {
                dS.merge(u, v);
                cout << "yes\n";
            }
        } else if (qryTp[i] == 1) {
            auto [v, x] = qryPara[i];
            HLD::update(v, x);
        } else {
            auto [u, v] = qryPara[i];
            if (!dS.isSameset(u, v))
                cout << "impossible\n";
            else
                cout << HLD::query(u, v, true) << '\n';
        }
    }

    return 0;
}