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

#define x first
#define y second

pli operator-(const pli &l, const pli &r) { return {l.x - r.x, l.y - r.y}; }

inline i64 ccw(pli p1, pli p2, pli p3) {
    auto [x1, y1] = p2 - p1;
    auto [x2, y2] = p3 - p1;
    return x1 * y2 - x2 * y1;
}

i64 dir(pli p1, pli p2, pli p3) {
    auto c = ccw(p1, p2, p3);
    if (c > 0) return 1;
    if (c == 0) return 0;
    return -1;
}

bool on_line(pli p1, pli p2, pli q) {
    return ccw(p1, p2, q) == 0 && p1.x <= q.x && q.x <= p2.x && p1.y <= q.y &&
           q.y <= p2.y;
}

bool sub(vector<pli> &l1, vector<pli> &l2) {
    if(l1.size()==1) return true;
    if(l1.size()==2) {
        auto p1 = l1[0], p2 = l1[1];
        vector<bool> ch(3);

        for(auto q:l2) {
            if(on_line(p1, p2, q)) return false;

            auto c = dir(p1, p2, q)+1;
            if(c==1) continue;
            if(ch[2-c]) return false;
            ch[c] = true;        
        }

        return true;
    }

    vector<pli> uh, dh;
    int un = 0, dn = 0;

    sort(iterall(l1));
    for (auto pt : l1) {
        while (un >= 2 && ccw(uh[un - 2], uh[un - 1], pt) >= 0)
            uh.pop_back(), --un;
        uh.emplace_back(pt), ++un;
    }

    reverse(iterall(l1));
    for (auto pt : l1) {
        while (dn >= 2 && ccw(dh[dn - 2], dh[dn - 1], pt) >= 0)
            dh.pop_back(), --dn;
        dh.emplace_back(pt), ++dn;
    }

    vector<pli> hull = uh;
    for (int i = 1; i < dn - 1; i++) hull.emplace_back(dh[i]);

    int hs = un + dn - 2;
    for (auto q : l2) {
        for (int i = 0; i < hs; i++) {
            auto p1 = hull[i];
            auto p2 = hull[(i + 1) % hs];

            if (on_line(p1, p2, q)) return false;
            if (ccw(p1, p2, q) > 0) goto next;
        }

        return false;
    next:;
    }

    return true;
}

bool process() {
    int N, M;
    cin >> N >> M;

    vector<pli> l1(N), l2(M);
    for (int i = 0; i < N; i++) cin >> l1[i].x >> l1[i].y;
    for (int i = 0; i < M; i++) cin >> l2[i].x >> l2[i].y;

    return sub(l1, l2) && sub(l2, l1);    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) cout << (process() ? "YES" : "NO") << '\n';

    return 0;
}