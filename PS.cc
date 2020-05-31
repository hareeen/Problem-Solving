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

class segTree {
public:
    vector<uint> vl;
    vector<uint> ls, lm;
    int N{};

    segTree() = default;

    explicit segTree(int _N) {
        const size_t sz = (1 << 19) + 1;
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

namespace TREE {
    int N, ord;
    uint xx;
    vector<vector<int>> tr;
    vector<int> in, out, par;
    random_device rd;
    mt19937 gen(rd());
    segTree sT1, sT2;

    void init(int _N) {
        N = _N;
        ord = 0;
        xx = 0;
        tr.resize(N + 1);
        in.resize(N + 1);
        out.resize(N + 1);
        par.resize(N + 1);
        par[1] = -1;
        sT1 = segTree(N);
        sT2 = segTree(N);
    }

    void emplace_edge(int p, int c) {
        tr[p].emplace_back(c);
    }

    void dfs(int h) {
        in[h] = ++ord;
        for (auto t:tr[h]) par[t] = h, dfs(t);
        out[h] = ord;
    }

    bool query(int u, int v) {
        if (u < 1 || v < 1) return true;
        return (sT1.query(in[u], in[u]) == sT1.query(in[v], in[v]) &&
                sT2.query(in[u], in[u]) == sT2.query(in[v], in[v]));
    }

    void update(int v) {
        uniform_int_distribution<int> dis(0, 10000);
        if (query(v, par[v])) {
            sT1.update(in[v], out[v], dis(gen), 1);
            sT2.update(in[v], out[v], dis(gen), 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    TREE::init(N);

    vector<int> pr;
    for (int i = 2; i <= N; i++) {
        int p;
        cin >> p;
        TREE::emplace_edge(p, i);
    }
    TREE::dfs(1);

    for (int i = 0; i < Q; i++) {
        int b, c, d, e;
        cin >> b >> c >> d;
        auto res = TREE::query(b, c);

        if (d) {
            if (res) TREE::update(b);
            else TREE::update(c);
        }

        // for(int j=1;j<=N;j++)
        cout << (res ? "YES" : "NO") << '\n';
    }

    return 0;
}