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

const int imin = numeric_limits<int>::min();
const int iMax = numeric_limits<int>::max();

int apply(int x, pi app) {
    auto[s, e] = app;
    if (x < s) return s;
    if (x > e) return e;
    else return x;
}

pi apply(pi p, pi app) {
    auto[s, e] = p;
    auto[sa, ea] = app;
    if (e < sa) return {sa, sa};
    if (ea < s) return {ea, ea};
    return {max(s, sa), min(e, ea)};
}

class segTree {
public:
    vector<int> vl;
    vector<pi> lz;
    int N{};

    segTree() = default;

    explicit segTree(int n) {
        const size_t sz = (1u << 22u) + 1;
        vl.resize(sz);
        lz.resize(sz);
        N = n;
    }

    void propagate(int s, int e, int n) {
        if (lz[n] == pi(imin, iMax)) return;
        vl[n] = apply(vl[n], lz[n]);

        if (s != e) {
            lz[n * 2] = apply(lz[n * 2], lz[n]);
            lz[n * 2 + 1] = apply(lz[n * 2 + 1], lz[n]);
        }

        lz[n] = pi(imin, iMax);
    }

    void update(int s, int e, int n, int l, int r, pi u) {
        propagate(s, e, n);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lz[n] = u;
            propagate(s, e, n);
            return;
        }

        update(s, (s + e) / 2, n * 2, l, r, u);
        update((s + e) / 2 + 1, e, n * 2 + 1, l, r, u);
    }

    void update(int l, int r, pi u) {
        update(1, N, 1, l, r, u);
    }

    void propFill(int s, int e, int n, vector<int> &target) {
        propagate(s, e, n);
        if (s == e) {
            target.emplace_back(vl[n]);
            return;
        }

        propFill(s, (s + e) / 2, n * 2, target);
        propFill((s + e) / 2 + 1, e, n * 2 + 1, target);
    }

    void propFill(vector<int> &target) {
        propFill(1, N, 1, target);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    auto sT = segTree(N);
    for (int i = 0; i < K; i++) {
        int op, l, r, h;
        cin >> op >> l >> r >> h;
        ++l, ++r;

        if (op == 1) sT.update(l, r, {h, iMax});
        else sT.update(l, r, {imin, h});
    }

    vector<int> res;
    sT.propFill(res);
    copy(iterall(res), ostream_iterator<int>(cout, "\n"));

    return 0;
}