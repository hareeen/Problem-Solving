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

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

const int sz = 2000000;
vector<int> graph1[2000000], graph2[2000000];

void dfs1(int here, vector<bool> &vst, stack<int> &trace) {
    for (auto there : graph1[here]) {
        if (!vst[there]) vst[there] = true, dfs1(there, vst, trace);
    }

    trace.push(here);
}

void dfs2(int here, vector<bool> &vst, vector<int> &group) {
    for (auto there : graph2[here]) {
        if (!vst[there]) vst[there] = true, dfs2(there, vst, group);
    }

    group.push_back(here);
}

bool SCC(const int V) {
    vector<bool> vst(V);
    stack<int> trace;
    for (int i = 0; i < V; i++) {
        if (!vst[i]) vst[i] = true, dfs1(i, vst, trace);
    }

    for (int i = 0; i < V; i++) {
        for (auto el : graph1[i]) graph2[el].emplace_back(i);
        graph1[i].clear();
    }

    vector<int> sccn(V);
    vst.clear(), vst.resize(V);
    while (!trace.empty()) {
        if (!vst[trace.top()]) {
            vector<int> group;
            vst[trace.top()] = true;
            dfs2(trace.top(), vst, group);
            for (auto el : group) sccn[el] = trace.size();
        }
        trace.pop();
    }

    for (int i = 0; i < V / 2; i++)
        if (sccn[i] == sccn[i + V / 2]) return false;
    return true;
};

void process() {
    int N, M;
    cin >> N >> M;

    vector<string> vec(N);
    int bn = 0, wn = 0;
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
        for (auto el : vec[i]) {
            if (el == 'B') bn++;
            if (el == 'W') wn++;
        }
    }

    if (wn != bn * 2) {
        cout << "NO" << endl;
        return;
    }

    const int nt = 4 * N * M;
    fill(graph2, graph2 + sz, vector<int>());
    auto sat_append = [&](int u, int v, bool b = true) {
        graph1[u].emplace_back(v);
        if (b) graph1[(nt + v) % (2 * nt)].emplace_back((nt + u) % (2 * nt));
    };

    const int t = 0, l = 1, r = 2, b = 3;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            auto ch = (i * M + j) * 4;
            if (i != 0) {
                sat_append(ch + t, ch - M * 4 + b);
                sat_append(ch - M * 4 + b, ch + t);
            }
            if (j != 0) {
                sat_append(ch + l, ch - 4 + r);
                sat_append(ch - 4 + r, ch + l);
            }
            if (j != M - 1) {
                sat_append(ch + r, ch + 4 + l);
                sat_append(ch + 4 + l, ch + r);
            }
            if (i != N - 1) {
                sat_append(ch + b, ch + M * 4 + t);
                sat_append(ch + M * 4 + t, ch + b);
            }

            if (vec[i][j] == '.') {
                if (i != 0) sat_append(ch + t, nt + ch + t, false);
                if (j != 0) sat_append(ch + l, nt + ch + l, false);
                if (j != M - 1) sat_append(ch + r, nt + ch + r, false);
                if (i != N - 1) sat_append(ch + b, nt + ch + b, false);
                continue;
            }

            auto tc = i != 0 ? vec[i - 1][j] : '.';
            auto lc = j != 0 ? vec[i][j - 1] : '.';
            auto rc = j != M - 1 ? vec[i][j + 1] : '.';
            auto bc = i != N - 1 ? vec[i + 1][j] : '.';

            if (vec[i][j] == 'B') {
                if (tc != 'W') sat_append(ch + t, nt + ch + t, false);
                if (lc != 'W') sat_append(ch + l, nt + ch + l, false);
                if (rc != 'W') sat_append(ch + r, nt + ch + r, false);
                if (bc != 'W') sat_append(ch + b, nt + ch + b, false);
                sat_append(ch + t, nt + ch + b);
                sat_append(ch + l, nt + ch + r);
                sat_append(nt + ch + r, ch + l);
                sat_append(nt + ch + b, ch + t);
            }
            if (vec[i][j] == 'W') {
                if (tc != 'B') sat_append(ch + t, nt + ch + t, false);
                if (lc != 'B') sat_append(ch + l, nt + ch + l, false);
                if (rc != 'B') sat_append(ch + r, nt + ch + r, false);
                if (bc != 'B') sat_append(ch + b, nt + ch + b, false);
                sat_append(ch + t, nt + ch + l);
                sat_append(ch + t, nt + ch + r);
                sat_append(ch + t, nt + ch + b);
                sat_append(ch + l, nt + ch + r);
                sat_append(ch + l, nt + ch + b);
                sat_append(ch + r, nt + ch + b);
            }
        }
    }
    vec.clear();

    cout << (SCC(2 * nt) ? "YES" : "NO") << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    for (int i = 0; i < T; i++) process();
}