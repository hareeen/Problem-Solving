#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")

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

i64 v[1000001], w[1000001];

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a % b) : a; }
void process() {
    i64 p, q, n;
    cin >> p >> q >> n;

    p %= q;

    i64 g = gcd(p, q);
    p /= g, q /= g;

    i64 ret = 0;
    ret += (q * (q - 1) / 2 * (n / q));
    n %= q;

    i64 sq = sqrt(n);

    for (i64 i = 0; i < sq; i++) v[i] = (p * i * sq % q);
    sort(v, v + sq);

    auto acc = accumulate(v, v + sq, 0LL);

    for (i64 i = 0; i < sq; i++)
        w[i] = i ? w[i - 1] + p : 0, w[i] = w[i] > q ? w[i] - q : w[i];
    sort(w, w + sq);

    i64 id = sq - 1;
    for (i64 i = 0; i < sq; i++) {
        while (id >= 0 && v[id] >= q - w[i]) --id;
        ret -= ((sq - 1 - id) * q);
        ret -= (p * i / q * q * sq);
    }

    ret += (acc * sq);
    ret += (p * sq * (sq - 1) / 2 * sq);

    for (i64 i = sq * sq; i <= n; i++) ret += (p * i % q);

    cout << ret * g << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int W;
    cin >> W;

    for (int i = 0; i < W; i++) process();

    return 0;
}