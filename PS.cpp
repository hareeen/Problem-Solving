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

void que_append(pi apd_deco, int apd_clr, int &N, vector<vector<int>> &mp, vector<vector<bool>> &check, queue<pi> &que)
{
  if (apd_deco.first >= 0 && apd_deco.first < N &&
      apd_deco.second >= 0 && apd_deco.second < N &&
      !check[apd_deco.first][apd_deco.second])
  {
    que.push(apd_deco);
    mp[apd_deco.first][apd_deco.second] = apd_clr;
    check[apd_deco.first][apd_deco.second] = true;
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<vector<int>> mp(N);
  vector<vector<bool>> check(N);
  queue<pi> que;
  for (int i = 0; i < N; i++)
  {
    string s;
    cin >> s;
    for (auto &j : s)
    {
      mp[i].push_back(static_cast<int>(j - '0'));
      check[i].push_back((j == '0'));
    }
  }

  int apd_clr = 1;
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (!check[i][j])
      {
        que = queue<pi>();
        que_append(pi(i, j), apd_clr, N, mp, check, que);
        while (!que.empty())
        {
          auto cur = que.front();
          que.pop();
          for (int k = 0; k < 4; k++)
            que_append(pi(cur.first + dx[k], cur.second + dy[k]), apd_clr, N, mp, check, que);
        }
        apd_clr++;
      }
    }
  }
  vector<int> clr(apd_clr - 1);
  for (const auto &i : mp)
    for (const auto &j : i)
      if (j != 0)
        clr[j - 1]++;

  sort(clr.begin(), clr.end());
  cout << clr.size() << endl;
  for (const auto &i : clr)
    cout << i << '\n';
  return 0;
}
