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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> M >> N;

    vector<ti> arr(N);
    for (int i = 0; i < N; i++) cin >> get<0>(arr[i]);
    for (int i = 0; i < N; i++) cin >> get<1>(arr[i]);
    if (M == 3) for (int i = 0; i < N; i++) cin >> get<2>(arr[i]);
    sort(iterall(arr));
    if (M == 2) for (int i = 0; i < N; i++) get<2>(arr[i]) = i;

    vector<set<pi>> vs(N + 1);
    vs[0].emplace(0, 0);

    for (auto[_, u, v]:arr) {
        int s = 0, e = N;
        while (s < e) {
            auto m = (s + e + 1) / 2;
            if (vs[m].empty()) {
                e = m - 1;
                continue;
            }

            auto it = vs[m].lower_bound({u, v});
            if (it != vs[m].begin() and prev(it)->second < v) s = m;
            else e = m - 1;
        }

        auto &aps = vs[s + 1];
        while (true) {
            auto it = aps.lower_bound({u, v});
            if (it == aps.end() || it->second < v) break;
            else aps.erase(it);
        }

        aps.emplace(u, v);
    }

    for (int i = N; i >= 0; i--) {
        if (!vs[i].empty()) {
            cout << i << endl;
            break;
        }
    }

    return 0;
}