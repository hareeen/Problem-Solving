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

template <template <class, class, class...> class C, class K, class V, class... Args>
inline void increment(C<K, V, Args...>& container, const K& key, const V& value) {
    auto [iter, success] = container.emplace(key, value);
    if (!success) iter->second += value;
}

template <template <class, class, class...> class C, class K, class V, class... Args>
inline V get_with_default(const C<K, V, Args...>& container, const K& key, const V& defaultValue) {
    auto iter = container.find(key);
    return iter == container.end() ? defaultValue : iter->second;
}

template <template <class, class...> class C, class T, class... Args>
inline void compress(C<T, Args...>& container) {
    sort(iterall(container));
    container.erase(unique(iterall(container)), container.end());
}

class SegTree {
   public:
    int N;
    vector<int> vl, lz;

    SegTree() = default;

    explicit SegTree(int _N) {
        N = _N;
        vl.resize(4 * N + 1);
        lz.resize(4 * N + 1);
    }

    void propagate(int s, int e, int n) {
        vl[n] += lz[n];

        if (s != e) {
            int k = n << 1;
            lz[k] += lz[n];
            lz[k + 1] += lz[n];
        }

        lz[n] = 0;
    }

    void update(int s, int e, int n, int l, int r, int d) {
        propagate(s, e, n);

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lz[n] += d;
            propagate(s, e, n);
            return;
        }

        int m = s + e >> 1, k = n << 1;
        update(s, m, k, l, r, d);
        update(m + 1, e, k + 1, l, r, d);
        vl[n] = max(vl[k], vl[k + 1]);
    }
    inline void update(int l, int r, int d) {
        update(1, N, 1, l, r, d);
    }

    inline int query() {
        propagate(1, N, 1);
        return vl[1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<ti> points(N);
    map<pi, set<int>> mp;
    for (auto& [x, y, c] : points) {
        cin >> x >> y >> c;
        x *= 2, y *= 2, --c;
        mp[{x, y}].emplace(c);
    }

    for (auto& [_, S] : mp) {
        if (S.size() >= K) {
            cout << 0 << endl;
            return 0;
        }
    }

    int lo = 1, hi = 500010;
    using qi = tuple<int, int, int, int, int>;
    while (lo < hi) {
        const int L = (lo + hi) / 2;

        vector<qi> queries;
        queries.reserve(2 * N);

        vector<int> xzip, yzip;
        xzip.reserve(2 * N), yzip.reserve(2 * N);

        for (auto [x, y, c] : points) {
            queries.emplace_back(x - L, y - L, y + L, c, 1);
            queries.emplace_back(x + L + 1, y - L, y + L, c, -1);

            xzip.emplace_back(x - L);
            xzip.emplace_back(x + L + 1);
            yzip.emplace_back(y - L);
            yzip.emplace_back(y + L);
        }
        sort(iterall(queries));
        compress(xzip);
        compress(yzip);

        const int X = xzip.size(), Y = yzip.size();
        SegTree ST(Y);
        vector<multiset<pi>> appended(K);

        bool flag = false;
        auto qit = queries.begin();
        for (auto x : xzip) {
            while (qit != queries.end() && get<0>(*qit) == x) {
                auto [_, ys, ye, c, d] = *qit;

                ys = lower_bound(iterall(yzip), ys) - yzip.begin() + 1;
                ye = lower_bound(iterall(yzip), ye) - yzip.begin() + 1;

                int qs = ys, qe = ye;
                auto it = appended[c].lower_bound({ys, ye});
                if (d == 1) {
                    if (!appended[c].empty() && it != appended[c].begin()) qs = max(qs, prev(it)->second + 1);
                    if (it != appended[c].end()) qe = min(qe, it->first - 1);

                    appended[c].emplace_hint(it, ys, ye);
                } else {
                    if (it != appended[c].begin()) qs = max(qs, prev(it)->second + 1);
                    if (next(it) != appended[c].end()) qe = min(qe, next(it)->first - 1);

                    appended[c].erase(it);
                }

                if (qs <= qe) ST.update(qs, qe, d);
                ++qit;
            }

            // cout << L << " " << ST.query() << endl;
            if (ST.query() >= K) {
                flag = true;
                break;
            }
        }

        // cout << endl;
        if (flag)
            hi = L;
        else
            lo = L + 1;
    }

    cout << lo << endl;

    return 0;
}
