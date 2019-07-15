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

  int N, M, R;
  cin >> N >> M >> R;

  vector<int> item;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    item.push_back(t);
  }

  vector<vector<int>> floyd(N, vector<int>(N, INT_MAX / 2));
  for (int i = 0; i < N; i++)
    floyd[i][i] = 0;

  for (int i = 0; i < R; i++)
  {
    int a, b, l;
    cin >> a >> b >> l;
    a--;
    b--;
    floyd[a][b] = l;
    floyd[b][a] = l;
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        floyd[k][j] = min(floyd[k][j], floyd[k][i] + floyd[i][j]);
        
  int ans = 0;
  for (int i = 0; i < N; i++)
  {
    int cp = 0;
    for (int j = 0; j < N; j++)
      if (floyd[i][j] <= M)
        cp += item[j];
    ans = max(cp, ans);
  }
  cout << ans << endl;

  return 0;
}