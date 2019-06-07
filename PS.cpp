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

int N, M;
vector<vector<bool>> mp, visit;

pi plus_them(pi &a, pi &b)
{
  return pi(a.first + b.first, a.second + b.second);
}

bool check(pi &cur_deco, pi &diff_deco)
{
  auto ret = plus_them(cur_deco, diff_deco);
  return (ret.first >= 0 && ret.first < N && ret.second >= 0 && ret.second < M && visit[ret.first][ret.second]);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> N;
  cin >> M;
  mp.resize(N);
  visit.resize(N);
  for (int i = 0; i < N; i++)
  {
    string s;
    cin >> s;
    for (auto j : s)
    {
      mp[i].push_back(static_cast<bool>(j - '0'));
      visit[i].push_back(static_cast<bool>(j - '0'));
    }
  }
  queue<pii> que;
  que.push(pii(pi(0, 0), 1));
  vector<pi> diff;
  diff.push_back(pi(0, -1));
  diff.push_back(pi(0, 1));
  diff.push_back(pi(-1, 0));
  diff.push_back(pi(1, 0));
  while (!que.empty())
  {
    auto cur = que.front();
    //out<<cur.first.first<<" "<<cur.first.second<<endl;
    que.pop();
    if (cur.first == pi(N - 1, M - 1))
    {
      cout << cur.second << endl;
      break;
    }
    mp[cur.first.first][cur.first.second] = false;
    for (auto &d : diff)
    {
      if (check(cur.first, d))
      {
        auto pl = plus_them(cur.first, d);
        que.push(pii(pl, cur.second + 1));
        visit[pl.first][pl.second] = false;
      }
    }
  }
  return 0;
}
