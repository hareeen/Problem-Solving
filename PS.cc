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

class CHT {
   public:
    vector<i64> a, b, c;
    int pv, top;

    CHT() {
        a.resize(100001);
        b.resize(100001);
        c.resize(100001);
    }

    void init() { pv = top = 0; }

    i64 get(i64 idx, i64 x) { return a[idx] * x + b[idx]; }

    void insert(i64 _a, i64 _b, i64 _c) {
        if (top >= 1 && _a == a[top - 1]) {
            c[top - 1] = _c;
            return;
        }

        while (top >= 2 && (b[top - 1] - b[top - 2]) * (a[top - 2] - _a) >=
                               (_b - b[top - 2]) * (a[top - 2] - a[top - 1]))
            top--;
        a[top] = _a, b[top] = _b, c[top] = _c;
        ++top;

        if (pv >= top) pv = top - 1;
    }

    pli query(i64 x) {
        while (pv + 1 < top && get(pv + 1, x) > get(pv, x)) ++pv;
        return {get(pv, x), c[pv]};
    }
};

i64 dp[100001];
int tr[201][100001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<i64> arr(N), s(N);
    cin >> arr[0];
    s[0] = arr[0];
    for (int i = 1; i < N; i++) cin >> arr[i], s[i] = arr[i] + s[i - 1];
    for (int i = 0; i < N; i++) dp[i] = s[i] * s[i];

    auto cht = CHT();

    for (int i = 0; i < K; i++) {
        cht.init();

        for (int j = 0; j < N; j++) {
            auto tmp = dp[j];
            auto q = j ? cht.query(s[j]) : pli(0, -1);
            q.first = -q.first;
            q.first += s[j] * s[j];
            tie(dp[j], tr[i][j]) = q;

            cht.insert(2 * s[j], -s[j] * s[j] - tmp, j);
        }
    }

    cout << (s[N - 1] * s[N - 1] - dp[N - 1]) / 2 << endl;

    auto t = tr[K - 1][N - 1];
    auto k = K - 1, d = 0;

    vector<bool> ret(N);

    while (t != -1) {
        ret[t] = true, ++d;
        if (k == 0) break;
        t = tr[--k][t];
    }

    auto p = 0;
    for (; d < K; d++) {
        while (ret[p]) ++p;
        ret[p] = true;
    }

    for (int i = 0; i < N; i++)
        if (ret[i]) cout << i + 1 << " ";
    cout << endl;

    return 0;
}