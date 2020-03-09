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

set<pi> st;
list<pi> ls;
vector<decltype(ls)::iterator> vt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> _arr(N);
    for (int i = 0; i < N; i++) cin >> _arr[i];

    vector<int> arr(N - 1);
    for (int i = 0; i < N - 1; i++) arr[i] = _arr[i + 1] - _arr[i];

    _arr.clear();

    for (int i = 0; i < N - 1; i++) {
        st.emplace(arr[i], i);
        ls.emplace_back(arr[i], i);
        vt.emplace_back(prev(ls.end()));
    }

    arr.clear();

    i64 ans = 0;
    for (int i = 0; i < K; i++) {
        auto be = st.begin();
        ans += be->first;

        if (i == K - 1) break;

        auto it = vt[be->second];
        if (it == ls.begin()) {
            st.erase(st.lower_bound(ls.front()));
            ls.pop_front();
            st.erase(st.lower_bound(ls.front()));
            ls.pop_front();
        } else if (it == prev(ls.end())) {
            st.erase(st.lower_bound(ls.back()));
            ls.pop_back();
            st.erase(st.lower_bound(ls.back()));
            ls.pop_back();
        } else {
            i64 toap = -be->first;
            auto idx = be->second;

            st.erase(st.lower_bound(*it));
            it = ls.erase(it);
            toap += it->first;
            st.erase(st.lower_bound(*it));
            it = prev(ls.erase(it));
            toap += it->first;
            st.erase(st.lower_bound(*it));
            it = ls.erase(it);

            toap = min(toap, static_cast<i64>(numeric_limits<int>::max()));
            ls.insert(it, {toap, idx});
            st.emplace(toap, idx);
            vt[idx] = prev(it);
        }
    }

    cout << ans << endl;
    return 0;
}