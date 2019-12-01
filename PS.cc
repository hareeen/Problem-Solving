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

const int inf = numeric_limits<int>::max() / 3;

void solve(int s, int l, const vector<vector<pi>> &par, vector<pi> &trace) {
  if (l == 2) {
    trace.push_back({s + 1, s + l});
    return;
  } else if (par[s][l].first) {
    solve(s, par[s][l].second, par, trace);
    solve(s + par[s][l].second, l - par[s][l].second, par, trace);
  } else {
    trace.push_back({s + 1, s + l});
    solve(s + 1, l - 2, par, trace);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  string s;
  cin >> s;

  vector<bool> arr;
  transform(iterall(s), back_inserter(arr),
            [](char c) -> bool { return c - '0'; });

  vector<vector<int>> dp(N + 1, vector<int>(N + 1, inf)),
      hi(N + 1, vector<int>(N + 1, 1));
  vector<vector<pi>> par(N + 1, vector<pi>(N + 1));
  for (int i = 0; i <= N; i++)
    for (int j = 0; j <= N; j++)
      dp[i][j] = inf, hi[i][j] = 1, par[i][j] = {0, 0};

  for (int i = 0; i + 1 < N; i++)
    if (arr[i] ^ arr[i + 1]) dp[i][2] = 3;

  for (int j = 4; j <= N; j += 2) {
    for (int i = 0; i + j - 1 < N; i++) {
      int h = 0;
      if (arr[i] ^ arr[i + j - 1]) {
        dp[i][j] = dp[i + 1][j - 2] + 2 * hi[i + 1][j - 2] + j + 1;
        hi[i][j] = hi[i + 1][j - 2] + 1;
        par[i][j] = {0, 0};
      }
      for (int k = 2; k < j; k += 2)
        if (dp[i][j] > dp[i][k] + dp[i + k][j - k]) {
          dp[i][j] = dp[i][k] + dp[i + k][j - k],
          hi[i][j] = max(hi[i][k], hi[i + k][j - k]);
          par[i][j] = {1, k};
        }

      // cout << i << " " << j << " " << dp[i][j] << endl;
    }
  }

  vector<pi> trace;
  solve(0, N, par, trace);
  sort(iterall(trace));

  cout << dp[0][N] << endl;
  for (auto el : trace) cout << el.first << " " << el.second << '\n';

  return 0;
}