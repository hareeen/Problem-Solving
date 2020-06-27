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

    random_device rd;
    mt19937 rnd(rd());

    int N, M;
    cin >> N >> M;

    vector<int> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];

    vector<vector<int>> idx(N + 1);
    for (int i = 0; i < N; i++) idx[v[i]].emplace_back(i);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        vector<int> s(25);
        uniform_int_distribution<int> dist(a, b);
        for (int j = 0; j < 25; j++) s[j] = v[dist(rnd)];
        sort(iterall(s));
        s.erase(unique(iterall(s)), s.end());

        for (auto el:s) {
            int hm = upper_bound(iterall(idx[el]), b) - lower_bound(iterall(idx[el]), a);
            if (hm * 2 > b - a + 1) {
                cout << el << '\n';
                goto next;
            }
        }

        cout << 0 << '\n';
        next:;
    }


    return 0;
}