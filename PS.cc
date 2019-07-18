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
  int N, K;
  cin >> N >> K;

  vector<pi> walk, bike;
  for (int i = 0; i < N; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    walk.push_back(pi(a, b));
    bike.push_back(pi(c, d));
  }

  vector<vector<int>> dp(N + 1, vector<int>(K + 1, INT_MIN / 2));

  dp[0][0] = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j <= K; j++)
    {
      if (j >= walk[i].first)
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - walk[i].first] + walk[i].second);
      if (j >= bike[i].first)
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - bike[i].first] + bike[i].second);
    }
  }

  cout << *max_element(iterall(dp.back())) << endl;

  return 0;
}