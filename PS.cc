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

class Line {
private:
    i64 a, b;
public:
    Line() {
        a = 0, b = -1e18;
    }

    Line(i64 _a, i64 _b) {
        a = _a, b = _b;
    }

    inline i64 get(i64 x) {
        return a * x + b;
    }
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
    void update(Node *h, const Line v) {
        auto s = h->s, e = h->e;
        auto m = (s + e) / 2;

        auto lo = h->v, hi = v;
        if (lo.get(s) > hi.get(s)) swap(lo, hi);

        if (lo.get(e) <= hi.get(e)) {
            h->v = hi;
            return;
        }

        if (lo.get(m) < hi.get(m)) {
            h->v = hi;
            if (!h->r) h->r = new Node(m + 1, e);
            update(h->r, lo);
        } else {
            h->v = lo;
            if (!h->l) h->l = new Node(s, m);
            update(h->l, hi);
        }
    }

    i64 query(Node *h, const i64 x) {
        if (!h) return -1e18;

        auto m = (h->s + h->e) / 2;
        return max(h->v.get(x), x <= m ? query(h->l, x) : query(h->r, x));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    for (int rev = 0; rev < 2; rev++) {
        i64 su = 0, ans = -1e18;
        auto root = new Node(-1e9, 1e9);
        for (i64 i = 0; i < N; i++) {
            su += arr[i];
            ans = max(ans, LiChao::query(root, arr[i]) + arr[i] * (i + 1) - su);
            LiChao::update(root, Line(-i, su - arr[i]));
        }
        cout << ans + su << endl;
        reverse(iterall(arr));
    }

    return 0;
}