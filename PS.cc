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

constexpr int pinf = numeric_limits<int>::max() / 2;
constexpr int ninf = numeric_limits<int>::min() / 2;

vector<int> dijkstra(const vector<vector<pi>>& G, const vector<int>& ini) {
    const int V = G.size();
    vector<int> dist(V, pinf);

    priority_queue<pi, vector<pi>, greater<pi>> pq;
    for (auto el : ini) {
        pq.emplace(0, el);
        dist[el] = 0;
    }

    while (!pq.empty()) {
        auto [W, h] = pq.top();
        pq.pop();

        if (dist[h] < W) continue;

        for (auto [t, w] : G[h]) {
            if (dist[t] > W + w) {
                dist[t] = W + w;
                pq.emplace(W + w, t);
            }
        }
    }

    return dist;
}

class DisjointSet {
   public:
    int N;
    vector<int> p;

    explicit DisjointSet(int _N) {
        N = _N;
        p.reserve(N);
        for (int i = 0; i < N; i++) p.emplace_back(i);
    }

    inline int find(int u) {
        return p[u] = (p[u] == u ? u : find(p[u]));
    }

    inline void mer(int u, int v) {
        p[find(u)] = find(v);
    }

    inline bool sset(int u, int v) {
        return find(u) == find(v);
    }

    inline void clear() {
        for (int i = 0; i < N; i++) p[i] = i;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K, Q;
    cin >> N >> M >> K >> Q;

    vector<pi> E(M);
    vector<vector<pi>> G(N);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;

        E[i] = {u, v};
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    vector<int> festival(K);
    for (auto& el : festival) {
        cin >> el;
        --el;
    }

    vector<pi> queries(Q);
    for (auto& [u, v] : queries) {
        cin >> u >> v;
        --u, --v;
    }

    vector<pi> D(N);
    vector<int> dist = dijkstra(G, festival);
    for (int i = 0; i < N; i++) D[i] = {dist[i], i};
    sort(iterall(D), greater<>());
    sort(iterall(E), [&dist](const pi& lhs, const pi& rhs) {
        return min(dist[lhs.first], dist[lhs.second]) > min(dist[rhs.first], dist[rhs.second]);
    });

    DisjointSet DS(M);

    vector<pi> validE;
    vector<int> requiredDist;
    validE.reserve(M);
    requiredDist.reserve(M);
    for (auto [u, v] : E) {
        if (DS.sset(u, v)) continue;
        DS.mer(u, v);
        validE.emplace_back(u, v);
        requiredDist.emplace_back(min(dist[u], dist[v]));
    }
    validE.shrink_to_fit();
    requiredDist.shrink_to_fit();
    const int VM = validE.size();
    DS.clear();

    vector<int> lo(Q), hi(Q, N - 1);
    {
        vector<vector<int>> qri(N);
        for (int i = 0; i < Q; i++) {
            auto [u, v] = queries[i];
            qri[u].emplace_back(i);
            qri[v].emplace_back(i);
        }

        for (int j = 0; j < N; j++) {
            for (auto i : qri[D[j].second]) {
                lo[i] = j;
            }
        }
    }

    vector<vector<int>> pbs(N);

    while (true) {
        bool termination = true;
        int cur = 0;

        for (int i = 0; i < Q; i++) {
            if (lo[i] != hi[i]) {
                termination = false;
                pbs[(lo[i] + hi[i]) >> 1].emplace_back(i);
            }
        }

        if (termination) break;

        for (int j = 0; j < N; j++) {
            while (cur < VM && requiredDist[cur] >= D[j].first) {
                auto [u, v] = validE[cur];
                DS.mer(u, v);
                ++cur;
            }

            for (auto i : pbs[j]) {
                auto [u, v] = queries[i];

                if (DS.sset(u, v))
                    hi[i] = j;
                else
                    lo[i] = j + 1;
            }
        }

        for (auto& vec : pbs) vec.clear();
        DS.clear();
    }

    for (int i = 0; i < Q; i++) {
        cout << D[lo[i]].first << '\n';
    }

    return 0;
}
