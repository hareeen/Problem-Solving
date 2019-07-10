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

  int N, K;
  cin >> N >> K;
  vector<int> arr;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    arr.push_back(t);
  }

  vector<int> dp(K + 1, INT_MAX / 2);
  dp[0] = 0;
  for (int i = 0; i < K; i++)
    for (int j = 0; j < N; j++)
      for (int k = i + arr[j]; k <= K; k += arr[j])
        dp[k] = min(dp[k], dp[i] + (k - i) / arr[j]);

  if (dp.back() >= INT_MAX / 2)
    cout << -1 << endl;
  else
    cout << dp.back() << endl;

  return 0;
}