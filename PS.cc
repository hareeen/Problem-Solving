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

#define x first
#define y second

pli operator-(const pli& lhs, const pli& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

i64 ccw(const pli& p1, const pli& p2, const pli& p3) {
    auto v1 = p2 - p1, v2 = p3 - p1;
    return v1.x * v2.y - v1.y * v2.x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    pli T, B;
    cin >> T.x >> T.y >> B.x >> B.y;

    vector<pli> pts({T, B});
    for (int i = 0; i < N; i++) {
        i64 yc, xs, xe;
        cin >> yc >> xs >> xe;

        auto c1 = ccw(B, T, {xs, yc}), c2 = ccw(B, T, {xe, yc});
        if (c1 == 0 || c2 == 0) continue;
        if (c1 > 0 ^ c2 > 0) continue;

        pts.emplace_back(c1 < 0 ? xs : xe, yc);
    }

    vector<pli> hull;
    int P;

    {
        int un = 0, dn = 0;
        vector<pli> uh, dh;

        sort(iterall(pts));
        for (auto p : pts) {
            while (un >= 2 && ccw(uh[un - 2], uh[un - 1], p) >= 0) --un, uh.pop_back();
            ++un, uh.emplace_back(p);
        }

        reverse(iterall(pts));
        for (auto p : pts) {
            while (dn >= 2 && ccw(dh[dn - 2], dh[dn - 1], p) >= 0) --dn, dh.pop_back();
            ++dn, dh.emplace_back(p);
        }

        copy(uh.begin(), uh.end(), back_inserter(hull));
        copy(dh.begin() + 1, dh.end() - 1, back_inserter(hull));
        P = un + dn - 2;
    }

    if (P == 2) {
        cout << 0 << endl;
        return 0;
    }

    i64 ans = 0;
    for (int i = 0; i < P - 2; i++) {
        int k = i + 2;
        for (int j = i + 1; j < P - 1; j++) {
            k = max(k, j + 1);
            
            i64 larea = abs(ccw(hull[i], hull[j], hull[k]));
            if (k < P - 1) {
                i64 narea = abs(ccw(hull[i], hull[j], hull[k + 1]));

                while (k < P - 1 && larea < narea) {
                    ++k;
                    larea = narea;

                    if (k == P - 1)
                        narea = -1;
                    else
                        narea = abs(ccw(hull[i], hull[j], hull[k + 1]));
                }
            }
            
            ans = max(ans, larea);
        }
    }

    cout << prec(10) << static_cast<long double>(ans) / 2.0L << endl;
    return 0;
}
