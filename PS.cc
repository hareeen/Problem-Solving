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
    int N;
    vector<int> par;
public:
    explicit disjointSet(int _N) {
        N = _N;
        par.resize(N + 1);
        for (int i = 0; i <= N; i++) par[i] = i;
    }

    int find(int x) {
        return par[x] = (par[x] == x ? x : find(par[x]));
    }

    void merge(int x, int y) {
        par[find(x)] = find(y);
    }

    bool sset(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const i64 MOD = 1e9 + 7;

    int N, M;
    cin >> N >> M;

    vector<i64> exp3(M, 1);
    for (int i = 1; i < M; i++) exp3[i] = exp3[i - 1] * 3, exp3[i] %= MOD;

    vector<pi> queries;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        queries.emplace_back(u, v);
    }

    i64 ans = 0;
    auto dS = disjointSet(N);
    for (int i = M - 1; i >= 0; i--) {
        auto[u, v] = queries[i];
        if (dS.sset(u, 0) && dS.sset(v, N - 1)) ans += exp3[i];
        else if (dS.sset(v, 0) && dS.sset(u, N - 1)) ans += exp3[i];
        else dS.merge(u, v);

        ans %= MOD;
    }

    cout << ans << endl;
    return 0;
}