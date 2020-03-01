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

template <class T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

vector<pli> adj[300001], tr[300001];
int sz[300001];

class slope {
   public:
    priority_queue<i64> bp;
    i64 sac, fz;

    slope() {
        sac = 0;
        fz = 0;
    }

    void push(i64 x) {
        fz += x;

        if (bp.empty()) {
            bp.push(x);
            bp.push(x);
            ++sac;
            return;
        }

        while (bp.size() > sac + 1) bp.pop();
        auto m1 = bp.top();
        bp.pop();
        auto m2 = bp.top();
        bp.pop();

        bp.push(m1 + x);
        bp.push(m2 + x);
    }
};

void mer(slope* s1, slope* s2) {
    s1->fz += s2->fz;
    s1->sac += s2->sac;
    while (!s2->bp.empty()) s1->bp.push(s2->bp.top()), s2->bp.pop();
    delete s2;
}

void dfs(int h, int p = -1) {
    sz[h] = 1;
    for (auto [t, _] : adj[h]) {
        if (t == p) continue;
        dfs(t, h);
        sz[h] += sz[t];
        tr[h].emplace_back(t, _);
    }

    sort(iterall(tr[h]), [](const pli& lhs, const pli& rhs) {
        return sz[lhs.first] > sz[rhs.first];
    });
}

slope* solve(int h) {
    slope* ret = nullptr;
    for (auto [t, wf] : tr[h]) {
        auto chslp = solve(t);
        chslp->push(wf);
        if (!ret)
            ret = chslp;
        else
            mer(ret, chslp);
    }

    return ret ? ret : new slope();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 2; i <= N + M; i++) {
        i64 j, w;
        cin >> j >> w;

        adj[i].emplace_back(j, w);
        adj[j].emplace_back(i, w);
    }

    dfs(1);
    auto res = *solve(1);
    vector<i64> bp;
    while (!res.bp.empty()) bp.emplace_back(res.bp.top()), res.bp.pop();
    reverse(iterall(bp));

    for (int i = 0; i < res.sac; i++) res.fz -= bp[i];
    cout << res.fz << endl;

    return 0;
}