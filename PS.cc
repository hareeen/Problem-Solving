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

inline i64 fsqrt(i64 x) {
    i64 s = 1, e = min(x, static_cast<i64>(numeric_limits<int>::max()));
    while (s < e) {
        i64 m = ((s + e) >> 1) + 1;
        if (x >= m * m)
            s = m;
        else
            e = m - 1;
    }

    return s;
}

class Node {
   public:
    i64 mx, mi, lsq, su, lz;
    int mxct;
    bool lsqt;

    Node() = default;
    Node(i64 _mx, i64 _mi, int _mxct, i64 _su, i64 _lsq = 0, bool _lsqt = false, i64 _lz = 0) {
        tie(mx, mi, mxct, su, lsq, lsqt, lz) = {_mx, _mi, _mxct, _su, _lsq, _lsqt, _lz};
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
                if (vl[n].lsq) {
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

                    vl[i].lz = 0;
                }

                if (vl[n].lz) {
                    vl[i].lz += vl[n].lz;
                }
            }
        }

        if (vl[n].lsq) {
            if (vl[n].lsqt) {
                vl[n].mx = vl[n].mi = vl[n].lsq;
                vl[n].su = vl[n].lsq * len;
                vl[n].mxct = len;
            } else {
                // mx - mi = 1, there exists integer k that satisfies k^2 = mx
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

    void update_sqrt(int s, int e, int n, int l, int r) {
        propagate(s, e, n);

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            i64 mxs = fsqrt(vl[n].mx);
            i64 mis = fsqrt(vl[n].mi);

            if (mxs == mis) {
                vl[n].lsq = mxs;
                vl[n].lsqt = true;
                propagate(s, e, n);
                return;
            }

            if (vl[n].mx - vl[n].mi == 1) {
                vl[n].lsq = mxs;
                vl[n].lsqt = false;
                propagate(s, e, n);
                return;
            }
        }

        int m = (s + e) >> 1, k = n << 1;
        update_sqrt(s, m, k, l, r);
        update_sqrt(m + 1, e, k + 1, l, r);
        vl[n] = vl[k] + vl[k + 1];
    }
    void update_sqrt(int l, int r) {
        update_sqrt(1, N, 1, l, r);
    }

    i64 query(int s, int e, int n, int l, int r) {
        propagate(s, e, n);

        if (r < s || e < l) return 0LL;
        if (l <= s && e <= r) return vl[n].su;

        int m = (s + e) >> 1, k = n << 1;
        return query(s, m, k, l, r) + query(m + 1, e, k + 1, l, r);
    }
    i64 query(int l, int r) {
        return query(1, N, 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    SegTree ST(N);
    ST.init(A);

    int Q;
    cin >> Q;

    while (Q--) {
        int qt;
        cin >> qt;

        int L, R;
        i64 X;
        switch (qt) {
            case 1:
                cin >> L >> R >> X;
                ST.update_sum(L, R, X);
                break;

            case 2:
                cin >> L >> R;
                ST.update_sqrt(L, R);
                break;

            case 3:
                cin >> L >> R;
                cout << ST.query(L, R) << "\n";
                break;

            default:
                break;
        }
    }

    return 0;
}
