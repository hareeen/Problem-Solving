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

vector<int> addVector(vector<int> &lhs, vector<int> &rhs)
{
  vector<int> result;
  for (int i = 0; i < lhs.size(); i++)
    result.push_back(lhs[i] + rhs[i]);
  return result;
}

class segmentTree
{
private:
  int treeSize;
  int elementSize;
  vector<vector<int>> tree;

public:
  segmentTree(const int N)
  {
    treeSize = (1 << static_cast<int>(ceil(log2(N)) + 1)) + 1;
    tree.clear();
    tree.resize(treeSize, vector<int>(N));
  }
  vector<int> init(const vector<vector<int>> &arr, const int s, const int e, const int node)
  {
    if (s == e)
      return tree[node] = arr[s];
    else
    {
      auto leftRes = init(arr, s, (s + e) / 2, node * 2);
      auto rightRes = init(arr, (s + e) / 2 + 1, e, node * 2 + 1);
      return tree[node] = addVector(leftRes, rightRes);
    }
  }
  void update(const int t, const int s, const int e, const int node, const int yCorr, const int diff)
  {
    if (t < s || e < t)
      return;
    tree[node][yCorr] += diff;
    if (s != e)
    {
      update(t, s, (s + e) / 2, node * 2, yCorr, diff);
      update(t, (s + e) / 2 + 1, e, node * 2 + 1, yCorr, diff);
    }
  }
  int query(const int s, const int e, const int node, const int lx, const int ly, const int rx, const int ry)
  {
    if (e < lx || rx < s)
      return 0;
    if (lx <= s && e <= rx)
    {
      int ret = 0;
      for (int i = ly; i <= ry; i++)
        ret += tree[node][i];
      return ret;
    }
    return query(s, (s + e) / 2, node * 2, lx, ly, rx, ry) + query((s + e) / 2 + 1, e, node * 2 + 1, lx, ly, rx, ry);
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> mp(1, vector<int>(N));
  for (int i = 0; i < N; i++)
  {
    vector<int> pb;
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      pb.push_back(t);
    }
    mp.push_back(pb);
  }

  auto sT = segmentTree(N);
  sT.init(mp, 1, N, 1);
  for (int i = 0; i < M; i++)
  {
    int mode;
    cin >> mode;
    if (mode == 0)
    {
      int x, y, c;
      cin >> x >> y >> c;
      y--;
      sT.update(x, 1, N, 1, y, c - mp[x][y]);
      mp[x][y] = c;
    }
    else
    {
      int sx, sy, ex, ey;
      cin >> sx >> sy >> ex >> ey;
      if (sx > ex)
        swap(sx, ex);
      if (sy > ey)
        swap(sy, ey);
      cout << sT.query(1, N, 1, sx, sy - 1, ex, ey - 1) << '\n';
    }
  }

  return 0;
}