#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class segTree {
private:
    vector<i64> vl, lz;
public:
    segTree() {
        vl.clear();
        lz.clear();
        vl.resize(2097152 + 1);
        lz.resize(2097152 + 1);
    }

    i64 init(int s, int e, int nd, const vector<i64> &arr) {
        if (s == e) return vl[nd] = arr[s];
        else return vl[nd] = init(s, (s + e) / 2, nd * 2, arr) + init((s + e) / 2 + 1, e, nd * 2 + 1, arr);
    }

    void propagate(int s, int e, int nd) {
        if (!lz[nd]) return;
        vl[nd] += lz[nd] * (e - s + 1);

        if (s != e) {
            lz[nd * 2] += lz[nd];
            lz[nd * 2 + 1] += lz[nd];
        }

        lz[nd] = 0;
    }

    void update(int s, int e, int nd, const int l, const int r, const i64 d) {
        propagate(s, e, nd);
        if (e < l || r < s) return;
        if (l <= s && e <= r) {
            lz[nd] += d;
            propagate(s, e, nd);
            return;
        }
        update(s, (s + e) / 2, nd * 2, l, r, d);
        update((s + e) / 2 + 1, e, nd * 2 + 1, l, r, d);
        vl[nd] = vl[nd * 2] + vl[nd * 2 + 1];
    }

    i64 query(int s, int e, int nd, const int l, const int r) {
        propagate(s, e, nd);
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) return vl[nd];
        return query(s, (s + e) / 2, nd * 2, l, r) + query((s + e) / 2 + 1, e, nd * 2 + 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q1, Q2;
    cin >> N >> Q1 >> Q2;

    vector<i64> arr(N + 1);
    for (int i = 1; i <= N; i++) cin >> arr[i];

    auto sT = segTree();
    sT.init(1, N, 1, arr);

    for (int i = 0; i < Q1 + Q2; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int n, m;
            cin >> n >> m;
            cout << sT.query(1, N, 1, n, m) << '\n';
        } else {
            int s, e;
            i64 l;
            cin >> s >> e >> l;
            sT.update(1, N, 1, s, e, l);
        }
    }

    return 0;
}