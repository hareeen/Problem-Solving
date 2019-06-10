#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

using pii = pair<pi, int>;

void que_append(pii to_append, int &M, int &N, vector<vector<int>> &mp, vector<vector<bool>> &check, queue<pii> &que)
{
  auto appendDeco = to_append.first;
  auto appendDay = to_append.second;
  if (appendDeco.first >= 0 && appendDeco.first < N &&
      appendDeco.second >= 0 && appendDeco.second < M &&
      !check[appendDeco.first][appendDeco.second])
  {
    que.push(to_append);
    check[appendDeco.first][appendDeco.second] = true;
    mp[appendDeco.first][appendDeco.second] = appendDay;
  }
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int M, N;
  cin >> M >> N;
  vector<vector<int>> mp(N);
  vector<vector<bool>> check(N);
  queue<pii> que;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      int t;
      cin >> t;
      mp[i].push_back(t);
      check[i].push_back((t != 0));
      if (t == 1)
        que.push(pii(pi(i, j), 0));
    }
  }
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};
  bool che_ini = true;
  for (const auto &i : check)
    for (const auto &j : i)
      che_ini &= j;
  if (che_ini)
  {
    cout << 0 << endl;
    return 0;
  }
  while (!que.empty())
  {
    auto curDeco = que.front().first;
    auto curDay = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++)
      que_append(pii(pi(curDeco.first + dx[i], curDeco.second + dy[i]), curDay + 1), M, N, mp, check, que);
  }
  int res = INT_MIN;
  for (const auto &i : mp)
  {
    for (const auto &j : i)
    {
      res = max(res, j);
      if (j == 0)
      {
        cout << -1 << endl;
        return 0;
      }
    }
  }

  cout << res << endl;
  return 0;
}
