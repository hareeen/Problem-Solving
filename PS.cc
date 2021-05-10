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

    int N;
    cin >> N;

    vector<i64> x(N + 1), y(N + 1);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i];
    x[N] = x[0], y[N] = y[0];

    i64 ans = 0;
    for (int i = 0; i < N; i++) ans += (x[i] * y[i + 1]);
    for (int i = 0; i < N; i++) ans -= (y[i] * x[i + 1]);
    ans = abs(ans);

    if (ans % 2 == 0)
        cout << ans / 2 << ".0" << endl;
    else
        cout << ans / 2 << ".5" << endl;

    return 0;
}
