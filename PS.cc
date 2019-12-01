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

const int M = 4;
const int bitNum = static_cast<int>(pow(2, M + 1));

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N = 1000;
  vector<vector<int>> dp(M * N + 1, vector<int>(bitNum));
  dp[0][0] = 1;

  for (int i = 0; i < M * N; i++) {
    for (int j = 0; j < bitNum; j++) {
      if (i % M != M - 1 && !(j & 3)) dp[i][j + 3] += dp[i][j];
      if (!(j & (bitNum / 2 + 1))) dp[i][j + (bitNum / 2 + 1)] += dp[i][j];
    }
    for (int j = 1; j < bitNum; j += 2) dp[i + 1][j / 2] += dp[i][j];
  }

  int Q;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int x;
    cin >> x;
    cout << dp[x * M][0] << '\n';
  }

  return 0;
}