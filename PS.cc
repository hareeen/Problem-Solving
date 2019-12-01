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

  string s;
  cin >> s;

  int N = s.size();
  vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

  for (int i = 2; i <= N; i++) {
    for (int j = 0; i + j <= N; j++) {
      if ((s[j] == 'a' && s[i + j - 1] == 't') ||
          (s[j] == 'g' && s[i + j - 1] == 'c'))
        dp[j][i + j] = dp[j + 1][i + j - 1] + 2;
      for (int k = j; k <= i + j; k++)
        dp[j][i + j] = max(dp[j][i + j], dp[j][k] + dp[k][i + j]);
    }
  }

  int ans = 0;
  for (const auto &vec : dp)
    for (auto el : vec) ans = max(ans, el);
  cout << ans << endl;

  return 0;
}