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

class kdtree {
   public:
    vector<pli> vl[262145];
    int nan[262145];

    void init(int n, int d, const vector<pli> &pts) {
        if (n == 1) vl[n] = pts;
        if (vl[n].size() <= 1) return;

        if (d % 2)
            sort(iterall(vl[n]));
        else
            sort(iterall(vl[n]), [](pli a, pli b) {
                return a.second != b.second ? a.second < b.second
                                            : a.first < b.first;
            });

        auto mid = (vl[n].size() - 1) / 2;
        for (int i = 0; i <= mid; i++) vl[n * 2].emplace_back(vl[n][i]);
        for (int i = mid + 1; i < vl[n].size(); i++)
            vl[n * 2 + 1].emplace_back(vl[n][i]);

        if (d % 2)
            nan[n] = vl[n][mid].first;
        else
            nan[n] = vl[n][mid].second;

        init(n * 2, d + 1, pts);
        init(n * 2 + 1, d + 1, pts);
    }

    inline i64 ab(i64 a) { return a > 0 ? a : -a; }

    inline i64 sq(i64 x) {
        return x*x;
    }

    i64 dist(pli x, pli y) {
        return (x.first - y.first) * (x.first - y.first) +
               (x.second - y.second) * (x.second - y.second);
    }

    void query(int n, int d, i64 &m, const pli q) {
        if (vl[n].size() == 1) {
            if (dist(q, vl[n][0]) == 0) return;
            m = min(m, dist(q, vl[n][0]));
            return;
        }

        if (d % 2) {
            if (q.first <= nan[n]) {
                query(n * 2, d + 1, m, q);
                if (sq(nan[n] - q.first) < m) query(n * 2 + 1, d + 1, m, q);
            } else {
                query(n * 2 + 1, d + 1, m, q);
                if (sq(q.first - nan[n]) < m) query(n * 2, d + 1, m, q);
            }
        } else {
            if (q.second <= nan[n]) {
                query(n * 2, d + 1, m, q);
                if (sq(nan[n] - q.second) < m) query(n * 2 + 1, d + 1, m, q);
            } else {
                query(n * 2 + 1, d + 1, m, q);
                if (sq(q.second - nan[n]) < m) query(n * 2, d + 1, m, q);
            }
        }
    }
};

void process() {
    int N;
    cin >> N;

    vector<pli> pt(N);
    for (int i = 0; i < N; i++) cin >> pt[i].first >> pt[i].second;

    auto kd = kdtree();
    kd.init(1, 1, pt);

    for (auto el : pt) {
        i64 m = numeric_limits<i64>::max();
        kd.query(1, 1, m, el);
        cout << m << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) process();

    return 0;
}