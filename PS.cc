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
  vector<vector<int>> mp(N), mpg(N), mpr(N), mpb(N);
  vector<vector<bool>> check(N), checkb(N), checkg(N), checkr(N);
  queue<pi> que;
  for (int i = 0; i < N; i++)
  {
    string s;
    cin >> s;
    for (auto &j : s)
    {
      mp[i].push_back(static_cast<int>(j != 'B'));
      mpg[i].push_back(static_cast<int>(j == 'G'));
      mpr[i].push_back(static_cast<int>(j == 'R'));
      mpb[i].push_back(static_cast<int>(j == 'B'));
      check[i].push_back((j == 'B'));
      checkg[i].push_back((j != 'G'));
      checkr[i].push_back((j != 'R'));
      checkb[i].push_back((j != 'B'));
    }
  }

  int apd_clr2 = 1;
  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (!checkb[i][j])
      {
        que = queue<pi>();
        que_append(pi(i, j), apd_clr2, N, mpb, checkb, que);
        while (!que.empty())
        {
          auto cur = que.front();
          que.pop();
          for (int k = 0; k < 4; k++)
            que_append(pi(cur.first + dx[k], cur.second + dy[k]), apd_clr2, N, mpb, checkb, que);
        }
        apd_clr2++;
      }
    }
  }

  int apd_clr1 = 1;
  que = queue<pi>();
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (!checkg[i][j])
      {
        que = queue<pi>();
        que_append(pi(i, j), apd_clr1, N, mpg, checkg, que);
        while (!que.empty())
        {
          auto cur = que.front();
          que.pop();
          for (int k = 0; k < 4; k++)
            que_append(pi(cur.first + dx[k], cur.second + dy[k]), apd_clr1, N, mpg, checkg, que);
        }
        apd_clr1++;
      }
    }
  }

  que = queue<pi>();
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (!checkr[i][j])
      {
        que = queue<pi>();
        que_append(pi(i, j), apd_clr1, N, mpr, checkr, que);
        while (!que.empty())
        {
          auto cur = que.front();
          que.pop();
          for (int k = 0; k < 4; k++)
            que_append(pi(cur.first + dx[k], cur.second + dy[k]), apd_clr1, N, mpr, checkr, que);
        }
        apd_clr1++;
      }
    }
  }

  cout << apd_clr1 - 1 + apd_clr2 - 1 << " ";

  int apd_clr = 1;
  que = queue<pi>();
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
  cout << apd_clr - 1 + apd_clr2 - 1 << " ";
  cout << endl;

  return 0;
}