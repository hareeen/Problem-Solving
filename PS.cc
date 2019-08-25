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

  vector<int> arr(1);
  while (true) {
    int t;
    cin >> t;
    if (!t) break;
    arr.push_back(t);
  }

  vector<vector<vector<int>>> dp(
      arr.size() + 1,
      vector<vector<int>>(5, vector<int>(5, numeric_limits<int>::max() / 2)));

  dp[0][0][0] = 0;

  int table[5][5] = {{1, 2, 2, 2, 2},
                     {2, 1, 3, 4, 3},
                     {2, 3, 1, 3, 4},
                     {2, 4, 3, 1, 3},
                     {2, 3, 4, 3, 1}};

  for (int i = 1; i < arr.size(); i++) {
    auto cur = arr[i];
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        if (j == cur && k == cur) continue;
        if (j != cur && k != cur) continue;
        if (k == cur) {
          for (int l = 0; l < 5; l++) {
            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][l] + table[l][k]);
          }
        }
        if (j == cur) {
          for (int l = 0; l < 5; l++) {
            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][l][k] + table[l][j]);
          }
        }
        // cout<<i<<" "<<j<<" "<<k<<" "<<dp[i][j][k]<<endl;
      }
    }
  }

  int ans = numeric_limits<int>::max();
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) ans = min(ans, dp[arr.size()-1][i][j]);

  cout << ans << endl;
  return 0;
}