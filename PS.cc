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
  cin >> N >> M;

  vector<vector<pli>> inc(N, vector<pli>());
  for (int i = 0; i < M; i++)
  {
    i64 u, v, w;
    cin >> u >> v >> w;
    inc[u - 1].push_back(pli(v - 1, w));
  }

  vector<i64> dist(N, INT_MAX);
  dist[0] = 0;

  for (int i = 0; i < N - 1; i++)
  {
    for (int j = 0; j < N; j++)
    {
      for (const auto &[vertex, weight] : inc[j])
        if (dist[j] != INT_MAX && dist[j] + weight < dist[vertex])
          dist[vertex] = dist[j] + weight;
    }
  }

  for (int j = 0; j < N; j++)
  {
    for (const auto &[vertex, weight] : inc[j])
    {
      if (dist[j] != INT_MAX && dist[j] + weight < dist[vertex])
      {
        cout << -1 << endl;
        return 0;
      }
    }
  }

  for (int i = 1; i < N; i++)
    cout << (dist[i] >= INT_MAX ? -1 : dist[i]) << '\n';

  return 0;
}