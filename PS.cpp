#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define M_iterall(container) container.begin(), container.end()

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

  int N, K;
  cin >> N >> K;
  vector<int> coins;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    coins.push_back(t);
  }
  sort(M_iterall(coins), greater<int>());
  vector<int> dp(K + 1);
  dp[0] = 1;
  for (int i = 0; i < N; i++)
  {
    vector<int> dp_append(K + 1);
    for (int j = 0; j <= K; j++)
    {
      int _s = 0;
      int cur = j - coins[i];
      while (cur >= 0)
      {
        _s += dp[cur];
        cur -= coins[i];
      }
      dp_append[j] = dp[j] + _s;
    }
    dp = dp_append;
  }
  cout << dp[K] << endl;
  return 0;
}
