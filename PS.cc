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

int operation(int n, char mode)
{
  if (mode == 'D')
    return (n * 2) % 10000;
  if (mode == 'S')
    return n == 0 ? 9999 : n - 1;
  if (mode == 'L')
    return (n % 1000) * 10 + n / 1000;
  if (mode == 'R')
    return (n % 10) * 1000 + n / 10;
  throw;
}

string process()
{
  vector<bool> visit(10000);
  int init, dest;
  cin >> init >> dest;

  char cmdlist[4] = {'D', 'S', 'L', 'R'};
  queue<pair<int, string>> que;
  que.push(make_pair(init, ""));
  visit[init] = true;

  while (!que.empty())
  {
    auto num = que.front().first;
    auto cmd = que.front().second;
    que.pop();
    if (num == dest)
      return cmd;
    for (int i = 0; i < 4; i++)
    {
      int opr_res = operation(num, cmdlist[i]);
      if (!visit[opr_res])
        visit[opr_res] = true, que.push(make_pair(opr_res, cmd + cmdlist[i]));
    }
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int K;
  cin >> K;
  for (int i = 0; i < K; i++)
  {
    cout << process() << '\n';
  }
  return 0;
}