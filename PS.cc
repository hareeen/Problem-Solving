#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstring>

#define iterall(container) container.begin(), container.end()

using namespace std;

using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

void update_ans(const vector<pi> &tagon, vector<vector<int>> &dp, const int N,
                const int W, int &ans, int finPos, int finPhase) {
  for (int i = 2; i <= N; i++) {
    bool fi_pos = tagon[i].first + tagon[i - 1].first <= W;
    bool se_pos = tagon[i].second + tagon[i - 1].second <= W;
    bool cur_pos = tagon[i].first + tagon[i].second <= W;

    if (cur_pos) dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
    if (fi_pos && se_pos) dp[i][0] = min(dp[i][0], dp[i - 2][0] + 2);
    if (fi_pos) dp[i][1] = min(dp[i][1], dp[i - 1][2] + 1);
    if (se_pos) dp[i][2] = min(dp[i][2], dp[i - 1][1] + 1);

    dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
    dp[i][2] = min(dp[i][2], dp[i - 1][0] + 1);
    dp[i][0] = min({dp[i][0], dp[i][1] + 1, dp[i][2] + 1, dp[i - 1][0] + 2});
  }

  ans = min(ans, dp[N - finPos][finPhase]);
  return;
}

void process() {
  int N, W;
  cin >> N >> W;

  vector<pi> tagon(N + 1);
  for (int i = 1; i <= N; i++) cin >> tagon[i].first;
  for (int i = 1; i <= N; i++) cin >> tagon[i].second;

  int ans = numeric_limits<int>::max();
  bool match1 = tagon[1].first + tagon[N].first <= W;
  bool match2 = tagon[1].second + tagon[N].second <= W;

  {
    vector<vector<int>> dp(N + 1, vector<int>(3, 1e9));
    dp[0][0] = 0;
    dp[1][0] = tagon[1].first + tagon[1].second <= W ? 1 : 2;
    dp[1][1] = dp[1][2] = 1;
    update_ans(tagon, dp, N, W, ans, 0, 0);
  }

  if (match1) {
    vector<vector<int>> dp(N + 1, vector<int>(3, 1e9));
    dp[1][0] = 2, dp[1][1] = 1;
    update_ans(tagon, dp, N, W, ans, 0, 2);
  }

  if (match2) {
    vector<vector<int>> dp(N + 1, vector<int>(3, 1e9));
    dp[1][0] = 2, dp[1][2] = 1;
    update_ans(tagon, dp, N, W, ans, 0, 1);
  }

  if (match1 && match2) {
    vector<vector<int>> dp(N + 1, vector<int>(3, 1e9));
    dp[1][0] = 2;
    update_ans(tagon, dp, N, W, ans, 1, 0);
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int T;
  cin >> T;

  for (int tc = 0; tc < T; tc++) process();

  return 0;
}