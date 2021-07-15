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

void dfs1(int h, vector<bool> &vst, stack<int> &trc, const vector<vector<int>> &G) {
    for (auto t : G[h]) {
        if (!vst[t]) vst[t] = true, dfs1(t, vst, trc, G);
    }

    trc.push(h);
}

void dfs2(int h, vector<bool> &vst, vector<int> &grp, const vector<vector<int>> &G) {
    for (auto t : G[h]) {
        if (!vst[t]) vst[t] = true, dfs2(t, vst, grp, G);
    }

    grp.emplace_back(h);
}

bool SCC(vector<vector<int>> &graph1) {
    const int V = graph1.size();

    vector<bool> vst(V);
    stack<int> trc;

    for (int i = 0; i < V; i++) {
        if (!vst[i]) vst[i] = true, dfs1(i, vst, trc, graph1);
    }

    vector<vector<int>> graph2(V);
    for (int h = 0; h < V; h++) {
        for (auto t : graph1[h]) graph2[t].emplace_back(h);
        graph1[h].clear();
    }

    for (auto &vec : graph2) vec.shrink_to_fit();

    vector<int> sccn(V);
    vst.clear(), vst.resize(V);
    while (!trc.empty()) {
        if (!vst[trc.top()]) {
            vector<int> grp;
            vst[trc.top()] = true;
            dfs2(trc.top(), vst, grp, graph2);
            for (auto el : grp) sccn[el] = trc.size();
        }
        trc.pop();
    }

    for (int i = 0; i < V / 2; i++) {
        if (sccn[i] == sccn[i + V / 2]) return false;
    }

    return true;
}

void process() {
    int N, M;
    cin >> N >> M;

    vector<string> mp(N);
    for (auto &str : mp) cin >> str;

    {
        int wn = 0, bn = 0;
        for (const auto &str : mp) {
            wn += count(iterall(str), 'W');
            bn += count(iterall(str), 'B');
        }

        if (wn != bn * 2) {
            cout << "NO" << endl;
            return;
        }
    }

    if (N == 1 || M == 1) {
        cout << "NO" << endl;
        return;
    }

    const int nt = N * (M - 1) + M * (N - 1);

    vector<vector<int>> graph1(2 * nt);

    auto sat_append = [&](int u, int v, bool inv = true) {
        graph1[u].emplace_back(v);
        if (inv) graph1[(nt + v) % (2 * nt)].emplace_back((nt + u) % (2 * nt));
    };

    {
        int n = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M - 1; j++, n++) {
                if (mp[i][j] == '.' || mp[i][j + 1] == '.' || mp[i][j] == mp[i][j + 1]) {
                    sat_append(n, nt + n, false);
                }
            }
        }
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < M; j++, n++) {
                if (mp[i][j] == '.' || mp[i + 1][j] == '.' || mp[i][j] == mp[i + 1][j]) {
                    sat_append(n, nt + n, false);
                }
            }
        }
    }

    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int t = N * (M - 1) + M * (i - 1) + j;
                int b = N * (M - 1) + M * i + j;
                int l = (M - 1) * i + j - 1;
                int r = (M - 1) * i + j;

                if (mp[i][j] == 'B') {
                    if (i == 0) sat_append(nt + b, b, false);
                    if (i == N - 1) sat_append(nt + t, t, false);
                    if (j == 0) sat_append(nt + r, r, false);
                    if (j == M - 1) sat_append(nt + l, l, false);

                    if (i > 0 && i < N - 1) {
                        sat_append(t, nt + b);
                        sat_append(nt + b, t);
                    }
                    if (j > 0 && j < M - 1) {
                        sat_append(l, nt + r);
                        sat_append(nt + r, l);
                    }
                }

                if (mp[i][j] == 'W') {
                    vector<int> validNodes;

                    if (i != 0) validNodes.emplace_back(t);
                    if (i != N - 1) validNodes.emplace_back(b);
                    if (j != 0) validNodes.emplace_back(l);
                    if (j != M - 1) validNodes.emplace_back(r);

                    const int V = validNodes.size();
                    for (int u = 0; u < V; u++) {
                        for (int v = u + 1; v < V; v++) {
                            sat_append(validNodes[u], nt + validNodes[v]);
                        }
                    }
                }
            }
        }
    }

    mp.clear();
    for (auto &vec : graph1) vec.shrink_to_fit();

    cout << (SCC(graph1) ? "YES" : "NO") << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;

    while (T--) process();

    return 0;
}
