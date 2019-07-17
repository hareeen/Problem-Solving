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

class planeSweep
{
private:
  int treeSize;
  vector<pi> tree;

public:
  planeSweep(const int &N)
  {
    treeSize = (1 << static_cast<int>(ceil(log2(static_cast<double>(N))) + 1));
    tree.clear();
    tree.resize(treeSize, pi(0, 0));
  }

  int update(int s, int e, int l, int r, int node, const int &diff)
  {
    if (r < s || e < l)
      return tree[node].first;

    if (l <= s && e <= r)
    {
      tree[node].second += diff;
    }
    else
    {
      update(s, (s + e) / 2, l, r, node * 2, diff);
      update((s + e) / 2 + 1, e, l, r, node * 2 + 1, diff);
    }

    if (tree[node].second != 0)
      return tree[node].first = e - s + 1;
    else
      return tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<tuple<int, bool, pi>> verticalSeg;
  for (int i = 0; i < N; i++)
  {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    verticalSeg.push_back(make_tuple(x1, true, pi(y1, y2)));
    verticalSeg.push_back(make_tuple(x2, false, pi(y1, y2)));
  }
  sort(iterall(verticalSeg));

  int ans = 0, last = -1, subans = 0;
  auto pS = planeSweep(65536);
  for (const auto &[xCorr, isStart, yRange] : verticalSeg)
  {
    if (last != xCorr && last != -1)
    {
      ans += subans * (xCorr - last);
      subans = 0;
    }
    auto res = pS.update(0, 30000, yRange.first, yRange.second - 1, 1, (isStart ? 1 : -1));
    subans = res;
    last = xCorr;
  }

  cout << ans << endl;

  return 0;
}