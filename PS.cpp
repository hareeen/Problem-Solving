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

  int n, k;
  cin >> n >> k;
  list<int> linkedList;
  vector<int> output;
  for (int i = 1; i <= n; i++)
    linkedList.push_back(i);
  auto it = linkedList.begin();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < k - 1; j++)
    {
      if (it == linkedList.end())
        it = linkedList.begin();
      it++;
    }
    if (it == linkedList.end())
      it = linkedList.begin();
    output.push_back(*it);
    if (i == n - 1)
      break;
    it = linkedList.erase(it);
  }
  cout << '<';
  for (const auto &el : output)
  {
    cout << el;
    if (el != output.back())
      cout << ", ";
  }
  cout << '>' << endl;
  return 0;
}
