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

pli operator-(const pli &l, const pli &r) { return {r.x - l.x, r.y - l.y}; }

inline i64 ccw(pli p1, pli p2, pli p3) {
    auto [x1, y1] = p2 - p1;
    auto [x2, y2] = p3 - p1;

    return x1 * y2 - y1 * x2;
}

inline i64 dist(pli p1, pli p2) {
    auto [xx, yy] = p2 - p1;
    return xx * xx + yy * yy;
}

void process() {
    int N;
    cin >> N;

    deque<pair<pli, int>> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].first.x >> v[i].first.y, v[i].second = i;   

    sort(iterall(v));

    auto pt = v[0];
    v.pop_front();
    sort(iterall(v), [&pt](auto l, auto r) {
        auto c = ccw(pt.first, l.first, r.first);
        if (c != 0) return c > 0;
        return dist(pt.first, l.first) < dist(pt.first, r.first);
    });

    auto iter = v.end() - 1;
    while (ccw(iter->first, v.back().first, pt.first) == 0) --iter;
    ++iter;

    reverse(iter, v.end());

    cout << pt.second << " ";
    for (auto el : v) cout << el.second << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int C;
    cin >> C;

    for (int i = 0; i < C; i++) process();

    return 0;
}