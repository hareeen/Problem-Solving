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

class segmentTree
{
private:
  int treeSize;
  vector<int> value;
  vector<int> lazy;

public:
  segmentTree(const int N)
  {
    treeSize = (1 << static_cast<int>(ceil(log2(N)) + 1));
    value.resize(treeSize, 0);
    lazy.resize(treeSize, 0);
  }

  int init(int s, int e, int node, vector<int> &arr)
  {
    if (s == e)
      return value[node] = arr[s];
    else
      return value[node] = init(s, (s + e) / 2, node * 2, arr) ^ init((s + e) / 2 + 1, e, node * 2 + 1, arr);
  }

  void update(const int l, const int r, int s, int e, int node)
  {
    if (lazy[node] != 0)
    {
      value[node] = (e - s + 1) - value[node];
      if (s != e)
      {
        lazy[node * 2] ^= lazy[node];
        lazy[node * 2 + 1] ^= lazy[node];
      }
      lazy[node] = 0;
    }

    if (e < l || r < s)
      return;

    if (l <= s && e <= r)
    {
      value[node] = (e - s + 1) - value[node];
      if (s != e)
      {
        lazy[node * 2] ^= 1;
        lazy[node * 2 + 1] ^= 1;
      }
      return;
    }

    update(l, r, s, (s + e) / 2, node * 2);
    update(l, r, (s + e) / 2 + 1, e, node * 2 + 1);

    value[node] = value[node * 2] + value[node * 2 + 1];
    return;
  }

  int query(const int l, const int r, int s, int e, int node)
  {
    if (lazy[node] != 0)
    {
      value[node] = (e - s + 1) - value[node];
      if (s != e)
      {
        lazy[node * 2] ^= lazy[node];
        lazy[node * 2 + 1] ^= lazy[node];
      }
      lazy[node] = 0;
    }

    if (e < l || r < s)
      return 0;
    else if (l <= s && e <= r)
      return value[node];
    else
      return query(l, r, s, (s + e) / 2, node * 2) + query(l, r, (s + e) / 2 + 1, e, node * 2 + 1);
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  auto sT = segmentTree(N);
  for (int i = 0; i < M; i++)
  {
    int mode, u, v;
    cin >> mode >> u >> v;
    if (mode == 0)
      sT.update(u, v, 1, N, 1);
    else
      cout << sT.query(u, v, 1, N, 1) << '\n';
  }

  return 0;
}