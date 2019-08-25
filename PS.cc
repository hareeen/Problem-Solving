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
using i128 = __int128;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, M;
  cin >> N >> M;

  int dp[1002][1002][2];

  for (int i = 0; i <= N + 1; i++) {
    for (int j = 0; j <= M + 1; j++) {
      dp[i][j][0] = dp[i][j][1] = numeric_limits<int>::min() / 2;
    }
  }
  dp[1][0][0] = 0;

  for (int i = 1; i <= N; i++) {
    vector<int> arr(1);
    for (int j = 1; j <= M; j++) {
      int t;
      cin >> t;
      arr.push_back(t);
    }

    if (i == 1) {
      for (int j = 1; j <= M; j++) {
        dp[i][j][0] = dp[i][j - 1][0] + arr[j];
      }
      for (int j = M; j >= 1; j--) {
        dp[i][j][1] = numeric_limits<int>::min() / 2;
      }
    } else {
      for (int j = 1; j <= M; j++) {
        dp[i][j][0] =
            max({dp[i][j - 1][0], dp[i - 1][j][0], dp[i - 1][j][1]}) + arr[j];
      }
      for (int j = M; j >= 1; j--) {
        dp[i][j][1] =
            max({dp[i][j + 1][1], dp[i - 1][j][0], dp[i - 1][j][1]}) + arr[j];
      }
    }
  }

  cout << max(dp[N][M][0], dp[N][M][1]) << endl;
  return 0;
}