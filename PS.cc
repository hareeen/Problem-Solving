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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, S;
    cin >> N >> S;

    vector<int> arr(N);
    for (auto &el : arr) cin >> el;

    int k = N / 2;
    vector<int> v;
    for (int i = 0; i < (1 << k); i++) {
        int s = 0;
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) s += arr[j];
        }
        v.emplace_back(s);
        // cout << s << endl;
    }
    sort(iterall(v));

    i64 ans = 0;
    for (int i = 0; i < (1 << (N - k)); i++) {
        int s = 0;
        for (int j = 0; j < N - k; j++) {
            if (i & (1 << j)) s += arr[N - 1 - j];
        }

        auto [itl, itu] = equal_range(iterall(v), S - s);
        ans += (itu - itl);
    }

    cout << ans - (S == 0) << endl;
    return 0;
}
