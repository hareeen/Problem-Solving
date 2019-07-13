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

using piv = pair<int, vector<int>>;

auto dijkstra(vector<vector<pi>> &inc, vector<vector<bool>> &check, int sNode)
{
  priority_queue<pi, deque<pi>, greater<pi>> pq;
  vector<piv> dist(inc.size(), piv(INT_MAX / 4, vector<int>()));

  dist[sNode] = piv(0, vector<int>(1, sNode));
  pq.push(pi(0, sNode));
  while (!pq.empty())
  {
    auto cur = pq.top();
    pq.pop();
    if (cur.first > dist[cur.second].first)
      continue;
    for (const auto &[vertex, weight] : inc[cur.second])
    {
      if (dist[vertex].first >= weight + cur.first && check[cur.second][vertex])
      {
        if (dist[vertex].first > weight + cur.first)
          dist[vertex].second.clear();
        dist[vertex].first = weight + cur.first;
        dist[vertex].second.push_back(cur.second);
        pq.push(pi(weight + cur.first, vertex));
      }
    }
  }

  return dist;
}

void erase_edge(vector<vector<bool>> &check, vector<piv> &dist, int n)
{
  if (n == dist[n].second[0])
    return;
  for (const auto &el : dist[n].second)
  {
    check[el][n] = false;
    erase_edge(check, dist, el);
  }
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  while (true)
  {
    int N, M;
    cin >> N >> M;
    if (N + M == 0)
      break;

    int S, D;
    cin >> S >> D;

    vector<vector<pi>> inc(N);
    vector<vector<bool>> check(N, vector<bool>(N, true));
    for (int i = 0; i < M; i++)
    {
      int u, v, w;
      cin >> u >> v >> w;
      inc[u].push_back(pi(v, w));
    }

    int min_dist = -1;
    while (true)
    {
      auto dist = dijkstra(inc, check, S);
      if (min_dist == -1)
      {
        if (dist[D].first >= INT_MAX / 4)
        {
          cout << -1 << '\n';
          break;
        }
        min_dist = dist[D].first;
      }
      else if (min_dist != dist[D].first)
      {
        cout << (dist[D].first >= INT_MAX / 4 ? -1 : dist[D].first) << '\n';
        break;
      }
      erase_edge(check, dist, D);
    }
  }

  return 0;
}