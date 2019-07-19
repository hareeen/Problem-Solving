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

class fenwickTree
{
private:
  int treeSize;
  vector<i64> tree;

public:
  fenwickTree(const int N)
  {
    tree.clear();
    treeSize = N;
    tree.resize(N + 1);
  }
  void init(vector<int> &arr)
  {
    for (int i = 1; i <= treeSize; i++)
      update(i, arr[i]);
    return;
  }
  i64 sum(int i)
  {
    i64 ans = 0;
    while (i > 0)
    {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
  i64 get(int i)
  {
    return tree[i];
  }
  void update(int i, i64 diff)
  {
    while (i <= treeSize)
    {
      tree[i] += diff;
      i += (i & -i);
    }
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  auto fT = fenwickTree(N);
  for (int i = 0; i < M; i++)
  {
    int a;
    cin >> a;
    if (a == 0)
    {
      int u, v;
      cin >> u >> v;
      if (u > v)
        swap(u, v);
      cout << fT.sum(v) - fT.sum(u - 1) << '\n';
    }
    else
    {
      int v;
      i64 d;
      cin >> v >> d;
      fT.update(v, d - (fT.sum(v) - fT.sum(v - 1)));
    }
  }

  return 0;
}