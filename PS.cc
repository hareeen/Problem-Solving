#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
   public:
    vector<uint> vl;
    vector<uint> ls, lm;
    int N;

    segTree() {
        vl.clear();
        ls.clear();
        lm.clear();
        N = 0;
    }

    segTree(int _N) {
        const size_t sz = (1 << 20) + 1;
        vl.resize(sz);
        ls.resize(sz);
        lm.resize(sz, 1);

        N = _N;
    }

    void propagate(int s, int e, int n) {
        if (lm[n] == 1 && ls[n] == 0) return;
        vl[n] = vl[n] * lm[n] + static_cast<uint>(e - s + 1) * ls[n];

        if (s != e) {
            lm[n * 2] *= lm[n], ls[n * 2] *= lm[n];
            ls[n * 2] += ls[n];
            lm[n * 2 + 1] *= lm[n], ls[n * 2 + 1] *= lm[n];
            ls[n * 2 + 1] += ls[n];
        }

        lm[n] = 1, ls[n] = 0;
    }

    void update(int s, int e, int n, const int l, const int r, const uint us,
                const uint um) {
        propagate(s, e, n);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lm[n] = um, ls[n] = us;
            propagate(s, e, n);
            return;
        }

        int m = s + e >> 1;
        update(s, m, n * 2, l, r, us, um);
        update(m + 1, e, n * 2 + 1, l, r, us, um);
        vl[n] = vl[n * 2] + vl[n * 2 + 1];
    }

    void update(const int l, const int r, const uint us, const uint um) {
        update(1, N, 1, l, r, us, um);
    }

    uint query(int s, int e, int n, const int l, const int r) {
        propagate(s, e, n);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[n];

        int m = s + e >> 1;
        return query(s, m, n * 2, l, r) + query(m + 1, e, n * 2 + 1, l, r);
    }

    uint query(const int l, const int r) { return query(1, N, 1, l, r); }
};

namespace HLD {

int N;
vector<vector<int>> adj, tr, spt;
vector<int> dep, sz;
vector<int> hld, hc, hld_tp;
vector<int> in, out;
segTree sT;

int hld_sz, order;

void init(int _N) {
    N = _N;

    adj.resize(N + 1), tr.resize(N + 1), spt.resize(N + 1);
    dep.resize(N + 1), sz.resize(N + 1);

    hld.resize(N + 1), hc.resize(N + 1);
    in.resize(N + 1), out.resize(N + 1);

    sT = segTree(N);
}

void emplace_edge(int u, int v) {
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
}

// dfs1: adj reconstruct & size
void dfs1(int h, int p) {
    sz[h] = 1;
    for (auto t : adj[h]) {
        if (t == p) continue;

        dfs1(t, h);
        sz[h] += sz[t];
        tr[h].emplace_back(t);
    }

    if (p == -1) adj.clear();
}

// dfs2: sparse table & depth
void dfs2(int h, int p) {
    if (p == -1)
        dep[h] = 1;
    else
        dep[h] = dep[p] + 1, spt[h].emplace_back(p);

    for (int i = 1; (1 << i) < dep[h]; i++)
        spt[h].emplace_back(spt[spt[h][i - 1]][i - 1]);
    for (auto t : tr[h]) dfs2(t, h);
}

// dfs3: HLD & dfs ordering
void dfs3(int h, bool _ini = false) {
    if (_ini) {
        order = 0;
        hld_sz = 0;
        hld[h] = 0;
        hld_tp.emplace_back(h);
    }

    in[h] = ++order;

    for (auto t : tr[h]) {
        if (2 * sz[t] >= sz[h]) {
            hld[t] = hld[h];
            hc[h] = t;
            dfs3(t);
            break;
        }
    }

    for (auto t : tr[h]) {
        if (2 * sz[t] < sz[h]) {
            hld[t] = ++hld_sz;
            hld_tp.emplace_back(t);
            dfs3(t);
        }
    }

    out[h] = order;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);

    int p = spt[v].size() - 1;
    while (dep[u] < dep[v]) {
        while (dep[v] - (1 << p) < dep[u]) --p;
        v = spt[v][p];
    }

    p = spt[v].size() - 1;
    while (true) {
        if (u == v) return v;
        if (spt[u][0] == spt[v][0]) return spt[v][0];
        while (spt[u][p] == spt[v][p]) --p;
        u = spt[u][p], v = spt[v][p];

        p = min(p, static_cast<int>(spt[v].size()) - 1);
    }
}

int getChild(int u, int v) {
    int p = spt[v].size() - 1;
    while (true) {
        if (spt[v][0] == u) return v;
        while (dep[v] - (1 << p) <= dep[u]) --p;
        v = spt[v][p];
    }
}

void s_update(int v, const uint s, const uint m) {
    sT.update(in[v], out[v], s, m);
}

void p_update(int u, int v, const uint s, const uint m, bool _ini = false) {
    if (_ini) {
        if (dep[u] > dep[v]) swap(u, v);
        auto L = lca(u, v);
        if (u != L) p_update(getChild(L, u), u, s, m);
        p_update(L, v, s, m);
        return;
    }

    if (hld[u] == hld[v]) {
        sT.update(in[u], in[v], s, m);
        return;
    }

    sT.update(in[hld_tp[hld[v]]], in[v], s, m);
    p_update(u, spt[hld_tp[hld[v]]][0], s, m);
}

uint s_query(int v) { return sT.query(in[v], out[v]); }

uint p_query(int u, int v, bool _ini = false) {
    if (_ini) {
        if (dep[u] > dep[v]) swap(u, v);

        auto L = lca(u, v);
        uint ret = 0;
        if (u != L) ret += p_query(getChild(L, u), u);
        ret += p_query(L, v);
        return ret;
    }

    if (hld[u] == hld[v]) return sT.query(in[u], in[v]);

    return sT.query(in[hld_tp[hld[v]]], in[v]) +
           p_query(u, spt[hld_tp[hld[v]]][0]);
}

}  // namespace HLD

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    HLD::init(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        HLD::emplace_edge(u, v);
    }

    HLD::dfs1(1, -1);
    HLD::dfs2(1, -1);
    HLD::dfs3(1, true);

    for (int i = 0; i < Q; i++) {
        uint qt, x, y, v;
        cin >> qt;

        switch (qt) {
            case 1:
                cin >> x >> v;
                HLD::s_update(x, v, 1);
                break;

            case 2:
                cin >> x >> y >> v;
                HLD::p_update(x, y, v, 1, true);
                break;

            case 3:
                cin >> x >> v;
                HLD::s_update(x, 0, v);
                break;

            case 4:
                cin >> x >> y >> v;
                HLD::p_update(x, y, 0, v, true);
                break;

            case 5:
                cin >> x;
                cout << HLD::s_query(x) << '\n';
                break;

            case 6:
                cin >> x >> y;
                cout << HLD::p_query(x, y, true) << '\n';
                break;

            default:
                break;
        }
    }

    return 0;
}