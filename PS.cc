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

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<int> rk1(N), rk2(N);
  for (int i = 0; i < M; i++)
  {
    int u, v;
    cin >> u >> v;
    rk1[u - 1]++;
    rk2[v - 1]++;
  }

  list<int> ls;
  for (int i = 1; i <= N; i++)
    ls.push_back(i);

  vector<int> print1;
  for (int i = 0; i < N; i++)
  {
    auto iter = ls.begin();
    for (int j = 0; j < rk1[i]; j++)
    {
      iter++;
      if (iter == ls.end())
      {
        cout << -1 << endl;
        return 0;
      }
    }
    print1.push_back(*iter);
    ls.erase(iter);
  }

  for (int i = N; i >= 1; i--)
    ls.push_back(i);

  vector<int> print2;
  for (int i = N - 1; i >= 0; i--)
  {
    auto iter = ls.begin();
    for (int j = 0; j < rk2[i]; j++)
    {
      iter++;
      if (iter == ls.end())
      {
        cout << -1 << endl;
        return 0;
      }
    }
    print2.push_back(*iter);
    ls.erase(iter);
  }

  reverse(iterall(print2));

  for (int i = 0; i < N; i++)
  {
    if (print1[i] != print2[i])
    {
      cout << -1 << endl;
      return 0;
    }
  }

  for (const auto &el : print1)
    cout << el << " ";
  cout << endl;

  return 0;
}