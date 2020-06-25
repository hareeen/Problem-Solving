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

class disjointSet {
   private:
    vector<int> par;
    int N;

   public:
    explicit disjointSet(int _N) {
        N = _N;
        par.resize(N + 1);
        for (int i = 0; i <= N; i++) par[i] = i;
    }

    int find(int u) { return par[u] = (u == par[u] ? u : find(par[u])); }

    bool sset(int u, int v) { return find(u) == find(v); }

    void merge(int u, int v) { par[find(u)] = find(v); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    auto dS = disjointSet(N);
    vector<int> mask(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        dS.merge(u, v);
        mask[u] = 1 - mask[u];
        mask[v] = 1 - mask[v];
    }

    vector<vector<int>> grp(N);
    for (int i = 0; i < N; i++) grp[dS.find(i)].emplace_back(i);

    int ans = 0;
    for (const auto &vec : grp) {
        if(vec.size() < 2) continue;
        // copy(iterall(vec), ostream_iterator<int>(cout, " "));
        // cout<<endl;

        int s = 0;
        for (auto el : vec) s += mask[el];
        ans += max(1, s >> 1);
    }

    cout << ans << endl;
    return 0;
}