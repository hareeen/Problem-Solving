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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    i64 N;
    cin >> N;

    vector<i64> fibo(2, 1);
    int fn = 2;
    for (; fibo[fn - 1] < 1e15;)
        fibo.push_back(fibo[fn - 1] + fibo[fn - 2]), ++fn;

    auto n = N;
    auto it = prev(fibo.end());
    while (n > 0) {
        while (*it > n) --it;
        n -= *it;
    }

    cout << (*it == N ? -1 : *it) << endl;
    return 0;
}