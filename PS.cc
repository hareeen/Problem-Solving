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

const int pinf = numeric_limits<int>::max() / 2;

vector<int> dijkstra(int sv, const vector<vector<pi>> &graph) {
    const int N = graph.size();
    vector<int> dist(N, pinf);
    dist[sv] = 0;

    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.emplace(0, sv);

    while (!pq.empty()) {
        auto [W, h] = pq.top();
        pq.pop();

        if (dist[h] < W) continue;
        for (auto [t, w] : graph[h]) {
            if (dist[t] > W + w) {
                dist[t] = W + w;
                pq.emplace(W + w, t);
            }
        }
    }

    return dist;
}

bool process() {
    int N, M;
    cin >> N >> M;

    if (N + M == 0) return false;

    int S, D;
    cin >> S >> D;

    vector<vector<pi>> graph(N);
    vector<ti> edg;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        edg.emplace_back(u, v, w);
    }

    vector<vector<int>> dist(N);
    for (int i = 0; i < N; i++) dist[i] = dijkstra(i, graph);

    vector<vector<pi>> graph2(N);
    for (int i = 0; i < M; i++) {
        auto [u, v, w] = edg[i];
        if (dist[S][u] + w + dist[v][D] != dist[S][D]) graph2[u].emplace_back(v, w);
    }

    int res = dijkstra(S, graph2)[D];
    if (res >= pinf) res = -1;
    cout << res << endl;

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (process())
        ;

    return 0;
}
