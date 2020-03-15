#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

class Line {
   public:
    i64 a, b;

    Line() { a = 0, b = inf; }
    Line(i64 _a, i64 _b) { a = _a, b = _b; }

    inline i64 get(i64 x) { return a * x + b; }
};

class Node {
   public:
    i64 s, e;
    Line v;
    Node *l, *r;

    Node() {
        s = e = 0;
        v = Line();
        l = r = nullptr;
    }

    Node(i64 _s, i64 _e) {
        s = _s, e = _e, v = Line();
        l = r = nullptr;
    }
};

namespace LiChao {
stack<pair<Node*, Line>> trace;

Node* init(i64 s, i64 e) { return new Node(s, e); }

int update(Node* h, const Line v) {
    auto s = h->s, e = h->e;
    auto m = (s + e) / 2;

    trace.push({h, h->v});

    auto lo = h->v, hi = v;
    if (lo.get(s) > hi.get(s)) swap(lo, hi);

    if (lo.get(e) <= hi.get(e)) {
        h->v = lo;
        return 1;
    }

    if (lo.get(m) < hi.get(m)) {
        h->v = lo;
        if (!h->r) h->r = new Node(m + 1, e);
        return update(h->r, hi) + 1;
    } else {
        h->v = hi;
        if (!h->l) h->l = new Node(s, m);
        return update(h->l, lo) + 1;
    }
}

i64 query(Node* h, const i64 x) {
    if (!h) return inf;

    auto s = h->s, e = h->e;
    auto m = (s + e) / 2;

    return min(h->v.get(x), x <= m ? query(h->l, x) : query(h->r, x));
}

void revert(int rv) {
    for (int i = 0; i < rv; i++) {
        auto& [nd, vl] = trace.top();
        trace.pop();

        nd->v = vl;
    }
}

};  // namespace LiChao

namespace Tree {
vector<vector<pli>> adj;
vector<vector<int>> tr;
vector<i64> dep, dp, vel, cost;
Node* root;
int N;

void init(int _N) {
    N = _N;
    adj.resize(N + 1);
    tr.resize(N + 1);
    dep.resize(N + 1);
    dp.resize(N + 1);
    vel.resize(N + 1);
    cost.resize(N + 1);
    root = LiChao::init(0, 1e9);
}

void emplace_edge(int u, int v, i64 w) {
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
}

void rearrange(int h, int p) {
    for (auto [t, w] : adj[h]) {
        if (t == p) continue;
        tr[h].emplace_back(t);
        dep[t] = dep[h] + w;
        rearrange(t, h);
    }
}

void solve(int h) {
    dp[h] = LiChao::query(root, vel[h]) + dep[h] * vel[h] + cost[h];
    if (h == 1) dp[h] = 0;
    auto rev = LiChao::update(root, Line(-dep[h], dp[h]));
    for (auto t : tr[h]) solve(t);
    LiChao::revert(rev);
}
}  // namespace Tree

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    Tree::init(N);
    for (int i = 0; i < N - 1; i++) {
        i64 u, v, w;
        cin >> u >> v >> w;
        Tree::emplace_edge(u, v, w);
    }
    Tree::rearrange(1, -1);

    for (int i = 2; i <= N; i++) cin >> Tree::cost[i] >> Tree::vel[i];
    Tree::solve(1);

    copy(Tree::dp.begin() + 2, Tree::dp.end(),
         ostream_iterator<i64>(cout, " "));
    cout << endl;

    return 0;
}