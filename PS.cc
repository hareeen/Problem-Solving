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

pi getProper3(pi f, pi s, pi t)
{
  return {min(min(f.first, s.first), t.first), max(max(f.second, s.second), t.second)};
}

pi getProper2(pi l, pi r)
{
  return {min(l.first, r.first), max(l.second, r.second)};
}

void constructTree(const vector<vector<pi>> &inc, vector<int> &depth, vector<vector<int>> &parents, vector<vector<int>> &maxParents, vector<vector<int>> &minParents, int node, int last, int lastWeight)
{
  depth[node] = (last == -1 ? 1 : (depth[last] + 1));
  parents[node].push_back(last);
  minParents[node].push_back((lastWeight == -1 ? INT_MAX : lastWeight));
  maxParents[node].push_back((lastWeight == -1 ? INT_MIN : lastWeight));

  for (int cur = 2; cur < depth[node]; cur *= 2)
  {
    minParents[node].push_back(min(minParents[node].back(), minParents[parents[node].back()][parents[node].size() - 1]));
    maxParents[node].push_back(max(maxParents[node].back(), maxParents[parents[node].back()][parents[node].size() - 1]));
    parents[node].push_back(parents[parents[node].back()][parents[node].size() - 1]);
  }

  for (const auto &el : inc[node])
    if (el.first != last)
      constructTree(inc, depth, parents, maxParents, minParents, el.first, node, el.second);

  return;
}

pi LCA(vector<int> &depth, vector<vector<int>> &parents, vector<vector<int>> &maxParents, vector<vector<int>> &minParents, int u, int v)
{
  // cout << u << " " << v << endl;
  if (depth[u] == depth[v])
  {
    if (u == v)
      return {INT_MAX, INT_MIN};
    else if (parents[u][0] == parents[v][0])
      return {min(minParents[u][0], minParents[v][0]), max(maxParents[u][0], maxParents[v][0])};
    for (int i = 1; i < parents[u].size(); i++)
      if (parents[u][i] == parents[v][i])
        return getProper3({minParents[u][i - 1], maxParents[u][i - 1]}, {minParents[v][i - 1], maxParents[v][i - 1]}, LCA(depth, parents, maxParents, minParents, parents[u][i - 1], parents[v][i - 1]));
    return getProper3({minParents[u].back(), maxParents[u].back()}, {minParents[v].back(), maxParents[v].back()}, LCA(depth, parents, maxParents, minParents, parents[u].back(), parents[v].back()));
  }
  else
  {
    if (depth[u] < depth[v])
      swap(u, v);
    int depthUp = static_cast<int>(log2(static_cast<double>(depth[u] - depth[v])));
    // cout << depthUp << " " << minParents[u][depthUp] << " " << maxParents[u][depthUp] << endl;
    return getProper2({minParents[u][depthUp], maxParents[u][depthUp]}, LCA(depth, parents, maxParents, minParents, parents[u][depthUp], v));
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<vector<pi>> inc(N);
  for (int i = 0; i < N - 1; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    inc[u].push_back({v, w});
    inc[v].push_back({u, w});
  }

  vector<int> depth(N);
  vector<vector<int>> parents(N), minParents(N), maxParents(N);
  constructTree(inc, depth, parents, maxParents, minParents, 0, -1, -1);

  int M;
  cin >> M;

  for (int i = 0; i < M; i++)
  {
    int u, v;
    cin >> u >> v;
    auto [ansMin, ansMax] = LCA(depth, parents, maxParents, minParents, --u, --v);
    cout << ansMin << " " << ansMax << '\n';
  }

  return 0;
}