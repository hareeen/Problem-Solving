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

inline i64 ceil(i64 n, i64 d) {
    if (n > 0) return n / d;
    return (n - d + 1) / d;
}

class Node {
   public:
    i64 mx, mi, lsq, su, lz;
    int mxct;
    bool lsqt, lsqv;

    Node() = default;
    Node(i64 _mx, i64 _mi, int _mxct, i64 _su, bool _lsqv = false, i64 _lsq = 0, bool _lsqt = false, i64 _lz = 0) {
        tie(mx, mi, mxct, su, lsqv, lsq, lsqt, lz) = {_mx, _mi, _mxct, _su, _lsqv, _lsq, _lsqt, _lz};
    }
};

Node operator+(const Node& l, const Node& r) {
    if (l.mx == r.mx)
        return {l.mx, min(l.mi, r.mi), l.mxct + r.mxct, l.su + r.su};
    else if (l.mx > r.mx)
        return {l.mx, min(l.mi, r.mi), l.mxct, l.su + r.su};
    else
        return {r.mx, min(l.mi, r.mi), r.mxct, l.su + r.su};
}

class SegTree {
   public:
    int N;
    vector<Node> vl;

    SegTree() = default;
    SegTree(int _N) {
        N = _N;
        vl.resize((N << 2) + 1);
    }

    Node init(int s, int e, int n, const vector<i64>& A) {
        if (s == e) return vl[n] = {A[s], A[s], 1, A[s]};

        int m = (s + e) >> 1, k = n << 1;
        return vl[n] = init(s, m, k, A) + init(m + 1, e, k + 1, A);
    }
    void init(const vector<i64>& A) {
        init(1, N, 1, A);
    }

    void propagate(int s, int e, int n) {
        i64 len = e - s + 1;

        if (s != e) {
            int k = n << 1;

            for (auto i : {k, k + 1}) {
                if (vl[n].lsqv) {
                    if (vl[n].lsqt) {
                        vl[i].lsq = vl[n].lsq;
                        vl[i].lsqt = true;
                    } else {
                        i64 tmx, tmi;

                        if (vl[i].lsqt)
                            tmx = tmi = vl[i].lsq + vl[i].lz;
                        else if (vl[i].lsq)
                            tmx = vl[i].lsq + vl[i].lz, tmi = vl[i].lsq + vl[i].lz - 1;
                        else
                            tmx = vl[i].mx + vl[i].lz, tmi = vl[i].mi + vl[i].lz;

                        if (tmx == tmi) {
                            if (tmx == vl[n].mx)
                                vl[i].lsq = vl[n].lsq;
                            else
                                vl[i].lsq = vl[n].lsq - 1;

                            vl[i].lsqt = true;
                        } else {
                            vl[i].lsq = vl[n].lsq;
                            vl[i].lsqt = false;
                        }
                    }

                    vl[i].lsqv = true;
                    vl[i].lz = 0;
                }

                if (vl[n].lz) {
                    vl[i].lz += vl[n].lz;
                }
            }
        }

        if (vl[n].lsqv) {
            if (vl[n].lsqt) {
                vl[n].mx = vl[n].mi = vl[n].lsq;
                vl[n].su = vl[n].lsq * len;
                vl[n].mxct = len;
            } else {
                vl[n].mx = vl[n].lsq;
                vl[n].mi = vl[n].lsq - 1;
                vl[n].su = (vl[n].lsq - 1) * len + vl[n].mxct;
            }
        }

        if (vl[n].lz) {
            vl[n].mx += vl[n].lz;
            vl[n].mi += vl[n].lz;
            vl[n].su += vl[n].lz * len;
        }

        vl[n].lsq = 0;
        vl[n].lsqv = false;
        vl[n].lsqt = false;
        vl[n].lz = 0;
    }

    void update_sum(int s, int e, int n, int l, int r, i64 d) {
        propagate(s, e, n);

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            vl[n].lz = d;
            propagate(s, e, n);
            return;
        }

        int m = (s + e) >> 1, k = n << 1;
        update_sum(s, m, k, l, r, d);
        update_sum(m + 1, e, k + 1, l, r, d);
        vl[n] = vl[k] + vl[k + 1];
    }
    void update_sum(int l, int r, i64 d) {
        update_sum(1, N, 1, l, r, d);
    }

    void update_div(int s, int e, int n, int l, int r, i64 d) {
        propagate(s, e, n);

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            i64 mxs = ceil(vl[n].mx, d);
            i64 mis = ceil(vl[n].mi, d);

            if (mxs == mis) {
                vl[n].lsq = mxs;
                vl[n].lsqv = true;
                vl[n].lsqt = true;
                propagate(s, e, n);
                return;
            }

            if (vl[n].mx - vl[n].mi == 1) {
                vl[n].lsq = mxs;
                vl[n].lsqv = true;
                vl[n].lsqt = false;
                propagate(s, e, n);
                return;
            }
        }

        int m = (s + e) >> 1, k = n << 1;
        update_div(s, m, k, l, r, d);
        update_div(m + 1, e, k + 1, l, r, d);
        vl[n] = vl[k] + vl[k + 1];
    }
    void update_div(int l, int r, i64 d) {
        update_div(1, N, 1, l, r, d);
    }

    i64 query_sum(int s, int e, int n, int l, int r) {
        propagate(s, e, n);

        if (r < s || e < l) return 0LL;
        if (l <= s && e <= r) return vl[n].su;

        int m = (s + e) >> 1, k = n << 1;
        return query_sum(s, m, k, l, r) + query_sum(m + 1, e, k + 1, l, r);
    }
    i64 query_sum(int l, int r) {
        return query_sum(1, N, 1, l, r);
    }

    i64 query_min(int s, int e, int n, int l, int r) {
        propagate(s, e, n);

        if (r < s || e < l) return numeric_limits<i64>::max();
        if (l <= s && e <= r) return vl[n].mi;

        int m = (s + e) >> 1, k = n << 1;
        return min(query_min(s, m, k, l, r), query_min(m + 1, e, k + 1, l, r));
    }
    i64 query_min(int l, int r) {
        return query_min(1, N, 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<i64> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    SegTree ST(N);
    ST.init(A);

    while (Q--) {
        int qt;
        cin >> qt;

        int L, R;
        i64 X;
        switch (qt) {
            case 1:
                cin >> L >> R >> X;
                L++, R++;
                ST.update_sum(L, R, X);
                break;

            case 2:
                cin >> L >> R >> X;
                L++, R++;
                ST.update_div(L, R, X);
                break;

            case 3:
                cin >> L >> R;
                L++, R++;
                cout << ST.query_min(L, R) << "\n";
                break;
            
            case 4:
                cin >> L >> R;
                L++, R++;
                cout << ST.query_sum(L, R) << "\n";
                break;

            default:
                break;
        }
    }

    return 0;
}
