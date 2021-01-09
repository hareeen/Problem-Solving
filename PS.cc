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

int filter(vector<pli>& arr, bool md) {
    sort(iterall(arr));

    vector<pli> res;
    for (const auto& [x, y] : arr) {
        if (md)
            while (!res.empty() && res.back().second <= y) res.pop_back();
        else if (!res.empty() && res.back().second <= y)
            continue;

        res.emplace_back(x, y);
    }

    arr = res;
    return arr.size();
}

inline i64 cost(const pli& mel, const pli& nel) {
    return max(nel.first - mel.first, 0LL) * max(nel.second - mel.second, 0LL);
}

i64 solve(int s, int e, int l, int r,
          const vector<pli>& mrr, const vector<pli>& nrr) {
    if (e - s < 2) {
        i64 ret = 0;
        for (int i = s; i <= e; i++) {
            for (int j = l; j <= r; j++) {
                ret = max(ret, cost(mrr[i], nrr[j]));
            }
        }

        return ret;
    }

    int m = (s + e) >> 1;
    i64 ret = 0;
    int rp = 0;

    for (int i = l; i <= r; i++) {
        auto cst = cost(mrr[m], nrr[i]);
        if (ret < cst) ret = cst, rp = i;
    }

    return max({solve(s, m - 1, l, rp, mrr, nrr),
                solve(m + 1, e, rp, r, mrr, nrr),
                ret});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M, N;
    cin >> M >> N;

    vector<pli> mrr(M), nrr(N);
    for (int i = 0; i < M; i++) cin >> mrr[i].first >> mrr[i].second;
    for (int i = 0; i < N; i++) cin >> nrr[i].first >> nrr[i].second;


    M = filter(mrr, false);
    N = filter(nrr, true);

    // re-filter
    {
        vector<i64> nx(N), ny(N);
        for (int i = 0; i < N; i++) tie(nx[i], ny[i]) = nrr[i];

        reverse(iterall(ny));

        vector<pli> res;
        for (const auto& [x, y] : mrr) {
            int xlo = upper_bound(iterall(nx), x) - nx.begin();
            int ylo = upper_bound(iterall(ny), y) - ny.begin();

            if (xlo + ylo < N) res.emplace_back(x, y);
        }

        mrr = res;
        M = mrr.size();
    }

    cout << solve(0, M - 1, 0, N - 1, mrr, nrr) << endl;

    return 0;
}
