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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<i64> arr(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    vector<pair<pi, int>> queries(K);
    vector<i64> answers(K);
    for (int i = 0; i < K; i++) {
        cin >> queries[i].first.first >> queries[i].first.second;
        queries[i].first.first--;
        queries[i].first.second--;
        queries[i].second = i;
    }

    int sq = (int)sqrt(N);
    sort(iterall(queries), [sq](const pair<pi, int>& lhs, const pair<pi, int>& rhs) {
        const auto& l = lhs.first;
        const auto& r = rhs.first;

        if (l.first / sq < r.first / sq) return true;
        if (l.first / sq == r.first / sq && l.second < r.second) return true;
        return false;
    });

    vector<i64> zip = arr;
    sort(iterall(zip));
    zip.erase(unique(iterall(zip)), zip.end());

    for (auto& el : arr) el = lower_bound(iterall(zip), el) - zip.begin();

    int Z = zip.size();
    i64 ans = 0;
    vector<i64> counts(Z);

    auto append_element = [&](int idx) {
        counts[arr[idx]]++;
        ans += (counts[arr[idx]] * 2 - 1) * zip[arr[idx]];
    };

    auto delete_element = [&](int idx) {
        ans -= (counts[arr[idx]] * 2 - 1) * zip[arr[idx]];
        counts[arr[idx]]--;
    };

    int sl, sr;
    {
        const auto& [l, r] = queries[0].first;
        const auto& idx = queries[0].second;

        for (int i = l; i <= r; i++) {
            append_element(i);
        }

        answers[idx] = ans;
        tie(sl, sr) = tie(l, r);
    }

    for (int i = 1; i < K; i++) {
        const auto& [l, r] = queries[i].first;
        const auto& idx = queries[i].second;

        while (sl > l) --sl, append_element(sl);
        while (sr < r) ++sr, append_element(sr);

        while (sl < l) delete_element(sl), ++sl;
        while (sr > r) delete_element(sr), --sr;

        answers[idx] = ans;
        tie(sl, sr) = tie(l, r);
    }

    copy(iterall(answers), ostream_iterator<i64>(cout, "\n"));
    return 0;
}
