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
    cin>>N;

    vector<int> v(N);
    for(int i=0;i<N;i++) cin>>v[i];
    sort(iterall(v));

    int M;
    cin>>M;
    
    for(int i=0;i<M;i++) {
        int k;
        cin>>k;
        cout<<upper_bound(iterall(v), k)-lower_bound(iterall(v), k)<<" ";
    }
    cout<<endl;

    return 0;
}