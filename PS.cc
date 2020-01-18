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

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

int M, N;

int xt, yt;
int t;
int d;

int lx, rx, ly, ry;
int l, r;

class Node {
public:
    int v;
    Node *l, *r;

    Node() {
        v = 0;
        l = r = nullptr;
    }
};

class segTree {
public:
    static void update(int s, int e, Node *here) {
        if (!here) return;

        if (t < s || e < t) return;
        if (s == e) {
            here->v = d;
            return;
        }

        if (s <= t && t <= (s + e) / 2) {
            if (!here->l) here->l = new Node();
            update(s, (s + e) / 2, here->l);
        } else {
            if (!here->r) here->r = new Node();
            update((s + e) / 2 + 1, e, here->r);
        }

        int q1 = 0, q2 = 0;
        if (here->l) q1 = here->l->v;
        if (here->r) q2 = here->r->v;
        here->v = max(q1, q2);
    }

    static int query(int s, int e, Node *here) {
        if (!here) return 0;
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return here->v;

        int q1 = 0, q2 = 0;
        if (here->l) q1 = query(s, (s + e) / 2, here->l);
        if (here->r) q2 = query((s + e) / 2 + 1, e, here->r);
        return max(q1, q2);
    }
};

class Node2d {
public:
    Node *v;
    Node2d *l, *r;

    Node2d() {
        v = nullptr;
        l = r = nullptr;
    }

    explicit Node2d(Node *_v) {
        v = _v;
        l = r = nullptr;
    }
};

class segTree2d {
public:
    static void update(int s, int e, Node2d *here) {
        if (!here) return;

        if (xt < s || e < xt) return;
        if (s == e) {
            segTree::update(1, N, here->v);
            return;
        }

        if (s <= xt && xt <= (s + e) / 2) {
            if (!here->l) here->l = new Node2d(new Node());
            update(s, (s + e) / 2, here->l);
        } else {
            if (!here->r) here->r = new Node2d(new Node());
            update((s + e) / 2 + 1, e, here->r);
        }

        int q1 = 0, q2 = 0;
        if (here->l) q1 = segTree::query(1, N, here->l->v);
        if (here->r) q2 = segTree::query(1, N, here->r->v);

        auto _d = d;
        d = max(q1, q2);
        segTree::update(1, N, here->v);
        d = _d;
    }

    static int query(int s, int e, Node2d *here) {
        if (!here) return 0;
        if (rx < s || e < lx) return 0;
        if (lx <= s && e <= rx) return segTree::query(1, N, here->v);

        int q1 = 0, q2 = 0;
        if (here->l) q1 = query(s, (s + e) / 2, here->l);
        if (here->r) q2 = query((s + e) / 2 + 1, e, here->r);
        return max(q1, q2);
    }
};

auto sT = new Node2d(new Node());

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> M >> N;

    vector<ti> v(N);
    for (int i = 0; i < N; i++) cin >> get<0>(v[i]);
    for (int i = 0; i < N; i++) cin >> get<1>(v[i]);
    if (M == 3) for (int i = 0; i < N; i++) cin >> get<2>(v[i]);
    else for (int i = 0; i < N; i++) get<2>(v[i]) = get<0>(v[i]);
    sort(iterall(v));

    vector<int> c1(N), c2(N);
    for (int i = 0; i < N; i++) c1[i] = get<1>(v[i]);
    for (int i = 0; i < N; i++) c2[i] = get<2>(v[i]);

    sort(iterall(c1));
    sort(iterall(c2));

    c1.erase(unique(iterall(c1)), c1.end());
    c2.erase(unique(iterall(c2)), c2.end());

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int cc1 = lower_bound(iterall(c1), get<1>(v[i])) - c1.begin() + 1;
        int cc2 = lower_bound(iterall(c2), get<2>(v[i])) - c2.begin() + 1;

        lx=1, rx=cc1;
        ly=1, ry=cc2;
        l=ly, r=ry;
        auto Q = segTree2d::query(1, N, sT) + 1;
        ans = max(ans, Q);

        d=Q;
        xt=cc1, yt=cc2;
        t=cc2;
        segTree2d::update(1, N, sT);
    }

    cout << ans << endl;
    return 0;
}