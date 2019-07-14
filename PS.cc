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

  int N, M;
  cin >> N;
  cin >> M;

  vector<vector<int>> inc(N, vector<int>(N, INT_MAX / 2));
  for (int i = 0; i < N; i++)
    inc[i][i] = 0;

  for (int i = 0; i < M; i++)
  {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    inc[u][v] = -1;
    inc[v][u] = 1;
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        if ((inc[k][i] > 0 && inc[i][j] > 0) || (inc[k][i] < 0 && inc[i][j] < 0))
          inc[k][j] = min(inc[k][j], inc[k][i] + inc[i][j]);
  
  int S;
  cin >> S;
  for (int i = 0; i < S; i++)
  {
    int u, v;
    cin >> u >> v;

    int res = inc[--u][--v];
    if (res < 0)
      cout << -1 << '\n';
    else if (res == 0 || res >= INT_MAX / 3)
      cout << 0 << '\n';
    else
      cout << 1 << '\n';
  }
  return 0;
}