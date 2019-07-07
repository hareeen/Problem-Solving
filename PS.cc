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

#define M_iterall(container) container.begin(), container.end()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

using pii = pair<pi, int>;

int process()
{
  int s;
  pi init, dest;
  cin >> s;
  cin >> init.first >> init.second;
  cin >> dest.first >> dest.second;
  queue<pii> que;

  int dx[8] = {2, 2, 1, 1, -1, -1, -2, -2};
  int dy[8] = {1, -1, 2, -2, 2, -2, 1, -1};
  vector<vector<bool>> visit(s, vector<bool>(s));

  visit[init.first][init.second] = true;
  que.push(pii(init, 0));
  while (!que.empty())
  {
    auto cur = que.front().first;
    auto cur_T = que.front().second;
    if (cur == dest)
      return cur_T;
    que.pop();
    for (int i = 0; i < 8; i++)
    {
      int next_x = cur.first + dx[i];
      int next_y = cur.second + dy[i];
      if (0 <= next_x && next_x < s && 0 <= next_y && next_y < s && !visit[next_x][next_y])
      {
        visit[next_x][next_y] = true;
        que.push(pii(pi(next_x, next_y), cur_T + 1));
      }
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int TC;
  cin >> TC;
  for (int tc = 0; tc < TC; tc++)
  {
    cout << process() << '\n';
  }

  return 0;
}