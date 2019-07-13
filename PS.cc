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

vector<int> dijkstra(vector<vector<pi>> &inc, int sNode)
{
  priority_queue<pi, deque<pi>, greater<pi>> pq;
  vector<int> dist(inc.size(), INT_MAX / 4);

  dist[sNode] = 0;
  pq.push(pi(0, sNode));
  while (!pq.empty())
  {
    auto cur = pq.top();
    pq.pop();
    if (cur.first > dist[cur.second])
      continue;
    for (const auto &[vertex, weight] : inc[cur.second])
    {
      if (dist[vertex] > weight + cur.first)
      {
        dist[vertex] = weight + cur.first;
        pq.push(pi(weight + cur.first, vertex));
      }
    }
  }

  return dist;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<pi>> inc(N);
  for (int i = 0; i < M; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    inc[u].push_back(pi(v, w));
    inc[v].push_back(pi(u, w));
  }

  int m1, m2;
  cin >> m1 >> m2;
  vector<int> dist_s = dijkstra(inc, 0), dist_e = dijkstra(inc, N - 1);
  int midDist = dijkstra(inc, --m1)[--m2];
  vector<int> dist;
  dist.push_back(midDist);
  dist.push_back(dist_s[m1] + dist_e[m2]);
  dist.push_back(dist_s[m2] + dist_e[m1]);

  if (*min_element(iterall(dist)) >= INT_MAX / 4)
    cout << -1 << endl;
  else
    cout << min(dist[1], dist[2]) + dist[0] << endl;

  return 0;
}