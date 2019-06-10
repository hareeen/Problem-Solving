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

void que_append(pi apd_deco, int apd_clr, int &N, int &M, vector<vector<int>> &mp, vector<vector<bool>> &check, queue<pi> &que)
{
  if (apd_deco.first >= 0 && apd_deco.first < N &&
      apd_deco.second >= 0 && apd_deco.second < M &&
      !check[apd_deco.first][apd_deco.second])
  {
    que.push(apd_deco);
    mp[apd_deco.first][apd_deco.second] = apd_clr;
    check[apd_deco.first][apd_deco.second] = true;
  }
}

void process()
{
  int N, M, K;
  cin >> M >> N >> K;
  vector<vector<int>> mp(N, vector<int>(M));
  vector<vector<bool>> check(N, vector<bool>(M, true));
  queue<pi> que;
  for (int i = 0; i < K; i++)
  {
    int a, b;
    cin >> b >> a;
    mp[a][b] = 1;
    check[a][b] = false;
  }

  int apd_clr = 1;
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      if (!check[i][j])
      {
        que = queue<pi>();
        que_append(pi(i, j), apd_clr, N, M, mp, check, que);
        while (!que.empty())
        {
          auto cur = que.front();
          que.pop();
          for (int k = 0; k < 4; k++)
            que_append(pi(cur.first + dx[k], cur.second + dy[k]), apd_clr, N, M, mp, check, que);
        }
        apd_clr++;
      }
    }
  }
  cout << apd_clr - 1 << '\n';
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++)
    process();

  return 0;
}
