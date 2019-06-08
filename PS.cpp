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

void que_append(queue<pi> &que, vector<bool> &check, int appd, int cur_t)
{
  if (appd >= 0 && appd < check.size() && !check[appd])
  {
    que.push(pi(appd, cur_t + 1));
    check[appd] = true;
  }
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, K;
  cin >> N >> K;
  queue<pi> que;
  que.push(pi(N, 0));
  vector<bool> check(200001);
  check[N] = true;
  while (!que.empty())
  {
    auto cur = que.front();
    que.pop();
    if (cur.first == K)
    {
      cout << cur.second << endl;
      break;
    }
    que_append(que, check, cur.first + 1, cur.second);
    que_append(que, check, cur.first - 1, cur.second);
    que_append(que, check, cur.first * 2, cur.second);
  }
  return 0;
}
