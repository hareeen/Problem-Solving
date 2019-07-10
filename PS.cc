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

  int N;
  cin >> N;
  vector<int> arr;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    arr.push_back(t);
  }

  vector<int> dp(N, INT_MAX / 2);
  dp[0] = 0;
  for (int i = 0; i < N; i++)
    for (int j = i + 1; j <= min(N - 1, i + arr[i]); j++)
      dp[j] = min(dp[j], dp[i] + 1);
  if (dp.back() >= INT_MAX / 2)
    cout << -1 << endl;
  else
    cout << dp.back() << endl;
  return 0;
}