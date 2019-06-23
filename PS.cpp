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

  int N;
  cin >> N;
  vector<vector<pi>> sche(N + 1);
  for (int i = 0; i < N; i++)
  {
    int Ti, Pi;
    cin >> Ti >> Pi;
    if (Ti + i <= N)
      sche[Ti + i].push_back(pi(i, Pi));
  }
  vector<int> dp;
  dp.push_back(0);
  for (int i = 1; i <= N; i++)
  {
    int _m = dp.back();
    for (auto el : sche[i])
      _m = max(el.second + dp[el.first], _m);
    dp.push_back(_m);
  }
  cout << dp.back() << endl;
  return 0;
}
