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

class BIT {
   public:
    vector<i64> v;
    size_t sz;

    BIT() {
        v.resize((1 << 18) + 1);
        sz = v.size();
    }

    void update(int i, i64 d) {
        while (i < sz) v[i] += d, i += (i & -i);
    }

    i64 query(int i) {
        i64 ret = 0;
        while (i) ret += v[i], i -= (i & -i);
        return ret;
    }

    i64 query(int l, int r) { return query(r) - (l ? query(l - 1) : 0); }
};

void dfs(int h, int p, int &ord, vector<int> &in, vector<int> &out,
         const vector<vector<int>> &adj) {
    in[h] = ord;

    for (auto t : adj[h]) {
        if (t == p) continue;

        ++ord;
        dfs(t, h, ord, in, out, adj);
    }

    out[h] = ord;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    i64 J;

    cin >> N >> K >> J;

    vector<vector<int>> adj(N + 1);
    for (int u = 2; u <= N; u++) {
        int v;
        cin >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    int ord = 1;
    vector<int> in(N + 1), out(N + 1);
    dfs(1, -1, ord, in, out, adj);

    vector<i64> goal(N + 1);
    vector<vector<int>> teams(N + 1);
    vector<int> cont(N + 1);
    for (int i = 1; i <= N; i++) {
        int t;
        cin >> t;

        teams[t].emplace_back(i);
        cont[i] = t;
        goal[t] += J;
    }

    for (auto t = 0; t <= N; t++)
        if (!goal[t]) goal[t] = numeric_limits<i64>::max();

    vector<tli> queries;
    for (int i = 0; i < K; i++) {
        i64 a, b, c;
        cin >> a >> b >> c;
        queries.emplace_back(a, b, c);
    }

    sort(iterall(queries));

    vector<i64> times;
    for (auto [t, _, __] : queries) times.emplace_back(t);

    times.erase(unique(iterall(times)), times.end());

    for (auto &[t, _, __] : queries)
        t = lower_bound(iterall(times), t) - times.begin();

    auto Q = times.size();

    vector<int> lo(N + 1, 0), hi(N + 1, Q);
    while (true) {
        bool flag = true;
        vector<vector<int>> q(Q);

        for (int i = 1; i <= N; i++) {
            if (lo[i] < hi[i]) {
                flag = false;
                q[(lo[i] + hi[i]) / 2].emplace_back(i);
            }
        }

        if (flag) break;

        int p = 0;
        auto biT = BIT();
        for (int i = 0; i < Q; i++) {
            while (p < K && get<0>(queries[p]) == i) {
                auto [t, n, d] = queries[p];
                d /= (out[n] - in[n] + 1);
                biT.update(in[n], d);
                biT.update(out[n] + 1, -d);
                ++p;
            }

            for (auto t : q[i]) {
                i64 su = 0;
                for (auto el : teams[t]) su += biT.query(in[el]);
                if (su <= goal[t])
                    lo[t] = i + 1;
                else
                    hi[t] = i;
            }
        }
    }

    for (int i = 1; i <= N; i++)
        cout << (lo[cont[i]] == Q ? -1 : times[lo[cont[i]]]) << '\n';

    return 0;
}