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

vector<i64> pzip;

class segTree {
   public:
    vector<i64> vl, lz;
    size_t sz;

    segTree(size_t _sz) {
        vl.resize((1 << 20) + 1);
        lz.resize((1 << 20) + 1);
        sz = _sz;
    }

    void propagate(int s, int e, int n) {
        if (!lz[n]) return;
        vl[n] += (pzip[e] - pzip[s - 1]) * lz[n];

        if (s != e) {
            lz[n * 2] += lz[n];
            lz[n * 2 + 1] += lz[n];
        }

        lz[n] = 0;
    }

    void update(int s, int e, int n, const int l, const int r) {
        propagate(s, e, n);

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lz[n]++;
            propagate(s, e, n);
            return;
        }

        update(s, (s + e) / 2, n * 2, l, r);
        update((s + e) / 2 + 1, e, n * 2 + 1, l, r);

        vl[n] = vl[n * 2] + vl[n * 2 + 1];
    }

    void update(const int l, const int r) { update(1, sz, 1, l, r); }

    i64 query(int s, int e, int n, const int l, const int r) {
        propagate(s, e, n);

        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[n];
        return query(s, (s + e) / 2, n * 2, l, r) +
               query((s + e) / 2 + 1, e, n * 2 + 1, l, r);
    }

    i64 query(const int l, const int r) { return query(1, sz, 1, l, r); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i64 N, M, Q;
    cin >> N >> M >> Q;

    vector<tli> upds;
    for (int i = 0; i < M; i++) {
        i64 l, r, v;
        cin >> l >> r >> v;
        upds.emplace_back(v, l, r + 1);
        pzip.emplace_back(l);
        pzip.emplace_back(r + 1);
    }
    sort(iterall(upds));

    vector<i64> zip;
    for (auto [v, l, r] : upds) zip.emplace_back(v);
    zip.erase(unique(iterall(zip)), zip.end());

    for (auto& [v, l, r] : upds) v = lower_bound(iterall(zip), v) - zip.begin();

    vector<tli> queries;
    for (int i = 0; i < Q; i++) {
        i64 l, r, j;
        cin >> l >> r >> j;

        queries.emplace_back(l, r + 1, j);
        pzip.emplace_back(l);
        pzip.emplace_back(r + 1);
    }

    sort(iterall(pzip));
    pzip.erase(unique(iterall(pzip)), pzip.end());

    for (auto& [v, l, r] : upds) {
        l = lower_bound(iterall(pzip), l) - pzip.begin() + 1;
        r = lower_bound(iterall(pzip), r) - pzip.begin();
    }

    for (auto& [l, r, j] : queries) {
        l = lower_bound(iterall(pzip), l) - pzip.begin() + 1;
        r = lower_bound(iterall(pzip), r) - pzip.begin();
    }

    const auto nu = zip.size();
    vector<int> lo(Q), hi(Q, nu - 1);

    while (true) {
        bool flag = true;
        vector<vector<int>> proc(nu);
        for (int i = 0; i < Q; i++) {
            if (lo[i] < hi[i]) {
                flag = false;
                proc[(lo[i] + hi[i]) / 2].emplace_back(i);
            }
        }

        if (flag) break;

        int p = 0;
        auto sT = segTree(pzip.size() - 1);

        for (int n = 0; n < nu; n++) {
            while (p < M && n == get<0>(upds[p])) {
                sT.update(get<1>(upds[p]), get<2>(upds[p]));
                ++p;
            }

            for (auto i : proc[n]) {
                auto [l, r, j] = queries[i];
                if (sT.query(l, r) < j)
                    lo[i] = n + 1;
                else
                    hi[i] = n;
            }
        }
    }

    for (int i = 0; i < Q; i++) cout << zip[lo[i]] << '\n';

    return 0;
}