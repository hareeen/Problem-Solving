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

    vector<int> psum(N + 1);
    for (int i = 0; i < N; i++) psum[i + 1] = psum[i] + arr[i];

    if (psum.back() < S) {
        cout << 0 << endl;
        return 0;
    }

    int s = 1, e = N;
    while (s < e) {
        int m = (s + e) / 2;
        for (int i = 0; i <= N - m; i++) {
            if (psum[i + m] - psum[i] >= S) {
                e = m;
                goto nl;
            }
        }

        s = m + 1;
    nl:;
    }

    cout << s << endl;
    return 0;
}
