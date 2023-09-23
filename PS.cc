#include <bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;

using li = long long;
using ld = long double;
using pi = pair<int, int>;
using pli = pair<li, li>;

#define all(c) c.begin(), c.end()
#define prec(n) setprecision(n) << fixed

template <typename T>
class AdditiveMaxSegTree {
   public:
    uint N, sz;
    vector<T> mx, lz;
    vector<uint> mxi;

    explicit AdditiveMaxSegTree(uint _N) : N(_N), sz(bit_ceil(N) << 1), lz(sz), mx(sz), mxi(sz) {
        function<void(uint, uint, uint)> _init = [&](uint s, uint e, uint n) {
            mxi[n] = s;

            if (s != e) {
                uint m = (s + e) >> 1, k = n << 1;
                _init(s, m, k);
                _init(m + 1, e, k | 1);
            }
        };

        _init(0, N - 1, 1);
    }

    void propagate(uint s, uint e, uint n) {
        mx[n] += lz[n];

        if (s != e) {
            uint k = n << 1;
            lz[k] += lz[n];
            lz[k | 1] += lz[n];
        }

        lz[n] = 0;
    }

    void update(uint s, uint e, uint n, uint l, uint r, T a) {
        propagate(s, e, n);

        if (r < s || e < l) return;

        if (l <= s && e <= r) {
            lz[n] += a;
            propagate(s, e, n);
            return;
        }

        uint m = (s + e) >> 1, k = n << 1;
        update(s, m, k, l, r, a);
        update(m + 1, e, k | 1, l, r, a);

        if (mx[k] > mx[k | 1])
            mx[n] = mx[k], mxi[n] = mxi[k];
        else
            mx[n] = mx[k | 1], mxi[n] = mxi[k | 1];
    }

    inline void update(uint l, uint r, T a) { update(0, N - 1, 1, l, r, a); }
    inline pair<T, uint> query() {
        propagate(0, N - 1, 1);
        return {mx[1], mxi[1]};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint N;
    cin >> N;

    N = (N / 2) - 1;
    vector<tuple<int, int, int>> horizontalSegments;

    int R;
    {
        int y, s, e;
        cin >> s >> y;
        for (uint i = 0; i < N; i++) {
            cin >> s >> y;
            cin >> e >> y;
            horizontalSegments.emplace_back(y, s, e);
        }
        cin >> e >> y;
        R = e;
    }

    ranges::sort(horizontalSegments);

    map<int, int> seps;
    seps.emplace(0, 0);
    seps.emplace(R, 0);

    vector<tuple<int, int, li>> floodingIntervals;
    for (auto [y, s, e] : horizontalSegments) {
        auto it = seps.upper_bound(s);
        auto le = it->first, ls = prev(it)->first;
        auto ly = max(it->second, prev(it)->second);

        li flood = (li)(y - ly) * (le - ls);
        floodingIntervals.emplace_back(ls, le, flood);
        seps[s] = y;
        seps[e] = y;
    }

    ranges::sort(floodingIntervals, [](const auto& lhs, const auto& rhs) {
        return pi(get<0>(lhs), -get<1>(lhs)) < pi(get<0>(rhs), -get<1>(rhs));
    });

    vector<optional<uint>> par(N);
    stack<uint> stk;
    for (uint i = 0; i < N; i++) {
        auto [s, e, w] = floodingIntervals[i];

        while (!stk.empty()) {
            auto [ts, te, tw] = floodingIntervals[stk.top()];
            if (ts <= s && e <= te) break;
            stk.pop();
        }

        if (!stk.empty()) par[i] = stk.top();
        stk.emplace(i);
    }

    vector<bool> isLeaf(N, true);
    for (auto p : par)
        if (p) isLeaf[*p] = false;

    vector<uint> leafidx;
    for (uint i = 0; i < N; i++)
        if (isLeaf[i]) leafidx.emplace_back(i);

    uint L = leafidx.size();
    vector<int> leafSegmentLeft;
    for (auto i : leafidx) leafSegmentLeft.emplace_back(get<0>(floodingIntervals[i]));

    AdditiveMaxSegTree<li> ST(L);
    for (auto& [s, e, w] : floodingIntervals) {
        s = ranges::lower_bound(leafSegmentLeft, s) - leafSegmentLeft.begin();
        e = ranges::upper_bound(leafSegmentLeft, e) - leafSegmentLeft.begin() - 1;

        ST.update(s, e, w);
    }

    uint K;
    cin >> K;

    K = min(K, L);

    li res = 0;
    vector<bool> vst(N);
    while (K--) {
        auto [mx, mxi] = ST.query();
        mxi = leafidx[mxi];

        res += mx;

        while (true) {
            auto [s, e, w] = floodingIntervals[mxi];
            ST.update(s, e, -w);

            vst[mxi] = true;
            if (!par[mxi] || vst[*par[mxi]]) break;
            mxi = *par[mxi];
        }
    }

    cout << res << '\n';

    return 0;
}
