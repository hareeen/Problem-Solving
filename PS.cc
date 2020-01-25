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

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

<<<<<<< HEAD
const i64 inf = numeric_limits<i64>::max() / 3;

class Line {
   public:
    i64 a, b;

    Line() { a = 1, b = -inf; }

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
};

namespace LiChao {
Node* init(i64 s, i64 e) { return new Node(s, e); }

void update(Node* hr, const Line l) {
    i64 s = hr->s, e = hr->e;
    i64 m = (s + e) / 2;

    auto lo = hr->v, hi = l;
    if (lo.get(s) > hi.get(s)) swap(lo, hi);

    if (lo.get(e) <= hi.get(e)) {
        hr->v = hi;
        return;
    }

    if (lo.get(m) < hi.get(m)) {
        hr->v = hi;
        if (!hr->r) hr->r = new Node(m + 1, e);
        update(hr->r, lo);
    } else {
        hr->v = lo;
        if (!hr->l) hr->l = new Node(s, m);
        update(hr->l, hi);
    }
}

i64 query(Node* hr, const i64 x) {
    if (!hr) return -inf;

    i64 s = hr->s, e = hr->e;
    i64 m = (s + e) / 2;

    return max(hr->v.get(x), x <= m ? query(hr->l, x) : query(hr->r, x));
}
};  // namespace LiChao
=======
#define x first
#define y second

pli operator-(const pli &lhs, const pli &rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

inline i64 ccw(pli p1, pli p2, pli p3) {
    auto[x1, y1] = p2 - p1;
    auto[x2, y2] = p3 - p1;

    return x1 * y2 - x2 * y1;
}

i64 dir(pli p1, pli p2, pli p3) {
    auto c = ccw(p1, p2, p3);

    if (c > 0)
        return 1;
    else if (c == 0)
        return 0;
    else
        return -1;
}

i64 isIntersect(pli p1, pli p2, pli q1, pli q2) {
    return dir(p1, p2, q1) * dir(p1, p2, q2) < 0 &&
           dir(q1, q2, p1) * dir(q1, q2, p2) < 0;
}

void dfs1(int here, vector<bool> &vst, stack<int> &trace,
          const vector<vector<int>> &graph) {
    for (auto there : graph[here]) {
        if (!vst[there]) vst[there] = true, dfs1(there, vst, trace, graph);
    }

    trace.push(here);
}

void dfs2(int here, vector<bool> &vst, vector<int> &group,
          const vector<vector<int>> &graph) {
    for (auto there : graph[here]) {
        if (!vst[there]) vst[there] = true, dfs2(there, vst, group, graph);
    }

    group.push_back(here);
}

vector<vector<int>> SCC(const vector<vector<int>> &graph1,
                        const vector<vector<int>> &graph2) {
    const int V = graph1.size();

    vector<bool> vst(V);
    stack<int> trace;
    for (int i = 0; i < V; i++)
        if (!vst[i]) {
            vst[i] = true, dfs1(i, vst, trace, graph1);
        }

    vector<vector<int>> ret;
    vst.clear(), vst.resize(V);
    while (!trace.empty()) {
        if (!vst[trace.top()]) {
            vector<int> group;
            vst[trace.top()] = true;
            dfs2(trace.top(), vst, group, graph2);
            sort(iterall(group));
            ret.push_back(group);
        }
        trace.pop();
    }

    return ret;
};
>>>>>>> 2942a67c145d1230c901d1e8b281a0d9f5675738

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

<<<<<<< HEAD
    vector<i64> v(N);
    for (int i = 0; i < N; i++) cin >> v[i];

    i64 _su = 0;
    i64 _ssu = 0;
    auto root = LiChao::init(-2e12, 2e12);

    vector<i64> d(N);
    for (int i = 0; i < N; i++) {
        LiChao::update(root, Line(-i, i * _su - _ssu));
        _su += v[i];
        _ssu += (i + 1) * v[i];
        d[i] = max(d[i], LiChao::query(root, _su) + _ssu);
=======
    vector<pair<pli, pli>> segs(3 * N);
    for (int i = 0; i < 3 * N; i++)
        cin >> segs[i].first.x >> segs[i].first.y >> segs[i].second.x >>
            segs[i].second.y;

    vector<vector<int>> graph1(6 * N), graph2(6 * N);
    const int _not = 3 * N;

    auto tsat_append = [&graph1, &graph2, _not](int u, int v, bool dau = true) {
        graph1[u].push_back(v);
        if (dau)
            graph1[(_not + v) % (2 * _not)].push_back((_not + u) % (2 * _not));

        graph2[v].push_back(u);
        if (dau)
            graph2[(_not + u) % (2 * _not)].push_back((_not + v) % (2 * _not));
    };

    for (int i = 0; i < N; i++) {
        tsat_append(_not + 3 * i, 3 * i + 1);
        tsat_append(_not + 3 * i + 1, 3 * i + 2);
        tsat_append(_not + 3 * i + 2, 3 * i);
    }

    for (int i = 0; i < 3 * N; i++) {
        for (int j = i + 1; j < 3 * N; j++) {
            if (isIntersect(segs[i].first, segs[i].second,
                            segs[j].first, segs[j].second))
                tsat_append(i, _not + j);
        }
    }

    auto scc = SCC(graph1, graph2);
    const int S = scc.size();

    vector<int> con(2 * _not);
    for (int i = 0; i < S; i++) {
        for (auto v : scc[i]) con[v] = i;
    }

    for (int i = 0; i < _not; i++) {
        if (con[i] == con[i + _not]) {
            cout << -1 << endl;
            return 0;
        }
    }

    vector<vector<bool>> graph(S, vector<bool>(S));
    for (int u = 0; u < 2 * _not; u++) {
        for (auto v : graph1[u]) graph[con[u]][con[v]] = true;
    }

    for (int i = 0; i < S; i++) graph[i][i] = false;

    vector<int> indeg(S);
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (graph[i][j]) indeg[j]++;
        }
    }

    vector<bool> vst(S), assigned(2 * _not), ans(2 * _not);

    queue<int> que;
    for (int i = 0; i < S; i++) {
        if (indeg[i] == 0) {
            que.push(i);
            vst[i] = true;
        }
    }

    while (!que.empty()) {
        auto cur = que.front();
        que.pop();

        for (auto v:scc[cur]) {
            if (!assigned[v]) {
                assigned[v] = true;
                assigned[(_not + v) % (2 * _not)] = true;

                ans[v] = false;
                ans[(_not + v) % (2 * _not)] = true;
            }
        }

        for (int i = 0; i < S; i++) {
            if (!graph[cur][i]) continue;
            if (--indeg[i] == 0 && !vst[i]) {
                que.push(i);
                vst[i] = true;
            }
        }
    }

    vector<int> res;
    for (int i = _not; i < 2 * _not; i++)
        if (ans[i]) res.push_back(i - _not + 1);

    cout << res.size() << endl;
    if (res.size()) {
        copy(iterall(res), ostream_iterator<int>(cout, " "));
        cout << endl;
>>>>>>> 2942a67c145d1230c901d1e8b281a0d9f5675738
    }

    cout << *max_element(iterall(d)) << endl;
    return 0;
}