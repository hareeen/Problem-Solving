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

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class Node {
public:
    int s, e;
    int v;
    Node *l, *r;

    Node() {
        s = e = v = 0;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _v) {
        s = _s, e = _e, v = _v;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _v, Node *_l, Node *_r) {
        s = _s, e = _e, v = _v;
        l = _l, r = _r;
    }
};

namespace psegTree {
    Node *init(int s, int e, const vector<int> &arr) {
        if (s == e)
            return new Node(s, e, arr[s]);
        else {
            auto l = init(s, (s + e) / 2, arr);
            auto r = init((s + e) / 2 + 1, e, arr);
            return new Node(s, e, l->v + r->v, l, r);
        }
    }

    Node *update(Node *h, const int t, const int d) {
        int s = h->s, e = h->e;
        if (t < s || e < t)
            return h;
        else if (s == e)
            return new Node(s, e, h->v + d, h->l, h->r);
        else {
            auto l = update(h->l, t, d);
            auto r = update(h->r, t, d);
            return new Node(s, e, l->v + r->v, l, r);
        }
    }

    int query(Node *h, const int l, const int r) {
        int s = h->s, e = h->e;
        if (r < s || e < l)
            return 0;
        else if (l <= s && e <= r)
            return h->v;
        else
            return query(h->l, l, r) + query(h->r, l, r);
    }
};

namespace TREE {

    int N;
    vector<int> adj[100001], tr[100001], spt[100001];
    vector<int> dep, sz;
    vector<int> in, out;
    vector<int> ord;
    vector<Node *> sT;

    int hld_sz, order;

    void init(int _N) {
        N = _N;

        dep.resize(N + 1), sz.resize(N + 1);

        in.resize(N + 1), out.resize(N + 1);

        vector<int> ini(N + 1);
        sT.emplace_back(psegTree::init(1, N, ini));
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

    // dfs3: dfs ordering
    void dfs3(int h, bool _ini = false) {
        if (_ini) {
            order = 0;
            hld_sz = 0;
        }

        in[h] = ++order;
        ord.emplace_back(h);
        for (auto t:tr[h]) dfs3(t);
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

    void seginit(const vector<int> &wcp) {
        for (int i = 1; i <= N; i++) {
            auto n = ord[i - 1];
            auto p = (n == 1 ? 0 : spt[n][0]);

            sT.emplace_back(psegTree::update(sT[in[p]], wcp[n - 1], 1));
        }
    }

    int solve(Node *t1, Node *t2, Node *t3, Node *t4, const int x) {
        if (!t1->l) return t1->s;

        auto v = t1->l->v + t2->l->v - t3->l->v - (t4 ? t4->l->v : 0);
        if (v < x) return solve(t1->r, t2->r, t3->r, t4 ? t4->r : nullptr, x - v);
        else return solve(t1->l, t2->l, t3->l, t4 ? t4->l : nullptr, x);
    }

    int solve(int u, int v, int t) {
        // cout << "asdf" << endl;
        auto l = lca(u, v);
        Node *t1 = sT[in[u]];
        Node *t2 = sT[in[v]];
        Node *t3 = sT[in[l]];
        Node *t4 = (l == 1 ? nullptr : sT[in[spt[l][0]]]);
        // cout << "asdf" << endl;
        return solve(t1, t2, t3, t4, t);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> wei(N), cpn, wcp(N);
    for (int i = 0; i < N; i++) cin >> wei[i];
    cpn = wei;
    sort(iterall(cpn));
    for (int i = 0; i < N; i++) wcp[i] = lower_bound(iterall(cpn), wei[i]) - cpn.begin() + 1;


    TREE::init(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        TREE::emplace_edge(u, v);
    }

    TREE::dfs1(1, -1);
    TREE::dfs2(1, -1);
    TREE::dfs3(1, true);

    TREE::seginit(wcp);

    for (int i = 0; i < Q; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        cout << cpn[TREE::solve(u, v, t) - 1] << '\n';
    }

    return 0;
}