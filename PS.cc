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

class group {
   public:
    priority_queue<i64> pq;
    i64 lim, su;

    group(i64 _lim) {
        lim = _lim;
        su = 0;
    }

    void validate() {
        while (!pq.empty() && su > lim) {
            su -= pq.top();
            pq.pop();
        }
    }

    void add(i64 x) {
        pq.emplace(x);
        su += x;
        validate();
    }

    i64 get() { return pq.size(); }

    void merge(group* rhs) {
        while (!rhs->pq.empty()) {
            pq.emplace(rhs->pq.top());
            rhs->pq.pop();
        }
        su += rhs->su;

        validate();
        delete rhs;
    }
};

vector<int> sz;
vector<i64> cost, ld;
vector<vector<int>> tr;

void alignTree(int h) {
    sz[h] = 1;

    for (auto t : tr[h]) {
        alignTree(t);
        sz[h] += sz[t];
    }

    sort(iterall(tr[h]), [](int l, int r) { return sz[l] > sz[r]; });
}

vector<i64> res;
group* solve(int h, const i64 LIM) {
    if (tr[h].empty()) {
        auto ret = new group(LIM);
        ret->add(cost[h]);
        res[h] = ret->get();
        return ret;
    }

    auto ret = solve(tr[h][0], LIM);
    for (int i = 1; i < tr[h].size(); i++) ret->merge(solve(tr[h][i], LIM));
    ret->add(cost[h]);
    res[h] = ret->get();
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    i64 M;
    cin >> N >> M;

    res.resize(N + 1);
    sz.resize(N + 1);
    tr.resize(N + 1);
    cost.resize(N + 1);
    ld.resize(N + 1);

    int root = -1;
    for (int i = 1; i <= N; i++) {
        i64 p, c, l;
        cin >> p >> c >> l;

        if (p == 0) root = i;
        tr[p].emplace_back(i);
        cost[i] = c;
        ld[i] = l;
    }

    alignTree(root);
    solve(root, M);

    i64 ans = numeric_limits<i64>::min();
    for (int i = 1; i <= N; i++) ans = max(ans, res[i] * ld[i]);
    cout << ans << endl;

    return 0;
}