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
#include <unordered_map>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define M_iterai64(container) container.begin(), container.end()

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

  int N, r1, r2;
  cin >> N >> r1 >> r2;
  r1--;
  r2--;
  vector<bool> visited(N);
  vector<vector<pi>> adjL(N);
  visited[r1] = true;
  for (int i = 0; i < N - 1; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    adjL[u].push_back(pi(v, w));
    adjL[v].push_back(pi(u, w));
  }
  queue<ti> que;
  que.push(ti(r1, 0, 0));
  while (true)
  {
    auto cur = que.front();
    int cur_vertex = get<0>(cur);
    int cur_weight = get<1>(cur);
    int cur_weight_max = get<2>(cur);

    que.pop();

    if (cur_vertex == r2)
    {
      cout << cur_weight - cur_weight_max << endl;
      break;
    }

    for (auto [vertex, weight] : adjL[cur_vertex])
    {
      if (!visited[vertex])
      {
        visited[vertex] = true;
        que.push(ti(vertex, cur_weight + weight, max(cur_weight_max, weight)));
      }
    }
  }
  return 0;
}
