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

class SegTree {
    using data_t = pair<i64, int>;
public:
    int N{};
    vector<i64> vl, lz;
    vector<int> vp;

    SegTree() = default;

    explicit SegTree(int N) {
        this->N = N;

        vl.resize(N << 2);
        lz.resize(N << 2);
        vp.resize(N << 2);
    }

    void init(int s, int e, int n) {
        vp[n] = s;

        if (s == e) return;

        int m = (s + e) >> 1, k = n << 1;
        init(s, m, k);
        init(m + 1, e, k + 1);
    }

    inline void init() {
        init(1, N, 1);
    }

    static data_t mer(const data_t &l, const data_t &r) {
        if (l.first > r.first) return l;
        else return r;
    }

    void propagate(int s, int e, int n) {
        if (lz[n] == 0) return;

        if (s != e) {
            lz[(n << 1)] += lz[n];
            lz[(n << 1) | 1] += lz[n];
        }

        vl[n] += lz[n];
        lz[n] = 0;
    }

    void update(int s, int e, int n, int l, int r, i64 d) {
        propagate(s, e, n);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lz[n] += d;
            propagate(s, e, n);
            return;
        }

        int m = (s + e) >> 1, k = n << 1;
        update(s, m, k, l, r, d);
        update(m + 1, e, k | 1, l, r, d);

        tie(vl[n], vp[n]) = mer({vl[k], vp[k]}, {vl[k | 1], vp[k | 1]});
    }

    inline void update(int l, int r, i64 d) {
        update(1, N, 1, l, r, d);
    }

    inline data_t query() {
        propagate(1, N, 1);
        return {vl[1], vp[1]};
    }
};

class Tree {
public:
    int N{}, leafN{};
    int qc{};
    SegTree ST;
    vector<vector<int>> tr;
    vector<i64> vl;
    vector<int> par;
    vector<int> in, out;
    vector<int> in_inv;

    Tree() = default;

    explicit Tree(int N) {
        this->N = N;

        leafN = 0;
        qc = 0;

        tr.resize(N);
        vl.resize(N), par.resize(N);
        in.resize(N, 1e9), out.resize(N);
        in_inv.resize(N + 1);
    }

    inline void emplace_edge(int p, int c) {
        tr[p].emplace_back(c);
    }

    inline void advance_vl(int i, i64 d) {
        vl[i] += d;
    }

    pair<int, i64> compress(int h, bool u) {
        if (tr[h].size() == 1) {
            auto t = tr[h][0];
            auto[c, v] = compress(t, true);
            v += vl[h];

            if (u) return {c, v};

            tr[h] = tr[c];
            tr[c].clear();
            vl[h] = v;
            return {h, v};
        }

        for (auto t: tr[h]) compress(t, false);
        return {h, vl[h]};
    }

    void numbering(int h, int p = -1) {
        par[h] = p;

        if (tr[h].empty()) {
            leafN++;
            in[h] = out[h] = leafN;
            in_inv[leafN] = h;
            return;
        }

        for (auto t: tr[h]) {
            numbering(t, h);
            in[h] = min(in[h], in[t]);
            out[h] = max(out[h], out[t]);
        }
    }

    void seg_init() {
        ST = SegTree(leafN);
        ST.init();

        for (int i = 0; i < N; i++) {
            if (in[i] > leafN) continue;
            ST.update(in[i], out[i], vl[i]);
        }
    }

    void rollback(int h) {
        if (h < 0 || vl[h] == 0) return;
        ST.update(in[h], out[h], -vl[h]);
        vl[h] = 0;
        rollback(par[h]);
    }

    i64 query() {
        qc++;
        if (qc > leafN) return 0;

        auto[v, p] = ST.query();
        rollback(in_inv[p]);

        return v;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<pi> pts(N);
    for (auto &[x, y] : pts)
        cin >> x >> y;

    int K;
    cin >> K;


    vector<tli> segs, rngs;
    for (int i = 1; i < N - 1; i += 2) {
        const auto &[sx, y] = pts[i];
        const auto &[ex, _] = pts[i + 1];
        segs.emplace_back(y, sx, ex);
    }
    rngs = segs;

    {
        segs.emplace_back(-1, get<1>(segs.front()), get<1>(segs.front()));

        stack<int> stk;
        stk.emplace((int) segs.size() - 1);

        for (int i = 0; i < (int) segs.size() - 1; i++) {
            const auto &[y, sx, ex] = segs[i];

            while (!stk.empty() && get<0>(segs[stk.top()]) >= y) stk.pop();
            const auto &pi = stk.top();
            const auto &[py, psx, pex] = segs[pi];

            get<1>(rngs[i]) = pex;
            stk.emplace(i);
        }

        segs.pop_back();
    }

    {
        segs.emplace_back(-1, get<2>(segs.back()), get<2>(segs.back()));

        stack<int> stk;
        stk.emplace((int) segs.size() - 1);

        for (int i = (int) segs.size() - 2; i >= 0; i--) {
            const auto &[y, sx, ex] = segs[i];

            while (!stk.empty() && get<0>(segs[stk.top()]) >= y) stk.pop();
            const auto &pi = stk.top();
            const auto &[py, psx, pex] = segs[pi];

            get<2>(rngs[i]) = psx;
            stk.emplace(i);
        }

        segs.pop_back();
    }

    sort(iterall(rngs), [](const tli &l, const tli &r) {
        const auto &[ly, lsx, lex] = l;
        const auto &[ry, rsx, rex] = r;

        return lsx != rsx ? lsx < rsx : lex > rex;
    });
    rngs.erase(unique(iterall(rngs)), rngs.end());


    int H = rngs.size();
    auto tr = Tree(H);

    {
        stack<int> stk;

        for (int i = 0; i < H; i++) {
            const auto &[y, sx, ex] = rngs[i];

            if (stk.empty()) {
                tr.advance_vl(i, (ex - sx) * y);
                stk.emplace(i);

                continue;
            }

            while (!stk.empty()) {
                const auto &[ty, tsx, tex] = rngs[stk.top()];

                if (tsx <= sx && ex <= tex) break;
                else stk.pop();
            }
            const auto &[ty, tsx, tex] = rngs[stk.top()];

            tr.advance_vl(i, (ex - sx) * (y - ty));
            tr.emplace_edge(stk.top(), i);
            stk.emplace(i);
        }
    }

    tr.compress(0, false);
    tr.numbering(0);

    tr.seg_init();

    i64 ans = 0;
    for (int i = 0; i < K; i++) {
        if (auto x = tr.query(); x > 0) {
            ans += x;
        } else {
            break;
        }
    }

    cout << ans << endl;
    return 0;
}
