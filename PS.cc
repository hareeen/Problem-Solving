#include <bits/stdc++.h>

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

class Tree {
public:
    int N;
    int hldn, order;
    vector<vector<int>> adj, tr;
    vector<int> par;
    vector<int> dep, sz, in, out;
    vector<int> hld, hld_sz, hld_tp;
    vector<int> clr_dist, clr;
    vector<deque<pi>> hld_clr;

    Tree(int _N, int C) {
        N = _N;
        hldn = order = 0;
        adj.resize(N + 1), tr.resize(N + 1), par.resize(N + 1);
        dep.resize(N + 1), sz.resize(N + 1, 1), in.resize(N + 1), out.resize(N + 1);
        hld.resize(N + 1);

        clr_dist.resize(N + 1), clr.resize(C + 1);
        clr[0] = N - 1, clr_dist[N - 1] = 1;
        clr_dist[0] += C;
    }

    void emplace_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    void newchain(int v) {
        hld[v] = hldn++;
        hld_tp.emplace_back(v);
        hld_sz.emplace_back(1);
        hld_clr.emplace_back(deque<pi>(1, pi(0, 0)));
    }

    // gen: tr, sz, in, out, dep
    void dfs1(int h, int p) {
        in[h] = ++order;
        par[h] = p;
        if (p) {
            tr[p].emplace_back(h);
            dep[h] = dep[p] + 1;
        } else {
            newchain(h);
            hld_sz[0] = 0;
        }

        for (auto t : adj[h]) {
            if (t == p) continue;
            dfs1(t, h);
        }

        out[h] = order;
        if (p) sz[p] += sz[h];
    }

    // gen: hld
    void dfs2(int h) {
        for (auto t : tr[h]) {
            if (sz[t] * 2 >= sz[h]) {
                hld[t] = hld[h];
                hld_sz[hld[h]]++;
                dfs2(t);
                break;
            }
        }

        for (auto t : tr[h]) {
            if (sz[t] * 2 < sz[h]) {
                newchain(t);
                dfs2(t);
            }
        }
    }

    void dfs(int root) {
        dfs1(root, 0);
        dfs2(root);

        for (int i = 0; i < hldn; i++) hld_clr[i][0].second = hld_sz[i];
    }

    void updateclr(int c, int d) {
        // cout << "UPDATECLR(" << c << ", " << d << ")" << endl;
        clr_dist[clr[c]]--;
        clr[c] += d;
        clr_dist[clr[c]]++;
    }

    void update(int v, int c) {
        // cout << "UPDATE(" << v << ", " << c << ")" << endl;
        if (v == 0) return;

        int hn = hld[v];
        int dd = dep[v] - dep[hld_tp[hn]] + 1;
        if (par[hld_tp[hn]] == 0) dd--;
        // cout << "dd: " << dd << endl;
        int ct = 0;
        while (ct < dd) {
            auto &ft = hld_clr[hn].front();

            if (ft.second > dd - ct) {
                ft.second -= (dd - ct);
                updateclr(ft.first, ct - dd);
                ct = dd;
            } else {
                updateclr(ft.first, -ft.second);
                ct += ft.second;
                hld_clr[hn].pop_front();
            }
        }

        hld_clr[hn].emplace_front(c, dd);
        updateclr(c, dd);
        update(par[hld_tp[hn]], c);
    }

    int query(int m) {
        return clr_dist[m] - (clr[0] == m);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, C, Q;
    cin >> N >> C >> Q;

    auto tree = Tree(N, C);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree.emplace_edge(u, v);
    }
    tree.dfs(1);

    for (int i = 0; i < Q; i++) {
        int u, c, m;
        cin >> u >> c >> m;

        tree.update(u, c);
        cout << tree.query(m) << '\n';
    }

    return 0;
}

