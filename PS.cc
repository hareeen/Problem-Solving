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
    vector<int> vl;
    vector<int> ls, lm;
    int N;

    segTree() {
        vl.clear();
        ls.clear();
        lm.clear();
        N = 0;
    }

    segTree(int _N) {
        const size_t sz = (1 << 19) + 1;
        vl.resize(sz);
        ls.resize(sz);
        lm.resize(sz, 1);

        N = _N;
    }

    void propagate(int s, int e, int n) {
        if (lm[n] == 1 && ls[n] == 0) return;
        vl[n] = vl[n] * lm[n] + (e - s + 1) * ls[n];

        if (s != e) {
            lm[n * 2] *= lm[n], ls[n * 2] *= lm[n];
            ls[n * 2] += ls[n];
            lm[n * 2 + 1] *= lm[n], ls[n * 2 + 1] *= lm[n];
            ls[n * 2 + 1] += ls[n];
        }

        lm[n] = 1, ls[n] = 0;
    }

    void update(int s, int e, int n, const int l, const int r, const int us,
                const int um) {
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
    void update(const int l, const int r, const int us, const int um) {
        update(1, N, 1, l, r, us, um);
    }

    void push0(const int l, const int r) { update(l, r, 0, 0); }
    void push1(const int l, const int r) { update(l, r, 1, 0); }
    void toggle(const int l, const int r) { update(l, r, 1, -1); }

    int query(int s, int e, int n, const int l, const int r) {
        propagate(s, e, n);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[n];

        int m = s + e >> 1;
        return query(s, m, n * 2, l, r) + query(m + 1, e, n * 2 + 1, l, r);
    }
    int query(const int l, const int r) { return query(1, N, 1, l, r); }

    optional<int> mex(int s, int e, int n) {
        propagate(s, e, n);
        if (vl[n] == e - s + 1) return nullopt;
        if (s == e) return make_optional(s);

        int m = s + e >> 1;
        if (auto res = mex(s, m, n * 2)) return res;
        return mex(m + 1, e, n * 2 + 1);
    }
    auto mex() { return mex(1, N, 1); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int Q;
    cin >> Q;

    vector<i64> com = {1, static_cast<i64>(1e18) + 2};

    vector<tli> queries(Q);
    for (int i = 0; i < Q; i++) {
        i64 t, l, r;
        cin >> t >> l >> r;
        ++r;
        queries[i] = {t, l, r};
        com.emplace_back(l);
        com.emplace_back(r);
    }

    sort(iterall(com));
    com.erase(unique(iterall(com)), com.end());

    int N = com.size();
    auto sT = segTree(N);
    for (auto [t, L, R] : queries) {
        int l = lower_bound(iterall(com), L) - com.begin() + 1;
        int r = lower_bound(iterall(com), R) - com.begin();

        if (t == 1) sT.push1(l, r);
        if (t == 2) sT.push0(l, r);
        if (t == 3) sT.toggle(l, r);

        cout << com[sT.mex().value() - 1] << '\n';
    }

    return 0;
}