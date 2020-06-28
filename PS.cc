#include "bits/stdc++.h"

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

class Edge {
public:
    int v, cap, fl;
    int rev;

    Edge() {
        v = cap = fl = 0;
        rev = 0;
    }

    Edge(int _v, int _cap, int _fl, int _rev) {
        v = _v, cap = _cap, fl = _fl, rev = _rev;
    }
};

void addEdge(int u, int v, int cap, vector<vector<Edge>> &graph) {
    graph[u].emplace_back(Edge(v, cap, 0, graph[v].size()));
    graph[v].emplace_back(Edge(u, 0, 0, graph[u].size() - 1));
}

int Source, Sink;

bool bfs(vector<int> &level, const vector<vector<Edge>> &graph) {
    fill(iterall(level), -1);

    queue<int> que;
    level[Source] = 0;
    que.push(Source);

    while (!que.empty()) {
        auto here = que.front();
        que.pop();
        for (auto el:graph[here]) {
            auto there = el.v, cap = el.cap, fl = el.fl;
            if (level[there] == -1 && cap - fl > 0) {
                level[there] = level[here] + 1;
                que.push(there);
            }
        }
    }

    return level[Sink] != -1;
}

int dfs(int here, int flow, vector<int> &work, const vector<int> &level, vector<vector<Edge>> &graph) {
    if (here == Sink) return flow;
    for (int &i = work[here]; i < graph[here].size(); i++) {
        auto there = graph[here][i].v, cap = graph[here][i].cap, fl = graph[here][i].fl;
        if (level[here] + 1 == level[there] && cap - fl > 0) {
            int bFlow = dfs(there, min(flow, cap - fl), work, level, graph);
            if (bFlow > 0) {
                graph[here][i].fl += bFlow;
                graph[graph[here][i].v][graph[here][i].rev].fl -= bFlow;
                return bFlow;
            }
        }
    }
    return 0;
}

int Dinic(vector<vector<Edge>> &graph) {
    int ret = 0;
    const int V = graph.size();
    vector<int> level(V), work(V);

    while (bfs(level, graph)) {
        fill(iterall(work), 0);
        while (true) {
            int flow = dfs(Source, numeric_limits<int>::max(), work, level, graph);
            if (!flow) break;
            ret += flow;
        }
    }

    return ret;
}

pi readI() {
    double d;
    cin >> d;
    return {(int) floor(d), (int) ceil(d)};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N + M + 4);
    vector<vector<int>> table(N, vector<int>(M));
    vector<int> xs(N), ys(M);

    const int E1 = N + M;
    const int E2 = N + M + 1;
    const int K1 = N + M + 2;
    const int K2 = N + M + 3;
    addEdge(K1, E1, numeric_limits<int>::max() / 2, graph);

    for (int i = 0; i < N; i++) {
        int su = 0;
        for (int j = 0; j < M; j++) {
            auto[f, c] = readI();
            addEdge(i, N + j, c - f, graph);
            addEdge(E2, N + j, f, graph);
            addEdge(i, K2, f, graph);
            table[i][j] = f;
        }
        auto[f, c] = readI();
        addEdge(E1, i, c - f, graph);
        addEdge(E2, i, f, graph);
        addEdge(E1, K2, f, graph);
    }
    for (int i = 0; i < M; i++) {
        auto[f, c] = readI();
        addEdge(N + i, K1, c - f, graph);
        addEdge(E2, K1, f, graph);
        addEdge(N + i, K2, f, graph);
    }

    Source = E2, Sink = K2;
    Dinic(graph);

    Source = E1, Sink = K1;
    Dinic(graph);

    for (int i = 0; i < N; i++) {
        for (auto el: graph[i]) {
            if (el.v >= N && el.v < N + M) table[i][el.v - N] += el.fl;
        }
    }

    for (int i = 0; i < N; i++) {
        int su = 0;
        for (int j = 0; j < M; j++) {
            cout << table[i][j] << " ";
            su += table[i][j];
            ys[j] += table[i][j];
        }
        cout << su << " ";
        cout << '\n';
    }
    copy(iterall(ys), ostream_iterator<int>(cout, " "));
    cout << '\n';

    return 0;
}