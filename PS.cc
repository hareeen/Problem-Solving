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

class DisjointSet {
   public:
    vector<int> p;
    int N{};

    explicit DisjointSet(int _N) {
        N = _N;
        p.resize(N);
        iota(iterall(p), 0);
    }

    int fd(int u) { return p[u] = p[u] == u ? u : fd(p[u]); }
    void mer(int u, int v) { p[fd(u)] = fd(v); }
    bool sset(int u, int v) { return fd(u) == fd(v); }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pi> rect(N);
    vector<int> zipped;
    for (auto &[f, s] : rect) {
        cin >> f >> s;
        zipped.emplace_back(f);
        zipped.emplace_back(s);
    }

    sort(iterall(zipped));
    zipped.erase(unique(iterall(zipped)), zipped.end());

    const int Z = zipped.size();
    auto DS = DisjointSet(Z);
    for (const auto &[f, s] : rect) {
        auto fi = lower_bound(iterall(zipped), f) - zipped.begin();
        auto si = lower_bound(iterall(zipped), s) - zipped.begin();

        DS.mer(fi, si);
    }

    i64 ans = 0;
    vector<vector<i64>> gps(Z);
    for (int i = 0; i < Z; i++) gps[DS.fd(i)].emplace_back(zipped[i]);

    vector<int> eds(Z);
    for (const auto &[f, s] : rect) {
        auto fi = DS.fd(lower_bound(iterall(zipped), f) - zipped.begin());
        auto si = DS.fd(lower_bound(iterall(zipped), s) - zipped.begin());
        assert(fi == si);

        eds[fi]++;
        ans += f, ans += s;
    }

    for (int i = 0; i < Z; i++) {
        const auto &vec = gps[i];
        if (vec.empty()) continue;

        ans -= accumulate(iterall(vec), 0LL);
        if (eds[i] != vec.size()) ans += *max_element(iterall(vec));
    }

    cout << ans << endl;

    return 0;
}
