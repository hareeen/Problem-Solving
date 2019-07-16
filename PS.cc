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

bool process()
{
  int N, M, W;
  cin >> N >> M >> W;

  vector<vector<i64>> inc(N, vector<i64>(N, INT_MAX));
  for (int i = 0; i < M + W; i++)
  {
    i64 u, v, w;
    cin >> u >> v >> w;
    inc[u - 1][v - 1] = min(inc[u - 1][v - 1], (i >= M ? -w : w));
    if (i < M)
      inc[v - 1][u - 1] = min(inc[v - 1][u - 1], w);
  }

  vector<i64> dist(N, INT_MAX);
  dist[0] = 0;

  for (int i = 0; i < N - 1; i++)
  {
    for (int j = 0; j < N; j++)
    {
      for (int v = 0; v < N; v++)
        if (dist[j] != INT_MAX && dist[j] + inc[j][v] < dist[v])
          dist[v] = dist[j] + inc[j][v];
    }
  }

  for (int j = 0; j < N; j++)
  {
    for (int v = 0; v < N; v++)
      if (dist[j] != INT_MAX && dist[j] + inc[j][v] < dist[v])
        return true;
  }

  return false;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++)
    cout << (process() ? "YES" : "NO") << '\n';

  return 0;
}