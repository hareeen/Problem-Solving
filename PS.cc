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

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class Node {
public:
    int s, e, v;
    Node *l, *r;

    Node() {
        s = e = v = 0;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _v) {
        s = _s, e = _e, v = _v;
        l = r = nullptr;
    }

    Node(int _s, int _e, int _v, Node *_l, Node *_r) {
        s = _s, e = _e, v = _v;
        l = _l, r = _r;
    }
};

namespace PST {
    Node *init(int s, int e) {
        if (s == e) return new Node(s, e, 0);

        int m = s + e >> 1;
        auto l = init(s, m), r = init(m + 1, e);
        return new Node(s, e, l->v + r->v, l, r);
    }

    Node *update(Node *h, const int t, const int d) {
        auto s = h->s, e = h->e, v = h->v;
        if (t < s || e < t) return h;
        if (s == e) return new Node(s, e, v + d);

        int m = s + e >> 1;
        auto l = update(h->l, t, d), r = update(h->r, t, d);
        return new Node(s, e, v + d, l, r);
    }

    int query(Node *h, const int l, const int r) {
        auto s = h->s, e = h->e, v = h->v;
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return v;
        return query(h->l, l, r) + query(h->r, l, r);
    }

    int q2(Node *lo, Node *hi, const int x, int b = 18) {
        if (b < 0) return lo->s;
        if (x & (1 << b)) {
            if (lo->l->v != hi->l->v) return q2(lo->l, hi->l, x, b - 1);
            return q2(lo->r, hi->r, x, b - 1);
        } else {
            if (lo->r->v != hi->r->v) return q2(lo->r, hi->r, x, b - 1);
            return q2(lo->l, hi->l, x, b - 1);
        }
    }

    int q5(Node *lo, Node *hi, int x, int b = 18) {
        if (b < 0) return lo->s;
        if (hi->l->v - lo->l->v >= x) return q5(lo->l, hi->l, x, b - 1);
        return q5(lo->r, hi->r, x - hi->l->v + lo->l->v, b - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<Node *> roots(1, PST::init(0, (1 << 19) - 1));

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int qt, L, R, x;
        cin >> qt;

        if (qt == 1) {
            cin >> x;
            roots.emplace_back(PST::update(roots.back(), x, 1));
        } else if (qt == 2) {
            cin >> L >> R >> x;
            cout << PST::q2(roots[L - 1], roots[R], x) << '\n';
        } else if (qt == 3) {
            cin >> x;
            roots.erase(roots.end() - x, roots.end());
        } else if (qt == 4) {
            cin >> L >> R >> x;
            cout << PST::query(roots[R], 0, x) - PST::query(roots[L - 1], 0, x) << '\n';
        } else if (qt == 5) {
            cin >> L >> R >> x;
            cout << PST::q5(roots[L - 1], roots[R], x) << '\n';
        }
    }

    return 0;
}