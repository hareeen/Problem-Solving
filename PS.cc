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

void sl(int x, vector<int> &dt, vector<pi> &trace) {
    dt[x] = dt[x + 1] = (6 - dt[x] - dt[x + 1]) % 3;
    trace.emplace_back(x, x + 1);
}

vector<pi> solve1D(vector<int> &dt) {
    vector<pi> ret;
    int p = 0;
    int N = dt.size();

    if (N == 1) return ret;

    while (p < N - 3) {
        if (dt[p] == dt[p + 1]) {
            ++p;
            continue;
        }

        if (dt[p + 1] != dt[p + 2]) {
            sl(p + 1, dt, ret);
        } else {
            sl(p, dt, ret);
            sl(p + 1, dt, ret);
            sl(p, dt, ret);
            sl(p + 1, dt, ret);
            sl(p, dt, ret);
            ++p;
        }
    }

    if (dt[N - 1] != dt[N - 2]) sl(N - 2, dt, ret);

    if (N % 3 == 0)
        return ret;
    else if (N % 3 == 1) {
        if (dt[N - 3] != dt[N - 2]) {
            sl(N - 3, dt, ret);
            sl(N - 2, dt, ret);
            sl(N - 3, dt, ret);
            sl(N - 2, dt, ret);
            sl(N - 3, dt, ret);
        }
    }

    p = N - 1;
    while (p > 1) {
        if (dt[p] == dt[p - 1]) {
            --p;
            continue;
        }

        if (dt[p - 1] != dt[p - 2]) {
            sl(p - 2, dt, ret);
        } else {
            sl(p - 1, dt, ret);
            sl(p - 2, dt, ret);
            sl(p - 1, dt, ret);
            sl(p - 2, dt, ret);
            sl(p - 1, dt, ret);
            --p;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> mp(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < M; j++) {
            if (s[j] == 'R') mp[i][j] = 0;
            if (s[j] == 'B') mp[i][j] = 1;
            if (s[j] == 'Y') mp[i][j] = 2;
        }
    }

    {
        int _su = 0;
        for (auto &v : mp)
            for (auto el : v) _su += el;
        if (_su % 3 != 0 && (N % 3 == 0 || M % 3 == 0)) {
            cout << -1 << endl;
            return 0;
        }
    }

    vector<pi> ord;
    vector<int> dt;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < M; j++) {
                ord.emplace_back(i + 1, j + 1);
                dt.emplace_back(mp[i][j]);
            }
        } else {
            for (int j = M - 1; j >= 0; j--) {
                ord.emplace_back(i + 1, j + 1);
                dt.emplace_back(mp[i][j]);
            }
        }
    }

    auto ret = solve1D(dt);
    cout << ret.size() << endl;
    for (auto [p1, p2] : ret)
        cout << ord[p1].first << " " << ord[p1].second << " " << ord[p2].first
             << " " << ord[p2].second << '\n';

    return 0;
}