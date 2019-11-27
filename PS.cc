#include <bits/stdc++.h>

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

  int N, Q;
  cin >> N >> Q;

  vector<int> arr(N + 1);
  for (int i = 1; i <= N; i++) cin >> arr[i];
  for (int i = 1; i <= N; i++) arr[i] += arr[i - 1];

  for (int i = 0; i < Q; i++) {
    int s, e;
    cin >> s >> e;
    cout << arr[e] - arr[s - 1] << '\n';
  }

  return 0;
}