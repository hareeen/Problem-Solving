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

void ufInit(vector<int> &par)
{
  for (int i = 0; i < par.size(); i++)
    par[i] = i;
  return;
}

int ufFind(vector<int> &par, int vtx)
{
  if (par[vtx] == vtx)
    return vtx;
  else
    return par[vtx] = ufFind(par, par[vtx]);
}

void ufMerge(vector<int> &par, int u, int v)
{
  par[ufFind(par, u)] = ufFind(par, v);
}

bool ufSameset(vector<int> &par, int u, int v)
{
  return ufFind(par, u) == ufFind(par, v);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  priority_queue<pair<int, pi>, deque<pair<int, pi>>, greater<pair<int, pi>>> pq;
  for (int i = 0; i < M; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    pq.push(make_pair(w, pi(--u, --v)));
  }

  vector<int> parent(N);
  ufInit(parent);

  int cur = 0, ans = 0;
  while (cur < N - 2)
  {
    auto edge = pq.top();
    pq.pop();
    if (!ufSameset(parent, edge.second.first, edge.second.second))
    {
      ufMerge(parent, edge.second.first, edge.second.second);
      cur++;
      ans += edge.first;
    }
  }

  cout << ans << endl;

  return 0;
}