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

i64 p1 = 13, p2 = 7, md = 1e12 - 11;

i64 hs(int here, int pr, const vector<vector<int>> &graph) {
    if (pr != -1 && graph[here].size() == 1) {
        return p1;
    }

    __int128 x = 1;
    for (auto el : graph[here]) {
        if (el == pr) continue;
        x *= (hs(el, here, graph) + 1);
        x *= p2;
        x %= md;
    }

    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int G;
    cin >> G;

    int ans = 0;
    unordered_set<i64> S;
    for (int g = 0; g < G; g++) {
        int N;
        cin >> N;

        vector<vector<int>> graph(N);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        size_t mxsize = 0;
        for (int i = 0; i < N; i++) mxsize = max(mxsize, graph[i].size());

        vector<i64> v;
        for (int i = 0; i < N; i++)
            if (graph[i].size() == mxsize) v.push_back(hs(i, -1, graph));

        for (auto el : v) {
            if (S.find(el) != S.end()) goto next;
        }

        ans++;
        for (auto el : v) S.insert(el);

    next:;
    }

    cout << ans << endl;
    return 0;
}