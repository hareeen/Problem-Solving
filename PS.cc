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

class SegTree {
   public:
    int N{};
    vector<i64> su, vl, lf, rg;

    SegTree() = default;
    explicit SegTree(int _N) {
        N = _N;
        su.resize(4 * N + 1);
        vl.resize(4 * N + 1);
        lf.resize(4 * N + 1);
        rg.resize(4 * N + 1);
    }

    void init(int s, int e, int n) {
        su[n] = 1LL * (e - s + 1) * (-N);

        if (s != e) {
            int m = (s + e) / 2, k = n * 2;
            init(s, m, k);
            init(m + 1, e, k + 1);
        }
    }
    void init() { init(1, N, 1); }

    void update(int s, int e, int n, int t) {
        if (t < s || e < t) return;
        if (s == e) {
            su[n] = vl[n] = lf[n] = rg[n] = 1;
            return;
        }

        int m = (s + e) / 2, k = n * 2;
        update(s, m, k, t);
        update(m + 1, e, k + 1, t);

        su[n] = su[k] + su[k + 1];
        lf[n] = max(lf[k], su[k] + lf[k + 1]);
        rg[n] = max(rg[k + 1], su[k + 1] + rg[k]);
        vl[n] = max({vl[k], vl[k + 1], rg[k] + lf[k + 1]});
    }
    void update(int t) { update(1, N, 1, t); }

    i64 query() { return vl[1]; }
};

bool process() {
    int N;
    cin >> N;

    if (!N) return false;

    vector<pli> hi(N);
    for (int i = 0; i < N; i++) {
        cin >> hi[i].first;
        hi[i].second = i + 1;
    }
    sort(iterall(hi), greater<>());

    i64 ans = 0;
    SegTree ST(N);
    ST.init();
    for (const auto& [h, i] : hi) {
        ST.update(i);
        ans = max(ans, ST.query() * h);
    }

    cout << ans << '\n';

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    process();

    return 0;
}
