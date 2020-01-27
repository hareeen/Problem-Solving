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
        vl[nd] = max(vl[nd * 2], vl[nd * 2 + 1]);
    }

    int query(int s, int e, int nd, const int l, const int r) {
        if (r < s || e < l) return -1;
        if (l <= s && e <= r) return vl[nd];
        return max(query(s, (s + e) / 2, nd * 2, l, r),
                   query((s + e) / 2 + 1, e, nd * 2 + 1, l, r));
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

void dfs1(int here, int par) {
    sz[here] = 1;
    for (auto there : adj[here]) {
        if (par == there) continue;

        tr[here].emplace_back(there);
        dfs1(there, here);
        sz[here] += sz[there];
    }

    if (par == -1) adj.clear();
}

void dfs2(int here, int par) {
    if (par == -1) {
        dep[here] = 1;
    } else {
        dep[here] = dep[par] + 1;
        spt[here].emplace_back(par);
    }

    for (int i = 1; (1 << i) < dep[here]; i++)
        spt[here].emplace_back(spt[spt[here][i - 1]][i - 1]);

    for (auto there : tr[here]) dfs2(there, here);
}

void dfs3(int here, bool _init = false) {
    if (_init) {
        order = 0;
        hld_sz = 0;
        hld_tp.emplace_back(here);
    }

    in[here] = ++order;

    for (auto there : tr[here]) {
        if (sz[there] * 2 >= sz[here]) {
            hld[there] = hld[here];
            hc[here] = there;
            dfs3(there);
            break;
        }
    }

    for (auto there : tr[here]) {
        if (sz[there] * 2 < sz[here]) {
            hld[there] = ++hld_sz;
            hld_tp.emplace_back(there);
            dfs3(there);
        }
    }

    out[here] = order;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);

    int pos = spt[v].size() - 1;
    while (dep[u] < dep[v]) {
        while ((1 << pos) > dep[v] - dep[u]) --pos;
        v = spt[v][pos];
    }

    while (true) {
        if (u == v) return u;
        if (spt[u][0] == spt[v][0]) return spt[u][0];

        pos = spt[u].size() - 1;
        while (spt[u][pos] == spt[v][pos]) --pos;

        u = spt[u][pos];
        v = spt[v][pos];
    }
}

void update(int u, int v, const int d) {
    if (dep[u] > dep[v]) swap(u, v);
    sT.update(1, N, 1, in[v], d);
}

int query(int u, int v, bool disjoint = false) {
    if (disjoint) {
        auto L = lca(u, v);
        return max(query(u, L), query(v, L));
    }

    if (u == v) return 0;
    if (dep[u] > dep[v]) swap(u, v);

    if (hld[hc[u]] == hld[v]) return sT.query(1, N, 1, in[hc[u]], in[v]);

    return max(query(u, spt[hld_tp[hld[v]]][0]),
               sT.query(1, N, 1, in[hld_tp[hld[v]]], in[v]));
}

};  // namespace HLD

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pi> edg(N);
    vector<int> wei(N);
    for (int i = 1; i < N; i++) cin >> edg[i].first >> edg[i].second >> wei[i];

    HLD::init(N);
    for (auto [u, v] : edg) HLD::emplace_edge(u, v);

    HLD::dfs1(1, -1);
    HLD::dfs2(1, -1);
    HLD::dfs3(1, true);

    for (int i = 1; i < N; i++)
        HLD::update(edg[i].first, edg[i].second, wei[i]);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int j, c;
            cin >> j >> c;
            HLD::update(edg[j].first, edg[j].second, c);
        } else {
            int u, v;
            cin >> u >> v;
            cout << HLD::query(u, v, true) << '\n';
        }
    }

    return 0;
}