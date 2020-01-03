#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

inline i64 smod(i64 x, i64 m) {
    return (x % m + m) % m;
}

tli ext_euc(i64 a, i64 b) {
    if (b == 0) return {a, 1, 0};
    auto[g, x, y] = ext_euc(b, a % b);
    return {g, y, x - (a / b) * y};
}

const i64 MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i64 N, K;
    cin >> N >> K;

    vector<i64> fact(1, 1);
    for (int i = 1; i <= N; i++) fact.push_back(fact.back() * i), fact.back() %= MOD;

    i64 ans = fact.back();
    ans *= get<1>(ext_euc(fact[K], MOD));
    ans = smod(ans, MOD);
    ans *= get<1>(ext_euc(fact[N - K], MOD));
    ans = smod(ans, MOD);

    cout << ans << endl;

    return 0;
}