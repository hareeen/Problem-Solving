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
        s = _s, e = _e;
        v = Line();
        l = r = nullptr;
    }

    Node(i64 _s, i64 _e, i64 _a, i64 _b) {
        s = _s, e = _e;
        v = Line(_a, _b);
        l = r = nullptr;
    }
};

namespace LiChao {
Node* init(i64 s, i64 e) { return new Node(s, e); }

void update(Node* here, const Line d) {
    i64 s = here->s, e = here->e;
    i64 m = (s + e) / 2;

    auto lo = here->v, hi = d;
    if (lo.get(s) > hi.get(s)) swap(lo, hi);

    if (lo.get(e) < hi.get(e)) {
        here->v = hi;
        return;
    }

    if (lo.get(m) < hi.get(m)) {
        here->v = hi;
        if (!here->r) here->r = new Node(m + 1, e);
        update(here->r, lo);
    } else {
        here->v = lo;
        if (!here->l) here->l = new Node(s, m);
        update(here->l, hi);
    }
}

i64 query(Node* here, const i64 x) {
    if (!here) return -inf;

    i64 s = here->s, e = here->e;
    i64 m = (s + e) / 2;

    return max(here->v.get(x), x <= m ? query(here->l, x) : query(here->r, x));
}
};  // namespace LiChao

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    auto root = LiChao::init(-1e12, 1e12);
    for (int i = 0; i < N; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            i64 a, b;
            cin >> a >> b;
            LiChao::update(root, Line(a, b));
        } else {
            i64 x;
            cin >> x;
            cout << LiChao::query(root, x) << '\n';
        }
    }

    return 0;
}