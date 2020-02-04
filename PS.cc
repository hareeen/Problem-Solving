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

class disjointSet {
   private:
    vector<int> uf, rk;
    stack<pi> trace;
    stack<bool> isUpdated;

   public:
    disjointSet(int N) {
        uf.resize(N + 1);
        for (int i = 1; i <= N; i++) uf[i] = i;

        rk.resize(N + 1);
    }

    int find(int v) {
        while (uf[v] != v) v = uf[v];
        return v;
    }

    bool sset(int u, int v) { return find(u) == find(v); }

    int merge(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return 0;

        if (rk[u] > rk[v]) swap(u, v);
        trace.push({u, uf[u]});
        isUpdated.push(rk[u] == rk[v]);

        uf[u] = v;
        if (rk[u] == rk[v]) ++rk[v];

        return 1;
    }

    void revert(int t) {
        for (int i = 0; i < t; i++) {
            auto [v, p] = trace.top();
            auto u = isUpdated.top();

            trace.pop();
            isUpdated.pop();

            if (u) --rk[uf[v]];
            uf[v] = p;
        }
    }
};

vector<vector<ti>> edg(262144 + 1);
void spread(int s, int e, int n, const int l, const int r, const ti t) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        edg[n].emplace_back(t);
        return;
    }

    spread(s, (s + e) / 2, n * 2, l, r, t);
    spread((s + e) / 2 + 1, e, n * 2 + 1, l, r, t);
}

using qi = tuple<int, int, int, int>;

vector<qi> queries(1, {13, 13, 13, 13});
void solve(int s, int e, int n, vector<disjointSet>& dS) {
    vector<int> rv(10);
    for (auto [u, v, w] : edg[n])
        for (int i = w; i < 10; i++) rv[i] += dS[i].merge(u, v);

    if (s == e) {
        auto& [t, u, v, w] = queries[s];
        if (t == 13) {
            for (int i = 9; i >= 0; i--) {
                if (dS[i].sset(u, v)) t = i;
            }
            if (t == 13) t = -1;
        }
    } else {
        solve(s, (s + e) / 2, n * 2, dS);
        solve((s + e) / 2 + 1, e, n * 2 + 1, dS);
    }

    for (int i = 0; i < 10; i++) dS[i].revert(rv[i]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < Q; i++) {
        int t, u, v, w = 0;
        cin >> t;
        if (t == 0)
            cin >> u >> v >> w;
        else
            cin >> u >> v;

        ++u, ++v;
        t += 11;

        queries.emplace_back(t, u, v, w);
    }

    map<pi, pi> mp;
    for (int i = 1; i <= Q; i++) {
        auto [t, u, v, w] = queries[i];

        if (u > v) swap(u, v);

        if (t == 11) {
            mp.insert({pi(u, v), pi(i, w)});
        } else if (t == 12) {
            auto it = mp.find({u, v});
            spread(1, Q, 1, it->second.first, i,
                   {it->first.first, it->first.second, it->second.second});
            mp.erase(it);
        }
    }

    for (auto [ed, st] : mp)
        spread(1, Q, 1, st.first, Q, {ed.first, ed.second, st.second});

    auto dS = vector<disjointSet>(10, disjointSet(N));
    solve(1, Q, 1, dS);

    for (auto [t, u, v, w] : queries) {
        if (t <= 10) cout << t << '\n';
    }

    return 0;
}