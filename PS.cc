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

using qli = tuple<i64, i64, i64, i64>;

inline i64 ccw(pli v1, pli v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<tli> lines;
    for (int i = 0; i < N; i++) {
        i64 l, r, y;
        cin >> l >> r >> y;

        if (l > r) swap(l, r);
        lines.emplace_back(l, r, y);
    }

    i64 ans = 0;
    for (auto [LL, RR, YY] : lines) {
        vector<pli> POINTS = {pli(LL, YY), pli(RR, YY)};
        for (auto [dpx, dpy] : POINTS) {
            i64 swp = RR - LL;
            vector<qli> points;

            int id = -1;
            for (auto [ll, rr, yy] : lines) {
                ++id;
                if (yy == dpy) continue;
                if (yy > dpy) {
                    points.emplace_back(dpx * 2 - ll, dpy * 2 - yy, id, -1);
                    points.emplace_back(dpx * 2 - rr, dpy * 2 - yy, id, 1);
                } else {
                    points.emplace_back(ll, yy, id, 1);
                    points.emplace_back(rr, yy, id, -1);
                }
            }

            for (auto& [xx, yy, id, op] : points) {
                xx -= dpx;
                yy = dpy - yy;
            }

            sort(iterall(points), [](qli lhs, qli rhs) {
                auto [lx, ly, li, lp] = lhs;
                auto [rx, ry, ri, rp] = rhs;

                auto c = ccw({lx, ly}, {rx, ry});
                if (c != 0) return c < 0;
                return lp > rp;
            });

            ans = max(ans, swp);
            for (auto& [xx, yy, id, op] : points) {
                swp += ((get<1>(lines[id]) - get<0>(lines[id])) * op);
                ans = max(ans, swp);
            }
        }
    }

    cout << ans << endl;
    return 0;
}