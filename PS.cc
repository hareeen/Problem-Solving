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

const i64 ninf = numeric_limits<i64>::min() / 2;

class Line {
   public:
    i64 a, b;

    Line() { a = 0, b = ninf; }

    Line(i64 _a, i64 _b) { a = _a, b = _b; }

    inline i64 get(i64 x) { return a * x + b; }
};

class Node {
   public:
    i64 s, e;
    Line v;
    Node *l, *r;

    Node() {
        s = e = 0;
        v = Line();
        l = r = nullptr;
    }

    Node(i64 _s, i64 _e) {
        s = _s, e = _e;
        v = Line();
        l = r = nullptr;
    }

    Node(i64 _s, i64 _e, i64 _a, i64 _b) {
        s = _s, e = _e;
        v = Line(_a, _b);
        l = r = nullptr;
    }
};

class LiChaoSeg {
   public:
    int N;
    vector<i64> cor;
    vector<Line> vl;

    LiChaoSeg() = default;
    LiChaoSeg(const vector<i64>& _cor) {
        cor = _cor;
        N = cor.size();
        vl.resize(4*N);
    }

    void update(int s, int e, int n, int l, int r, Line v) {
        int m = s + e >> 1, k = n << 1;
        i64 cs = cor[s], ce = cor[e], cm = cor[m];

        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            auto lo = vl[n], hi = v;
            if (lo.get(cs) > hi.get(cs)) swap(lo, hi);

            if (lo.get(ce) <= hi.get(ce)) {
                vl[n] = hi;
                return;
            }

            if (lo.get(cm) > hi.get(cm)) {
                vl[n] = lo;
                update(s, m, k, l, r, hi);
            } else {
                vl[n] = hi;
                update(m + 1, e, k + 1, l, r, lo);
            }

            return;
        }

        update(s, m, k, l, r, v);
        update(m + 1, e, k + 1, l, r, v);
    }
    inline void update(int l, int r, Line v) {
        update(0, N - 1, 1, l, r, v);
    }

    i64 query(int s, int e, int n, int t) {
        i64 m = s + e >> 1, k = n << 1;

        if (s == e)
            return vl[n].get(cor[t]);
        else
            return max(vl[n].get(cor[t]), t <= m ? query(s, m, k, t) : query(m + 1, e, k + 1, t));
    }
    inline i64 query(int t) {
        return query(0, N - 1, 1, t);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pli> pts(N);
    for (auto& [x, y] : pts) cin >> x >> y;

    N = N / 2 - 1;
    vector<tli> arr;
    for (int i = 1; i + 1 < static_cast<int>(pts.size()); i += 2) {
        const auto& [l, h] = pts[i];
        const auto& [r, _] = pts[i + 1];
        arr.emplace_back(l, r, h);
    }

    if (N == 1) {
        auto [l, r, h] = arr[0];
        cout << (r - l) * h << endl;
        return 0;
    }

    vector<i64> res(N - 1);
    const i64 R = get<1>(arr.back());

    {
        vector<i64> cor(1, 0);
        for (const auto& [l, r, h] : arr) cor.emplace_back(r);
        stack<pli> stk;
        LiChaoSeg seg(cor);

        for (int i = 0; i < N; i++) {
            const auto& [l, r, h] = arr[i];
            i64 ml = i;

            while (!stk.empty() && stk.top().first > h) {
                auto [lh, ll] = stk.top();
                ml = ll;
                stk.pop();
                seg.update(ll, i, Line(lh, -lh * cor[ll]));
            }
            stk.emplace(h, ml);
        }

        while (!stk.empty()) {
            auto [h, l] = stk.top();
            stk.pop();
            seg.update(l, N, Line(h, -h * cor[l]));
        }

        for (int i = 0; i < N - 1; i++) {
            res[i] += seg.query(i + 1);
        }
    }

    reverse(iterall(arr));
    reverse(iterall(res));
    for (auto& [l, r, h] : arr) {
        swap(l, r);
        l = R - l;
        r = R - r;
    }

    {
        vector<i64> cor(1, 0);
        for (const auto& [l, r, h] : arr) cor.emplace_back(r);
        stack<pli> stk;
        LiChaoSeg seg(cor);

        for (int i = 0; i < N; i++) {
            const auto& [l, r, h] = arr[i];
            i64 ml = i;

            while (!stk.empty() && stk.top().first > h) {
                auto [lh, ll] = stk.top();
                ml = ll;
                stk.pop();
                seg.update(ll, i, Line(lh, -lh * cor[ll]));
            }
            stk.emplace(h, ml);
        }

        while (!stk.empty()) {
            auto [h, l] = stk.top();
            stk.pop();
            seg.update(l, N, Line(h, -h * cor[l]));
        }

        for (int i = 0; i < N - 1; i++) {
            res[i] += seg.query(i + 1);
        }
    }

    cout << *max_element(iterall(res)) << endl;

    return 0;
}
