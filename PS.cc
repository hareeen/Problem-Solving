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

const i64 ninf = numeric_limits<i64>::min() / 2;

class Line {
   public:
    i64 a, b;

    Line() { a = 0, b = ninf; }

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

    void update(Node* h, const Line d, i64 l, i64 r) {
        i64 s = h->s, e = h->e;
        i64 m = (s + e) / 2;

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            auto lo = h->v, hi = d;
            if (lo.get(s) > hi.get(s)) swap(lo, hi);

            if (lo.get(e) <= hi.get(e)) {
                h->v = hi;
                return;
            }

            if (lo.get(m) > hi.get(m)) {
                h->v = lo;
                if (!h->l) h->l = new Node(s, m);
                update(h->l, hi, l, r);
            } else {
                h->v = hi;
                if (!h->r) h->r = new Node(m + 1, e);
                update(h->r, lo, l, r);
            }

            return;
        }

        if (!h->l) h->l = new Node(s, m);
        if (!h->r) h->r = new Node(m + 1, e);
        update(h->l, d, l, r);
        update(h->r, d, l, r);
    }

    i64 query(Node* h, const i64 x) {
        if (!h) return ninf;

        i64 s = h->s, e = h->e;
        i64 m = (s + e) / 2;

        return max(h->v.get(x), x <= m ? query(h->l, x) : query(h->r, x));
    }
};  // namespace LiChao

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> arr(N);
    for (auto& el : arr) cin >> el;

    stack<pli> stk;
    Node* root = LiChao::init(0, N - 1);

    for (i64 i = 0; i < N; i++) {
        int tpi = i;
        while (!stk.empty() && stk.top().first > arr[i]) {
            auto [h, j] = stk.top();
            tpi = j;
            stk.pop();
            LiChao::update(root, Line(h, h * (1 - j)), j, i - 1);
        }
        stk.emplace(arr[i], tpi);
    }

    while (!stk.empty()) {
        auto [h, j] = stk.top();
        stk.pop();
        LiChao::update(root, Line(h, h * (1 - j)), j, N - 1);
    }


    vector<i64> res(N);
    for (int i = 0; i < N; i++) res[i] = LiChao::query(root, i);
    for (int i = 1; i < N; i++) res[i] = max(res[i - 1], res[i]);
    copy(iterall(res), ostream_iterator<i64>(cout, "\n"));

    return 0;
}
