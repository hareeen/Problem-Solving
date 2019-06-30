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

#define M_iterall(container) container.begin(), container.end()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

void mp_assign(vector<vector<int>> &mp, vector<pi> &a, int idx)
{
  mp[a[idx].first][a[idx].second] = -1;
  return;
}

int bfs(int N, int M, vector<vector<int>> &mp, vector<pi> &virus)
{
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  queue<pi> que;
  for (const auto &el : virus)
    que.push(pi(el)), mp[el.first][el.second] = 1;
  while (!que.empty())
  {
    auto cur = que.front();
    que.pop();
    for (int i = 0; i < 4; i++)
    {
      int corX = cur.first + dx[i];
      int corY = cur.second + dy[i];
      if (corX >= 0 && corX < N && corY >= 0 && corY < M && mp[corX][corY] == 0)
      {
        que.push(pi(corX, corY));
        mp[corX][corY] = 1;
      }
    }
  }
  int _s = 0;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      if (mp[i][j] == 0)
        _s++;
    }
  }
  return _s;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<vector<int>> _map(N);
  vector<pi> virus;
  vector<pi> empty;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      int t;
      cin >> t;
      _map[i].push_back((t == 1 ? -1 : 0));
      if (t == 0)
        empty.push_back(pi(i, j));
      if (t == 2)
        virus.push_back(pi(i, j));
    }
  }
  int ret = INT_MIN;
  for (int i = 0; i < empty.size() - 2; i++)
  {
    for (int j = i + 1; j < empty.size() - 1; j++)
    {
      for (int k = j + 1; k < empty.size(); k++)
      {
        auto mp = _map;
        mp_assign(mp, empty, i);
        mp_assign(mp, empty, j);
        mp_assign(mp, empty, k);
        ret = max(ret, bfs(N, M, mp, virus));
      }
    }
  }

  cout << ret << endl;
  return 0;
}
