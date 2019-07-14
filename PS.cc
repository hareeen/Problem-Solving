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

class disjointSet
{
private:
  vector<int> uf;

public:
  disjointSet(int N)
  {
    uf.clear();
    for (int i = 0; i < N; i++)
      uf.push_back(i);
  }
  int find(int n)
  {
    if (n == uf[n])
      return n;
    return uf[n] = find(uf[n]);
  }
  void merge(int u, int v)
  {
    uf[find(u)] = uf[find(v)];
    return;
  }
  bool isSameset(int u, int v)
  {
    return find(u) == find(v);
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;

  for (int tc = 0; tc < T; tc++)
  {
    int N, K;
    cin >> N >> K;

    vector<int> weight;
    for (int i = 0; i < N; i++)
    {
      int t;
      cin >> t;
      weight.push_back(t);
    }

    vector<vector<int>> inc(N);
    vector<int> remain(N);
    auto ds = disjointSet(N);
    for (int i = 0; i < K; i++)
    {
      int u, v;
      cin >> u >> v;
      u--;
      v--;
      inc[u].push_back(v);
      ds.merge(u, v);
      remain[v]++;
    }

    int target;
    cin >> target;
    target--;

    queue<int> topo;
    for (int i = 0; i < N; i++)
      if (remain[i] == 0 && ds.isSameset(i, target))
        topo.push(i);

    vector<int> minTime(N, 0);
    while (!topo.empty())
    {
      auto cur = topo.front();
      topo.pop();

      minTime[cur] += weight[cur];
      for (const auto &i : inc[cur])
      {
        minTime[i] = max(minTime[i], minTime[cur]);
        remain[i]--;
        if (remain[i] == 0)
          topo.push(i);
      }
    }

    cout << minTime[target] << '\n';
  }

  return 0;
}