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

    int N, M;
    cin>>N>>M;

    vector<int> arr(N);
    for(int i=0;i<N;i++) cin>>arr[i];
    
    int mx=0;
    for(int i=0;i<N;i++) for(int j=i+1;j<N;j++) for(int k=j+1;k<N;k++) if(arr[i]+arr[j]+arr[k]<=M) mx=max(mx,arr[i]+arr[j]+arr[k]);
    
    cout<<mx<<endl;
    return 0;
}