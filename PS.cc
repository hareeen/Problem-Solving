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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    vector<i64> arr(N), ans(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    priority_queue<i64> pq;
    i64 offset = 0;

    pq.push(arr[0]);
    ans[0] = arr[0];
    for (int i = 1; i < N; i++) {
        offset++;

        i64 pmin = pq.top() + offset;
        if (arr[i] < pmin) {
            pq.pop();
            pq.push(arr[i] - offset);
        }

        pq.push(arr[i] - offset);
        ans[i] = pq.top() + offset;
    }

    for (int i = N - 2; i >= 0; --i)
        if (ans[i] >= ans[i + 1]) ans[i] = ans[i + 1] - 1;
    copy(iterall(ans), ostream_iterator<i64>(cout, "\n"));

    return 0;
}