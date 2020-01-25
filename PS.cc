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

    Line() { a = 1, b = -inf; }

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
        s = _s, e = _e;
        v = Line();
        l = r = nullptr;
    }
};

namespace LiChao {
Node* init(i64 s, i64 e) { return new Node(s, e); }

void update(Node* hr, const Line l) {
    i64 s = hr->s, e = hr->e;
    i64 m = (s + e) / 2;

    auto lo = hr->v, hi = l;
    if (lo.get(s) > hi.get(s)) swap(lo, hi);

    if (lo.get(e) <= hi.get(e)) {
        hr->v = hi;
        return;
    }

    if (lo.get(m) < hi.get(m)) {
        hr->v = hi;
        if (!hr->r) hr->r = new Node(m + 1, e);
        update(hr->r, lo);
    } else {
        hr->v = lo;
        if (!hr->l) hr->l = new Node(s, m);
        update(hr->l, hi);
    }
}

i64 query(Node* hr, const i64 x) {
    if (!hr) return -inf;

    i64 s = hr->s, e = hr->e;
    i64 m = (s + e) / 2;

    return max(hr->v.get(x), x <= m ? query(hr->l, x) : query(hr->r, x));
}
};  // namespace LiChao

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];

    i64 _su = 0;
    i64 _ssu = 0;
    auto root = LiChao::init(-2e12, 2e12);

    vector<i64> d(N);
    for (int i = 0; i < N; i++) {
        LiChao::update(root, Line(-i, i * _su - _ssu));
        _su += v[i];
        _ssu += (i + 1) * v[i];
        d[i] = max(d[i], LiChao::query(root, _su) + _ssu);
    }

    cout << *max_element(iterall(d)) << endl;
    return 0;
}