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

void configure_tree(vector<vector<int>> &inc, vector<pair<vector<int>, int>> &tree, int node, int parent)
{
  tree[node].second = (parent == -1 ? 1 : (tree[parent].second + 1));
  tree[node].first.push_back(parent);

  for (int cur = 2; cur < tree[node].second; cur *= 2)
    tree[node].first.push_back(tree[tree[node].first.back()].first[tree[node].first.size() - 1]);

  for (const auto &el : inc[node])
    if (tree[el].first.empty())
      configure_tree(inc, tree, el, node);

  return;
}

int LCA(vector<pair<vector<int>, int>> &tree, int u, int v)
{
  if (tree[u].second == tree[v].second)
  {
    if (u == v)
      return u;
    if (tree[u].first[0] == tree[v].first[0])
      return tree[u].first[0];
    for (int i = 1; i < tree[u].first.size(); i++)
      if (tree[u].first[i] == tree[v].first[i])
        return LCA(tree, tree[u].first[i - 1], tree[v].first[i - 1]);
    return LCA(tree, tree[u].first.back(), tree[v].first.back());
  }
  else
  {
    if (tree[u].second < tree[v].second)
      swap(u, v);
    return LCA(tree, tree[u].first[static_cast<int>(log2(static_cast<double>(tree[u].second - tree[v].second)))], v);
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<vector<int>> inc(N);
  for (int i = 0; i < N - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    inc[u].push_back(v);
    inc[v].push_back(u);
  }

  vector<pair<vector<int>, int>> tree(N);
  configure_tree(inc, tree, 0, -1);

  int M;
  cin >> M;
  for (int i = 0; i < M; i++)
  {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    cout << LCA(tree, u, v) + 1 << '\n';
  }

  return 0;
}