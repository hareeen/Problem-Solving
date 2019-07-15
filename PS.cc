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

class SegmentTree
{
private:
  vector<int> tree;

public:
  SegmentTree(int N)
  {
    tree.clear();
    tree.resize(static_cast<int>(pow(2, floor(log2(N) + 1) + 1)) + 1);
  }
  int init(vector<int> &arr, int s, int e, int node)
  {
    if (s == e)
      return tree[node] = arr[s];
    else
      return tree[node] = init(arr, s, (s + e) / 2, node * 2) + init(arr, (s + e) / 2 + 1, e, node * 2 + 1);
  }
  void update(int target, int s, int e, int node, int diff)
  {
    if (target < s || e < target)
      return;
    tree[node] += diff;
    if (s != e)
    {
      update(target, s, (s + e) / 2, node * 2, diff);
      update(target, (s + e) / 2 + 1, e, node * 2 + 1, diff);
    }
    return;
  }
  int query(int l, int r, int s, int e, int node) // SUM
  {
    if (r < s || e < l)
      return 0;
    else if (l <= s && e <= r)
      return tree[node];
    else
      return query(l, r, s, (s + e) / 2, node * 2) + query(l, r, (s + e) / 2 + 1, e, node * 2 + 1);
  }
};

i64 process()
{
  int N;
  cin >> N;

  vector<pi> corY, corr;
  for (int i = 0; i < N; i++)
  {
    int x, y;
    cin >> x >> y;
    corY.push_back(pi(y, i));
    corr.push_back(pi(-x, y));
  }

  sort(iterall(corY));

  int cur = 0, last = INT_MAX;
  for (auto &[num, idx] : corY)
  {
    if (num != last)
      cur++, last = num;
    corr[idx].second = cur;
  }
  int maxY = cur + 1;

  sort(iterall(corr));

  i64 ret = 0;
  auto segt = SegmentTree(maxY);
  for (const auto &[x, y] : corr)
  {
    ret += segt.query(1, y, 1, maxY, 1);
    segt.update(y, 1, maxY, 1, 1);
  }

  return ret;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++)
    cout << process() << '\n';
}