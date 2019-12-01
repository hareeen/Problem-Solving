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

  vector<vector<bool>> isPalin(N, vector<bool>(N));
  for (int i = 0; i < N; i++) isPalin[i][i] = true;
  for (int i = 0; i + 1 < N; i++) isPalin[i][i + 1] = (s[i] == s[i + 1]);

  for (int j = 2; j < N; j++)
    for (int i = 0; i + j < N; i++)
      if (isPalin[i + 1][i + j - 1] && s[i] == s[i + j])
        isPalin[i][i + j] = true;

  vector<int> dp(N, numeric_limits<int>::max() / 3);
  dp[0] = 1;

  for (int i = 1; i < N; i++) {
    if (isPalin[0][i]) {
      dp[i] = 1;
      continue;
    }
    dp[i] = dp[i - 1] + 1;
    for (int j = 0; j < i; j++)
      if (isPalin[j + 1][i]) dp[i] = min(dp[i], dp[j] + 1);
  }

  cout << dp.back() << endl;

  return 0;
}