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

void dfs1(vector<vector<int>> &inc, vector<bool> &isVisit, stack<int> &trace, const int vertex)
{
  for (const auto &el : inc[vertex])
  {
    if (!isVisit[el])
    {
      isVisit[el] = true;
      dfs1(inc, isVisit, trace, el);
    }
  }
  trace.push(vertex);
  return;
}

void dfs2(vector<vector<int>> &inc, vector<bool> &isVisit, vector<int> &group, const int vertex)
{
  for (const auto &el : inc[vertex])
  {
    if (!isVisit[el])
    {
      isVisit[el] = true;
      dfs2(inc, isVisit, group, el);
    }
  }
  group.push_back(vertex);
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int V, E;
  cin >> V >> E;

  vector<vector<int>> inc1(V), inc2(V);
  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    inc1[u].push_back(v);
    inc2[v].push_back(u);
  }

  for (auto &vec : inc1)
    sort(iterall(vec));
  for (auto &vec : inc2)
    sort(iterall(vec));

  vector<bool> isVisit(V);
  stack<int> trace;

  for (int i = 0; i < V; i++)
    if (!isVisit[i])
      isVisit[i] = true, dfs1(inc1, isVisit, trace, i);

  vector<vector<int>> scc;
  isVisit = vector<bool>(V);
  while (!trace.empty())
  {
    if (!isVisit[trace.top()])
    {
      vector<int> group;
      isVisit[trace.top()] = true;
      dfs2(inc2, isVisit, group, trace.top());
      sort(iterall(group));
      group.push_back(-2);
      scc.push_back(group);
    }
    trace.pop();
  }

  vector<pi> printing;
  for (int i = 0; i < scc.size(); i++)
    printing.push_back(pi(scc[i][0], i));
  sort(iterall(printing));

  cout << scc.size() << '\n';
  for (const auto &[minel, idx] : printing)
  {
    for (const auto &el : scc[idx])
      cout << el + 1 << " ";
    cout << '\n';
  }

  return 0;
}