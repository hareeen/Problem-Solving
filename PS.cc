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

const i64 inf = numeric_limits<i64>::max() / 3;

vector<i64> dijkstra(int sv, const vector<vector<pli>> &adj) {
    vector<i64> dist(adj.size(), inf);
    priority_queue<pli, vector<pli>, greater<>> pq;
    dist[sv] = 0;
    pq.emplace(0, sv);

    while (!pq.empty()) {
        auto [W, u] = pq.top();
        pq.pop();

        if (W > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > W + w) {
                pq.emplace(W + w, v);
                dist[v] = W + w;
            }
        }
    }

    return dist;
}

pair<vector<i64>, vector<i64>> adv_dijkstra(int sv,
                                            const vector<vector<pli>> &adj,
                                            const vector<i64> &td) {
    vector<i64> dist(adj.size() + 1, inf), tm(adj.size() + 1, inf);
    priority_queue<tli, vector<tli>, greater<>> pq;
    dist[sv] = 0, tm[sv] = td[sv];
    pq.emplace(0, td[sv], sv);

    while (!pq.empty()) {
        auto [W, M, u] = pq.top();
        pq.pop();

        if (W > dist[u] || M > tm[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > W + w ||
                (dist[v] == W + w && tm[v] > min(M, td[v]))) {
                pq.emplace(W + w, min(M, td[v]), v);
                dist[v] = W + w;
                tm[v] = min(M, td[v]);
            }
        }
    }

    return {dist, tm};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, S, T, U, V;
    cin >> N >> M >> S >> T >> U >> V;

    vector<vector<pli>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        i64 u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    auto ud = dijkstra(U, adj);
    auto vd = dijkstra(V, adj);
    auto [sd, svm] = adv_dijkstra(S, adj, vd);
    auto [td, tvm] = adv_dijkstra(T, adj, vd);

    auto minDis = sd[T];
    auto ans = ud[V];

    for (int i = 1; i <= N; i++) {
        if (minDis != sd[i] + td[i]) continue;
        ans = min(ans, ud[i] + min(svm[i], tvm[i]));
    }

    cout << ans << endl;
    return 0;
}