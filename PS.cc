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

  int N;
  cin >> N;

  vector<int> arr(N);
  for (int i = 0; i < N; i++) cin >> arr[i];

  vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
  for (int i = 0; i < N; i++)
    if (arr[i] == arr[(i + 1) % N]) dp[i][2] = 1;

  for (int j = 3; j <= N; j++) {
    for (int i = 0; i < N; i++) {
      if (arr[i] == arr[(i + j - 1) % N])
        dp[i][j] = max(dp[i][j], dp[(i + 1) % N][j - 2] + 1);
      for (int k = 1; k < j; k++)
        dp[i][j] = max(dp[i][j], dp[i][k] + dp[(i + k) % N][j - k]);
      // cout << i << " " << j << " " << dp[i][j] << endl;
    }
  }

  int ans = 0;
  for (const auto &vec : dp)
    for (auto el : vec) ans = max(ans, el);

  cout << ans << endl;

  return 0;
}