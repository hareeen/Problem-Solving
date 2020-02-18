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

using qli = tuple<i64, i64, i64, i64>;
#define pack(n) su[n], ls[n], rs[n], vl[n]

const i64 inf = numeric_limits<i64>::max() / 4;

class segTree {
   public:
    vector<i64> su;
    vector<i64> ls;
    vector<i64> rs;
    vector<i64> vl;
    const i64 ini = -100001;
    size_t SZ = 0;

    segTree() {
        const size_t s = (1 << 18) + 1;
        su.resize(s);
        ls.resize(s);
        rs.resize(s);
        vl.resize(s);
    }

    qli mer(qli l, qli r) {
        auto [lsu, lls, lrs, lvl] = l;
        auto [rsu, rls, rrs, rvl] = r;

        i64 tsu = lsu + rsu;
        i64 tls = max(lls, lsu + rls);
        i64 trs = max(rrs, rsu + lrs);
        i64 tvl = max({tls, trs, lrs + rls, lvl, rvl});

        return {tsu, tls, trs, tvl};
    }

    void init(int s, int e, int n) {
        if (n == 1) SZ = e;

        if (s == e) {
            vl[n] = ls[n] = rs[n] = 0;
            su[n] = ini;
            return;
        }

        init(s, (s + e) / 2, n * 2);
        init((s + e) / 2 + 1, e, n * 2 + 1);
        tie(pack(n)) = mer({pack(n * 2)}, {pack(n * 2 + 1)});
    }

    void update(int s, int e, int n, const int t, const i64 u = 1LL) {
        if (t < s || e < t) return;

        if (s == e) {
            vl[n] = ls[n] = rs[n] = max(u, 0LL);
            su[n] = u;
            return;
        }

        update(s, (s + e) / 2, n * 2, t, u);
        update((s + e) / 2 + 1, e, n * 2 + 1, t, u);
        tie(pack(n)) = mer({pack(n * 2)}, {pack(n * 2 + 1)});
    }

    void update(const int t) { update(1, SZ, 1, t); }

    qli query(int s, int e, int n, const int l, const int r) {
        if (r < s || e < l) return {0, -inf, -inf, -inf};
        if (l <= s && e <= r) return {pack(n)};
        return mer(query(s, (s + e) / 2, n * 2, l, r),
                   query((s + e) / 2 + 1, e, n * 2 + 1, l, r));
    }

    i64 query(const int l, const int r) {
        return get<3>(query(1, SZ, 1, l, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pli> hist(N);
    for (int i = 0; i < N; i++) {
        cin >> hist[i].first;
        hist[i].second = i + 1;
    }

    sort(iterall(hist), greater<>());

    vector<i64> comp(N);
    for (int i = 0; i < N; i++) comp[i] = hist[i].first;
    reverse(iterall(comp));
    comp.erase(unique(iterall(comp)), comp.end());

    for (auto& [h, _] : hist) h = lower_bound(iterall(comp), h) - comp.begin();

    int H = comp.size();

    int Q;
    cin >> Q;

    vector<tli> queries(Q);
    for (int i = 0; i < Q; i++) {
        i64 l, r, w;
        cin >> l >> r >> w;
        queries[i] = {l, r, w};
    }

    vector<int> lo(Q), hi(Q, H);
    while (true) {
        bool flag = true;
        vector<vector<int>> proc(H + 1);

        for (int i = 0; i < Q; i++) {
            if (lo[i] < hi[i]) {
                flag = false;
                proc[(lo[i] + hi[i] + 1) / 2].emplace_back(i);
            }
        }

        if (flag) break;

        auto sT = segTree();
        sT.init(1, N, 1);

        int p = 0;
        for (int h = H; h >= 0; --h) {
            for (; p < N && hist[p].first == h; ++p) {
                sT.update(hist[p].second);
            }
            for (auto i : proc[h]) {
                auto [l, r, w] = queries[i];
                if (sT.query(l, r) >= w)
                    lo[i] = h;
                else
                    hi[i] = h - 1;
            }
        }
    }

    for (int i = 0; i < Q; i++) cout << comp[lo[i]] << '\n';

    return 0;
}