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

class Node {
   public:
    i64 mx, mx2, mxct, su;
    Node() { mx = 0, mx2 = 0, mxct = 0, su = 0; }
    Node(i64 _mx, i64 _mx2, i64 _mxct, i64 _su) {
        mx = _mx, mx2 = _mx2, mxct = _mxct, su = _su;
    }
};

Node operator+(const Node& l, const Node& r) {
    if (l.mx == r.mx)
        return {l.mx, max(l.mx2, r.mx2), l.mxct + r.mxct, l.su + r.su};
    if (l.mx > r.mx) return {l.mx, max(r.mx, l.mx2), l.mxct, l.su + r.su};
    return {r.mx, max(l.mx, r.mx2), r.mxct, l.su + r.su};
}

class segTreeBeats {
   public:
    vector<Node> vl;
    int sz;

    segTreeBeats(int _sz) {
        vl.resize((1 << 21) + 1);
        sz = _sz;
    }

    Node init(int s, int e, int n, const vector<i64>& arr) {
        if (s == e) return vl[n] = {arr[s], -1, 1, arr[s]};
        return vl[n] = init(s, (s + e) / 2, n * 2, arr) +
                       init((s + e) / 2 + 1, e, n * 2 + 1, arr);
    }

    void init(const vector<i64>& arr) { init(1, sz, 1, arr); }

    void push(int s, int e, int n) {
        if (s == e) return;
        for (auto i : {n * 2, n * 2 + 1}) {
            if (vl[n].mx < vl[i].mx) {
                vl[i].su -= vl[i].mxct * (vl[i].mx - vl[n].mx);
                vl[i].mx = vl[n].mx;
            }
        }
    }

    void update(int s, int e, int n, const int l, const int r, const i64 u) {
        push(s, e, n);
        if (r < s || e < l || vl[n].mx <= u) return;
        if (l <= s && e <= r && vl[n].mx2 < u) {
            vl[n].su -= vl[n].mxct * (vl[n].mx - u);
            vl[n].mx = u;
            push(s, e, n);
            return;
        }

        update(s, (s + e) / 2, n * 2, l, r, u);
        update((s + e) / 2 + 1, e, n * 2 + 1, l, r, u);
        vl[n] = vl[n * 2] + vl[n * 2 + 1];
    }

    void update(const int l, const int r, const i64 u) {
        update(1, sz, 1, l, r, u);
    }

    i64 query_max(int s, int e, int n, const int l, const int r) {
        push(s, e, n);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[n].mx;
        return max(query_max(s, (s + e) / 2, n * 2, l, r),
                   query_max((s + e) / 2 + 1, e, n * 2 + 1, l, r));
    }

    i64 query_max(const int l, const int r) {
        return query_max(1, sz, 1, l, r);
    }

    i64 query_sum(int s, int e, int n, const int l, const int r) {
        push(s, e, n);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return vl[n].su;
        return query_sum(s, (s + e) / 2, n * 2, l, r) +
               query_sum((s + e) / 2 + 1, e, n * 2 + 1, l, r);
    }

    i64 query_sum(const int l, const int r) {
        return query_sum(1, sz, 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> arr(N + 1);
    for (int i = 1; i <= N; i++) cin >> arr[i];

    auto sTB = segTreeBeats(N);
    sTB.init(arr);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int qt;
        cin >> qt;

        int l, r;
        i64 x = 0;
        cin >> l >> r;
        if (qt == 1) cin >> x;

        if (qt == 1) sTB.update(l, r, x);
        if (qt == 2) cout << sTB.query_max(l, r) << '\n';
        if (qt == 3) cout << sTB.query_sum(l, r) << '\n';
    }

    return 0;
}