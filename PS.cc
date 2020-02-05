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

class Line {
   public:
    i64 a, b;

    Line() { a = 0, b = -inf; }
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
        h->v = hi;
        return 1;
    }

    if (lo.get(m) < hi.get(m)) {
        h->v = hi;
        if (!h->r) h->r = new Node(m + 1, e);
        return update(h->r, lo) + 1;
    } else {
        h->v = lo;
        if (!h->l) h->l = new Node(s, m);
        return update(h->l, hi) + 1;
    }
}

i64 query(Node* h, const i64 x) {
    if (!h) return -inf;

    auto s = h->s, e = h->e;
    auto m = (s + e) / 2;

    return max(h->v.get(x), x <= m ? query(h->l, x) : query(h->r, x));
}

void revert(int rv) {
    for (int i = 0; i < rv; i++) {
        auto& [nd, vl] = trace.top();
        trace.pop();

        nd->v = vl;
    }
}

};  // namespace LiChao

vector<tli> queries(1);

vector<vector<Line>> edg(1048576 + 1);
void spread(int s, int e, int n, const int l, const int r, const Line li) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        edg[n].emplace_back(li);
        return;
    }

    spread(s, (s + e) / 2, n * 2, l, r, li);
    spread((s + e) / 2 + 1, e, n * 2 + 1, l, r, li);
}

vector<i64> ans;
void solve(int s, int e, int n, Node* rt) {
    int rv = 0;
    for (auto [a, b] : edg[n]) rv += LiChao::update(rt, Line(a, b));

    if (s == e) {
        auto [t, x, _] = queries[s];
        if (t == 3) ans.emplace_back(LiChao::query(rt, x));
    } else {
        solve(s, (s + e) / 2, n * 2, rt);
        solve((s + e) / 2 + 1, e, n * 2 + 1, rt);
    }

    LiChao::revert(rv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        i64 t;
        i64 a, b = 0;

        cin >> t;

        if (t == 1)
            cin >> a >> b;
        else
            cin >> a;

        queries.emplace_back(t, a, b);
    }

    set<int> st;
    for (int i = 1; i <= N; i++) {
        auto [t, idx, _] = queries[i];
        if (t == 1) st.insert(i);
        if (t == 2) {
            auto [__, a, b] = queries[idx];
            spread(1, N, 1, idx, i, Line(a, b));
            st.erase(idx);
        }
    }

    for (auto idx : st) {
        auto [_, a, b] = queries[idx];
        spread(1, N, 1, idx, N, Line(a, b));
    }

    auto rt = LiChao::init(-1e9, 1e9);
    solve(1, N, 1, rt);

    for (auto el : ans) {
        if (el == -inf)
            cout << "EMPTY\n";
        else
            cout << el << '\n';
    }

    return 0;
}