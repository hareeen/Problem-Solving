#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

using namespace std;
using namespace __gnu_pbds;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

class disjointSet {
private:
    vector<int> p;
public:
    explicit disjointSet(int N) {
        p.clear();
        p.resize(N + 1);
        for (int i = 1; i <= N; i++) p[i] = i;
    }

    virtual void reset() {
        for (int i = 0; i < p.size(); i++) p[i] = i;
    }

    virtual int find(int u) {
        return p[u] = (p[u] == u ? u : find(p[u]));
    }

    virtual void merge(int u, int v) {
        p[find(v)] = p[find(u)];
    }

    virtual bool sset(int u, int v) {
        return find(u) == find(v);
    }
};

class disjointSet2d : disjointSet {
private:
    int N, M;
public:
    disjointSet2d(int _N, int _M) : disjointSet(4 * _N * _M) {
        N = _N, M = _M;
    }

    int get(int x, int y) {
        return (x * 2 * M + y) * 2;
    }

    void reset() final {
        disjointSet::reset();
    }

    int find(int x, int y) {
        return disjointSet::find(get(x, y));
    }

    void merge(int x, int y) final {
        auto h = get(x, y);
        if (x) disjointSet::merge(h, h - 2 * M);
        if (y) disjointSet::merge(h, h - 1);
        disjointSet::merge(h, h + 2 * M);
        disjointSet::merge(h, h + 1);
    }

    bool sset(int x1, int y1, int x2, int y2) {
        return disjointSet::sset(get(x1, y1), get(x2, y2));
    }
};

using qi = tuple<int, int, int, int>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    vector<int> zip;
    vector<vector<int>> hei(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> hei[i][j];
            zip.emplace_back(hei[i][j]);
        }
    }

    sort(iterall(zip));
    zip.erase(unique(iterall(zip)), zip.end());
    const int Z = zip.size();

    for (auto &v: hei)
        for (auto &el: v)
            el = distance(zip.begin(), lower_bound(iterall(zip), el));

    vector<ti> updque;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            updque.emplace_back(hei[i][j], i, j);
    sort(iterall(updque));

    vector<qi> queries;
    for (int i = 0; i < Q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        --x1, --y1, --x2, --y2;
        queries.emplace_back(x1, y1, x2, y2);
    }

    auto dS = disjointSet2d(N, M);
    vector<int> st(Q, 0), ed(Q, Z - 1);

    for (int i = 0; i < Q; i++) {
        auto[x1, y1, x2, y2] = queries[i];
        if (x1 == x2 && y1 == y2) st[i] = ed[i] = hei[x1][y1];
    }

    while (true) {
        vector<vector<int>> pbs(Z);
        bool loopEnd = true;
        auto qptr = updque.begin();

        dS.reset();

        for (int i = 0; i < Q; i++) {
            if (st[i] != ed[i]) {
                loopEnd = false;
                pbs[(st[i] + ed[i]) / 2].emplace_back(i);
            }
        }

        if (loopEnd) break;

        for (int i = 0; i < Z; i++) {
            while (qptr != updque.end()) {
                auto[h, x, y] = *qptr;
                if (h != i) break;

                dS.merge(x, y);
                ++qptr;
            }

            for (auto j: pbs[i]) {
                auto[x1, y1, x2, y2] = queries[j];
                if (dS.sset(x1, y1, x2, y2)) ed[j] = i;
                else st[j] = i + 1;
            }
        }
    }

    for (auto el: st) cout << zip[el] << '\n';
    return 0;
}