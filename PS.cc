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

  int N, M;
  cin >> N >> M;

  vector<bool> arr(N + 1, true);
  for (int i = 0; i < M; i++)
  {
    int t;
    cin >> t;
    arr[t] = false;
  }

  vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(N + 1, vector<int>(3, INT_MAX / 2)));
  dp[0][0][0] = 0;
  for (int i = 1; i <= N; i++)
  {
    for (int j = 0; j <= N; j++)
    {
      vector<int> possible0, possible1, possible2;
      possible0.push_back(INT_MAX / 2);
      possible1.push_back(INT_MAX / 2);
      possible2.push_back(INT_MAX / 2);

      if (arr[i])
      {
        if (j <= N - 3)
          possible0.push_back(*min_element(iterall(dp[i - 1][j + 3])));
        possible0.push_back(*min_element(iterall(dp[i - 1][j])) + 10);
      }
      if (!arr[i])
        possible0.push_back(*min_element(iterall(dp[i - 1][j])));
      dp[i][j][0] = *min_element(iterall(possible0));

      if (i >= 3 && j >= 1)
        possible1.push_back(*min_element(iterall(dp[i - 3][j - 1])) + 25);
      if (!arr[i])
        possible1.push_back(*min_element(iterall(dp[i - 1][j])));
      dp[i][j][1] = *min_element(iterall(possible1));

      if (i >= 5 && j >= 2)
        possible2.push_back(*min_element(iterall(dp[i - 5][j - 2])) + 37);
      if (!arr[i])
        possible2.push_back(*min_element(iterall(dp[i - 1][j])));
      dp[i][j][2] = *min_element(iterall(possible2));
    }
  }

  int res = INT_MAX;
  for (int i = 0; i <= N; i++)
    for (int j = 0; j < 3; j++)
      res = min(res, dp.back()[i][j]);
  cout << res * 1000 << endl;

  return 0;
}