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

int bit[17] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
int solve(const int &N, vector<vector<int>> &inc, vector<vector<int>> &dp, int length, int stateBit, int node)
{
  if (length == N - 1)
    return inc[node][0] == 0 ? INT_MAX / 2 : inc[node][0];
  if (dp[stateBit][node] != -1)
    return dp[stateBit][node];

  int ret = INT_MAX / 2;
  for (int i = 0; i < N; i++)
    if ((stateBit & bit[i]) == 0 && inc[node][i] != 0)
      ret = min(ret, solve(N, inc, dp, length + 1, stateBit + bit[node], i) + inc[node][i]);

  if (ret >= INT_MAX / 2)
    return INT_MAX / 2;

  // cout<<stateBit<<" "<<node<<" "<<ret<<endl;
  return dp[stateBit][node] = ret;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<vector<int>> incMat(N, vector<int>(N));
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      incMat[i][j] = t;
    }
  }

  vector<vector<int>> dp(bit[N], vector<int>(N, -1));
  cout << solve(N, incMat, dp, 0, 0, 0) << endl;

  return 0;
}