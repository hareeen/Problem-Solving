#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

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

void ufinit(vector<int> &parent)
{
  for (int i = 0; i < parent.size(); i++)
    parent[i] = i;
  return;
}

int uffind(vector<int> &parent, int x)
{
  if (parent[x] == x)
    return x;
  else
    return parent[x] = uffind(parent, parent[x]);
}

void ufunion(vector<int> &parent, int x, int y)
{
  parent[uffind(parent, y)] = uffind(parent, x);
  return;
}

int ufcount(vector<int> &parent)
{
  int ret = 0;
  vector<bool> count(parent.size());
  for (const auto &el : parent)
    count[uffind(parent, el)] = true;
  for (auto el : count)
    if (el)
      ret++;
  return ret;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<int> parent(++N);
  ufinit(parent);
  for (int i = 0; i < M; i++)
  {
    int md, a, b;
    cin >> md >> a >> b;
    if (md == 0)
      ufunion(parent, a, b);
    else
      cout << (uffind(parent, a) == uffind(parent, b) ? "YES" : "NO") << '\n';
  }
  return 0;
}
