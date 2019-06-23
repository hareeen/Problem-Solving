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
  vector<vector<bool>> vec(N);
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      vec[i].push_back(static_cast<bool>(t));
    }
  }
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        vec[j][k] = vec[j][k] | (vec[j][i] & vec[i][k]);
  for (const auto &v : vec)
  {
    for (const auto &el : v)
      cout << el << " ";
    cout << '\n';
  }
  return 0;
}
