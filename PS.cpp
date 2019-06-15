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

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  vector<vector<int>> adjl;
  vector<int> remain;
  vector<bool> check;
  cin >> N >> M;
  adjl.resize(N);
  remain.resize(N);
  check.resize(N);
  for (int i = 0; i < M; i++)
  {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    adjl[a].push_back(b);
    remain[b]++;
  }
  priority_queue<int, vector<int>, greater<int>> que;
  for (int i = 0; i < N; i++)
  {
    if (remain[i] == 0)
    {
      que.push(i);
      check[i] = true;
    }
  }
  while (!que.empty())
  {
    int cur = que.top();
    cout << cur + 1 << " ";
    que.pop();
    for (auto &el : adjl[cur])
    {
      remain[el]--;
      if (remain[el] == 0)
      {
        que.push(el);
        check[el] = true;
      }
    }
  }
  cout << endl;
  return 0;
}
