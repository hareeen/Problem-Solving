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

i64 solve(i64 f, i64 s, i64 n, const i64 t) {
    // cout << f << " " << s << " " << n << " " << t << endl;
    if (t == n) return f;
    if (t == n + 1) return s;
    if (f < 0 || s < 0) return solve(s, f > s ? f - s : s - f, n + 1, t);
    if (f < s) return solve(s, s - f, n + 1, t);
    if (f >= 2 * s) {
        i64 p;

        if (s != 0)
            p = f / (2 * s);
        else
            p = t / 3 + 1;

        if (t <= n + 3 * p) {
            if ((t - n) % 3 == 1)
                return s;
            else if ((t - n) % 3 == 2)
                return f - ((t - n - 1) / 3) * 2 * s - s;
            else
                return f - ((t - n - 1) / 3) * 2 * s - 2 * s;
        }

        return solve(f % (2 * s), s, n + 3 * p, t);
    }

    return solve(s, f - s, n + 1, t);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i64 f, s;
    cin >> f >> s;

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        i64 t;
        cin >> t;
        cout << solve(f, s, 0, t) << '\n';
    }

    return 0;
}