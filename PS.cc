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
    vector<int> vl, lz;
public:
    segTree() {
        vl.clear();
        lz.clear();
        vl.resize(1048576 + 1);
        lz.resize(1048576 + 1);
    }

    int init(int s, int e, int nd, const vector<int> &arr) {
        if (s == e) return vl[nd] = arr[s];
        else return vl[nd] = init(s, (s + e) / 2, nd * 2, arr) ^ init((s + e) / 2 + 1, e, nd * 2 + 1, arr);
    }

    void propagate(int s, int e, int nd) {
        if (!lz[nd]) return;
        vl[nd] ^= lz[nd];

        if (s != e) {
            lz[nd * 2] ^= lz[nd];
            lz[nd * 2 + 1] ^= lz[nd];
        }

        lz[nd] = 0;
    }

    void update(int s, int e, int nd, const int l, const int r, const int d) {
        propagate(s, e, nd);
        if (e < l || r < s) return;
        if (l <= s && e <= r) {
            lz[nd] ^= d;
            propagate(s, e, nd);
            return;
        }
        update(s, (s + e) / 2, nd * 2, l, r, d);
        update((s + e) / 2 + 1, e, nd * 2 + 1, l, r, d);
        vl[nd] = vl[nd * 2] ^ vl[nd * 2 + 1];
    }

    int query(int s, int e, int nd, const int l, const int r) {
        propagate(s, e, nd);
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) return vl[nd];
        return query(s, (s + e) / 2, nd * 2, l, r) ^ query((s + e) / 2 + 1, e, nd * 2 + 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<int> arr(N + 1);
    for (int i = 1; i <= N; i++) cin >> arr[i];

    auto sT = segTree();
    sT.init(1, N, 1, arr);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++) {
        int q;
        cin >> q;

        if (q == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            a++, b++;
            sT.update(1, N, 1, a, b, c);
        } else {
            int a;
            cin >> a;
            a++;
            cout << sT.query(1, N, 1, a, a) << '\n';
        }
    }

    return 0;
}