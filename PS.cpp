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
#include <unordered_map>

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

int ufunion_count(vector<int> &parent, vector<int> &nodeCount, int x, int y)
{
  auto xroot = uffind(parent, x);
  auto yroot = uffind(parent, y);
  if (xroot != yroot)
  {
    parent[yroot] = xroot;
    nodeCount[xroot] += nodeCount[yroot];
    nodeCount[y] = 1;
  }
  return nodeCount[xroot];
}

int ufcount(vector<int> &parent, int x)
{
  int ret = 0;
  int target = uffind(parent, x);
  for (const auto &el : parent)
    if (uffind(parent, el) == target)
      ret++;
  return ret;
}

void process()
{
  int N;
  int cur_max = 0;
  cin >> N;
  vector<int> parent(2 * N);
  vector<int> nodeCount(2 * N, 1);
  unordered_map<string, int> _map;
  ufinit(parent);
  for (int i = 0; i < N; i++)
  {
    int i1, i2;
    string s1, s2;
    cin >> s1 >> s2;

    auto it1 = _map.find(s1);
    if (it1 == _map.end())
      i1 = _map[s1] = cur_max++;
    else
      i1 = it1->second;

    auto it2 = _map.find(s2);
    if (it2 == _map.end())
      i2 = _map[s2] = cur_max++;
    else
      i2 = it2->second;

    cout << ufunion_count(parent, nodeCount, i1, i2) << '\n';
  }
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int tc = 0; tc < T; tc++)
    process();
  return 0;
}
