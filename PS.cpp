#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

i64 nCr(i64 n, i64 r, i64 m)
{
  if (n < r)
    return 0;
  vector<vector<i64>> d(n + 1, vector<i64>(r + 1, 1));
  for (i64 i = 1; i <= n; i++)
    for (i64 j = 1; j <= min(n, r); j++)
      d[i][j] = (d[i - 1][j - 1] + (j != i ? d[i - 1][j] : 0)) % m;
  return d[n][r];
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  i64 n, m, r;
  cin >> n >> r >> m;
  i64 ans = 1;
  while (n != 0 || r != 0)
  {
    ans *= nCr(n % m, r % m, m);
    ans %= m;
    n /= m;
    r /= m;
  }
  cout << ans << endl;
  return 0;
}
