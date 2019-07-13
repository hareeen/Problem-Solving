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

int solve(vector<vector<int>> &inc, vector<vector<int>> &early, int node, int lastNode, int status)
{
  if (lastNode != -1 && inc[node].size() == 1)
    return status;
  if (early[node][status] != -1)
    return early[node][status];

  int ret = status;
  for (const auto &el : inc[node])
  {
    if (el == lastNode)
      continue;
    int svFalse = solve(inc, early, el, node, 0);
    int svTrue = solve(inc, early, el, node, 1);
    if (status == 0)
      ret += svTrue;
    else
      ret += min(svTrue, svFalse);
  }

  // cout << node << " " << status << " " << ret << endl;
  return early[node][status] = ret;
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

  vector<vector<int>> early(N, vector<int>(2, -1));
  cout << min(solve(inc, early, 0, -1, 0), solve(inc, early, 0, -1, 1)) << endl;

  return 0;
}