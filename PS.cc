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

class sqrtDecomp {
   public:
    int N, sq;
    // sd[i] : [sq*i, sq*(i+1))
    vector<int> vl, sd;

    sqrtDecomp(int _N) {
        N = _N;
        sq = sqrt(N);

        vl.resize(N + 1);
        sd.resize(N / sq + 1);
    }

    void update(int t, int d) {
        vl[t] += d;
        sd[t / sq] += d;
    }

    int query() {
        for (int i = N / sq; i >= 0; i--) {
            if (!sd[i]) continue;
            for (int j = min(i * sq + sq - 1, N); j >= i * sq; j--)
                if (vl[j]) return j;
        }

        return 0;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<list<int>> v(K);
    vector<int> arr(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        arr[i] += arr[i - 1];
        arr[i] %= K;
    }

    int Q;
    cin >> Q;

    vector<ti> queries;
    for (int i = 0; i < Q; i++) {
        int s, e;
        cin >> s >> e;
        queries.emplace_back(--s, e, i);
    }

    int sqN = sqrt(N);
    sort(iterall(queries), [sqN](const ti &l, const ti &r) {
        auto [s1, e1, i1] = l;
        auto [s2, e2, i2] = r;
        s1 /= sqN;
        s2 /= sqN;
        return s1 == s2 ? e1 < e2 : s1 < s2;
    });

    vector<int> ret(Q);
    ti lq = {-1, -1, -1};
    auto sD = sqrtDecomp(N);

    for (auto [s, e, id] : queries) {
        if (get<0>(lq) == -1) {
            for (int i = s; i <= e; i++) v[arr[i]].emplace_back(i);
            for (const auto &l : v) {
                if (l.empty()) continue;
                sD.update(l.back() - l.front(), 1);
            }
        } else {
            auto [ls, le, _] = lq;
            if (s < ls)
                for (int i = ls - 1; i >= s; i--) {
                    if (!v[arr[i]].empty())
                        sD.update(v[arr[i]].back() - v[arr[i]].front(), -1);
                    v[arr[i]].emplace_front(i);
                    sD.update(v[arr[i]].back() - v[arr[i]].front(), 1);
                }
            if (le < e)
                for (int i = le + 1; i <= e; i++) {
                    if (!v[arr[i]].empty())
                        sD.update(v[arr[i]].back() - v[arr[i]].front(), -1);
                    v[arr[i]].emplace_back(i);
                    sD.update(v[arr[i]].back() - v[arr[i]].front(), 1);
                }
            if (s > ls)
                for (int i = ls; i < s; i++) {
                    sD.update(v[arr[i]].back() - v[arr[i]].front(), -1);
                    v[arr[i]].pop_front();
                    if (!v[arr[i]].empty())
                        sD.update(v[arr[i]].back() - v[arr[i]].front(), 1);
                }
            if (le > e)
                for (int i = le; i > e; i--) {
                    sD.update(v[arr[i]].back() - v[arr[i]].front(), -1);
                    v[arr[i]].pop_back();
                    if (!v[arr[i]].empty())
                        sD.update(v[arr[i]].back() - v[arr[i]].front(), 1);
                }
        }

        lq = {s, e, id};
        ret[id] = sD.query();
    }

    copy(iterall(ret), ostream_iterator<decltype(ret)::value_type>(cout, "\n"));

    return 0;
}