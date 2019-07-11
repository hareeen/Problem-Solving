#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define iterall(container) container.begin(), container.end()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T, W;
  cin >> T >> W;

  int cur_t = 0;
  int streak = 0;
  vector<int> arr(1);
  for (int i = 0; i < T; i++)
  {
    int t;
    cin >> t;
    t--;
    if (t == cur_t)
      streak++;
    else
    {
      arr.push_back(streak);
      streak = 1;
      cur_t = t;
    }
  }
  if (streak != 0)
    arr.push_back(streak);

  int dp[1002][31][2] = {0};
  for (int i = 1; i <= arr.size() - 1; i++)
  {
    for (int j = 0; j <= W; j++)
    {
      if (j == 0)
        dp[i][j][0] = dp[i - 1][j][0] + (i % 2 == 1 ? arr[i] : 0);
      else
      {
        if (j % 2 == 0)
          dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j - 1][1]) + (i % 2 == 1 ? arr[i] : 0);
        else
          dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0]) + (i % 2 == 0 ? arr[i] : 0);
      }
      // cout << i << " " << j << " " << dp[i][j][0] << " " << dp[i][j][1] << endl;
    }
  }

  int res = INT_MIN;
  for (int i = 0; i <= W; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      res = max(res, dp[arr.size() - 1][i][j]);
    }
  }
  cout << res << endl;

  return 0;
}