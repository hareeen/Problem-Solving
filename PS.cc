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

const i64 inf = numeric_limits<i64>::max() / 2;

vector<pair<int, i64>> graph[800000];

vector<i64> dijkstra(int st, int V) {
    vector<i64> dist(V, inf);
    dist[st] = 0;

    priority_queue<pair<i64, int>> pq;
    pq.emplace(0, st);

    while (!pq.empty()) {
        auto[d, h] = pq.top();
        pq.pop();

        if (dist[h] < d) continue;
        for (auto[t, w]:graph[h]) {
            if (dist[t] > d + w) {
                dist[t] = d + w;
                pq.emplace(d + w, t);
            }
        }
    }

    return dist;
}

class Node {
public:
    int idx;
    Node *l, *r;

    explicit Node(int _idx) {
        idx = _idx;
        l = r = nullptr;
    }

    Node(int _idx, Node *_l, Node *_r) {
        idx = _idx, l = _l, r = _r;
    }
};

namespace partitionHelper {
    int N, cur;
    Node *root = nullptr;

    void init(int _N) {
        N = _N;
        cur = 0;
    }

    Node *construct(int s, int e) {
        if (s == e) return new Node(cur++);

        auto i = cur;
        cur += 2;
        auto m = (s + e) >> 1;
        auto l = construct(s, m);
        auto r = construct(m + 1, e);
        return new Node(i, l, r);
    }

    Node *construct() {
        return construct(1, N);
    }

    void rangeCollect(int s, int e, Node *h, int l, int r, bool tp, vector<int> &target) {
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            if (s == e) target.emplace_back(h->idx);
            else target.emplace_back(h->idx + tp);
            return;
        }

        auto m = (s + e) >> 1;
        rangeCollect(s, m, h->l, l, r, tp, target);
        rangeCollect(m + 1, e, h->r, l, r, tp, target);
    }

    vector<int> rangeCollect(int l, int r, bool tp) {
        vector<int> ret;
        rangeCollect(1, N, root, l, r, tp, ret);
        return ret;
    }

    void defaultEdges(int s, int e, Node *h, Node *p, vector<pi> &target) {
        if (p) {
            auto hx = h->idx, px = p->idx;
            target.emplace_back(hx, px);
            if (s != e) target.emplace_back(px + 1, hx + 1);
            else target.emplace_back(px + 1, hx);
        }

        if (s == e) return;

        auto m = (s + e) >> 1;
        defaultEdges(s, m, h->l, h, target);
        defaultEdges(m + 1, e, h->r, h, target);
    }

    vector<pi> defaultEdges() {
        vector<pi> ret;
        defaultEdges(1, N, root, nullptr, ret);
        return ret;
    }

    void indexCollect(int s, int e, Node *h, vector<int> &target) {
        if (s == e) {
            target.emplace_back(h->idx);
            return;
        }

        auto m = (s + e) >> 1;
        indexCollect(s, m, h->l, target);
        indexCollect(m + 1, e, h->r, target);
    }

    vector<int> indexCollect() {
        vector<int> ret(1);
        indexCollect(1, N, root, ret);
        return ret;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    partitionHelper::init(N);
    partitionHelper::root = partitionHelper::construct();
    auto indexMap = partitionHelper::indexCollect();

    int V = partitionHelper::cur;

    for (int i = 0; i < M; i++) {
        i64 w;
        int a, b, c, d;
        cin >> w >> a >> b >> c >> d;

        auto stV = partitionHelper::rangeCollect(a, b, false);
        auto edV = partitionHelper::rangeCollect(c, d, true);

        for (auto sv: stV) {
            for (auto ev: edV) {
                if (sv != ev) graph[sv].emplace_back(ev, w);
            }
        }
    }

    auto dEdg = partitionHelper::defaultEdges();
    for (auto[u, v]:dEdg) graph[u].emplace_back(v, 0);

    auto dist = dijkstra(indexMap[K], V);
    for (int i = 1; i <= N; i++) {
        auto vl = dist[indexMap[i]];
        if (vl >= inf) vl = -1;

        cout << vl << " ";
    }
    cout << '\n';

    return 0;
}