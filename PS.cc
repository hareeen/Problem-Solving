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

using pii = pair<int, pi>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M, H;
  int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
  cin >> N >> M >> H;
  vector<vector<vector<int>>> holes(N, vector<vector<int>>(M, vector<int>(4, -1)));

  // 0: down, 1: up, 2:right, 3:left
  for (int i = 0; i < N + 1; i++)
  {
    for (int j = 0; j < M; j++)
    {
      int h;
      cin >> h;
      if (i != N)
        holes[i][j][1] = h;
      if (i != 0)
        holes[i - 1][j][0] = h;
    }
  }
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M + 1; j++)
    {
      int h;
      cin >> h;
      if (j != M)
        holes[i][j][3] = h;
      if (j != 0)
        holes[i][j - 1][2] = h;
    }
  }

  priority_queue<pii, deque<pii>, greater<pii>> pq;
  vector<vector<int>> water(N, vector<int>(M, H));
  for (int i = 0; i < M; i++)
  {
    if (holes[0][i][1] != -1 && holes[0][i][1] < water[0][i])
      pq.push(pii(holes[0][i][1], pi(0, i))), water[0][i] = holes[0][i][1];
    if (holes[N - 1][i][0] != -1 && holes[N - 1][i][0] < water[N - 1][i])
      pq.push(pii(holes[N - 1][i][0], pi(N - 1, i))), water[N - 1][i] = holes[N - 1][i][0];
  }
  for (int i = 0; i < N; i++)
  {
    if (holes[i][0][3] != -1 && holes[i][0][3] < water[i][0])
      pq.push(pii(holes[i][0][3], pi(i, 0))), water[i][0] = holes[i][0][3];
    if (holes[i][M - 1][2] != -1 && holes[i][M - 1][2] < water[i][M - 1])
      pq.push(pii(holes[i][M - 1][2], pi(i, M - 1))), water[i][M - 1] = holes[i][M - 1][2];
  }

  while (!pq.empty())
  {
    auto cur = pq.top();
    auto curH = cur.first, curX = cur.second.first, curY = cur.second.second;
    pq.pop();
    if (water[curX][curY] < curH)
      continue;
    for (int i = 0; i < 4; i++)
    {
      if (holes[curX][curY][i] != -1)
      {
        int x = curX + dx[i], y = curY + dy[i];
        if (x < 0 || x >= N || y < 0 || y >= M)
          continue;
        if (water[x][y] > max(curH, holes[curX][curY][i]))
        {
          water[x][y] = max(curH, holes[curX][curY][i]);
          pq.push(pii(max(curH, holes[curX][curY][i]), pi(x, y)));
        }
      }
    }
  }

  int ans = 0;
  for (const auto &vec : water)
    for (const auto &el : vec)
      ans += el;
  cout << ans << endl;

  return 0;
}