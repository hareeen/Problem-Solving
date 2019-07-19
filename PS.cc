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

i64 moveDist(vector<i64> &pole, i64 spacing)
{
  i64 ret = 0;
  for (i64 i = 0; i < pole.size(); i++)
    ret += abs(pole[i] - (pole[0] + i * spacing));
  return ret;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<i64> pole;
  for (int i = 0; i < N; i++)
  {
    i64 t;
    cin >> t;
    pole.push_back(t);
  }

  i64 lo = 0, hi = 1000000000;
  while (hi - lo > 3)
  {
    i64 midLo = (lo * 2 + hi) / 3, midHi = (lo + 2 * hi) / 3;
    i64 distLo = moveDist(pole, midLo), distHi = moveDist(pole, midHi);
    if (distLo > distHi)
      lo = midLo + 1;
    else
      hi = midHi - 1;
  }

  i64 ans = INT64_MAX;
  for (i64 i = lo; i <= hi; i++)
    ans = min(ans, moveDist(pole, i));

  cout << ans << endl;

  return 0;
}