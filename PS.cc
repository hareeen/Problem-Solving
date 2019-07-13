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

void ufInit(vector<int> &par)
{
  for (int i = 0; i < par.size(); i++)
    par[i] = i;
  return;
}

int ufFind(vector<int> &par, int vtx)
{
  if (par[vtx] == vtx)
    return vtx;
  else
    return par[vtx] = ufFind(par, par[vtx]);
}

void ufMerge(vector<int> &par, int u, int v)
{
  par[ufFind(par, u)] = ufFind(par, v);
}

bool ufSameset(vector<int> &par, int u, int v)
{
  return ufFind(par, u) == ufFind(par, v);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<int> parent(N);
  ufInit(parent);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      if (i > j && t == 1)
        ufMerge(parent, i, j);
    }
  }

  bool ret = true;
  int lst, cur;
  cin >> lst;
  lst--;
  for (int i = 1; i < M; i++)
  {
    cin >> cur;
    cur--;
    ret &= ufSameset(parent, lst, cur);
    lst = cur;
  }

  cout << (ret ? "YES" : "NO") << endl;

  return 0;
}