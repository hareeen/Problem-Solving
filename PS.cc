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

const int inf = numeric_limits<int>::max() / 3;

void relax(int sv, int sw, vector<int> &dist, const vector<vector<bool>> &adj) {
    const int N = dist.size();

    dist[sv] = sw;
    queue<pi> que;
    que.push({sw, sv});

    while (!que.empty()) {
        auto [w, u] = que.front();
        que.pop();

        if (w > dist[u]) continue;

        for (int v = 0; v < N; v++) {
            if (adj[u][v]) {
                if (w + 1 < dist[v]) {
                    dist[v] = w + 1;
                    que.push({w + 1, v});
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<vector<bool>> adj(N, vector<bool>(N));
    vector<pi> edg(M);

    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u][v] = true;
        edg[i] = {u, v};
    }

    vector<pi> queries(Q);
    for (int i = 0; i < Q; i++) {
        char c;
        int t, p;
        cin >> c >> p;
        --p;

        if (c == 'U')
            t = 0;
        else
            t = 1;

        queries[i] = {t, p};
        if (t == 0) {
            auto [u, v] = edg[p];
            adj[u][v] = false;
        }
    }

    vector<int> dist(N, inf);
    relax(0, 0, dist, adj);

    reverse(iterall(queries));

    vector<int> ret;
    for (auto [t, p] : queries) {
        if (t == 0) {
            auto [u, v] = edg[p];
            adj[u][v] = true;

            if (dist[v] - dist[u] > 1) relax(v, dist[u] + 1, dist, adj);
        } else {
            ret.push_back(dist[p]);
            if (ret.back() >= inf) ret.back() = -1;
        }
    }

    reverse(iterall(ret));
    copy(iterall(ret), ostream_iterator<int>(cout, "\n"));

    return 0;
}