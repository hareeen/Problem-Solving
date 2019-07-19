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

  int N;
  cin >> N;

  vector<pi> polygon;
  for (int i = 0; i < N; i++)
  {
    int x, y;
    cin >> x >> y;
    polygon.push_back({x, y});
  }

  while (!(polygon[0].first == polygon[1].first && polygon[0].second < 0 && polygon[1].second > 0))
    rotate(polygon.begin(), polygon.begin() + 1, polygon.end());

  int last = INT_MAX;
  int pairCount = 0;
  vector<ti> pairs;
  for (int i = 0; i < N; i += 2)
  {
    int x = polygon[i].first;
    int y1 = polygon[i].second, y2 = polygon[i + 1].second;
    if (y1 < y2)
      swap(y1, y2);
    if (y1 > 0 && y2 < 0)
    {
      if (last == INT_MAX)
        last = x;
      else
      {
        if (last > x)
          swap(last, x);
        pairs.push_back({last, 1, pairCount});
        pairs.push_back({x, -1, pairCount});
        pairCount++;
        last = INT_MAX;
      }
    }
  }

  sort(iterall(pairs));

  int openPair = 0;
  int lastPair = -1;
  int ans1 = 0, ans2 = 0;
  for (const auto &[x, isOpen, pairNum] : pairs)
  {
    if (isOpen == -1 && openPair == 1)
      ans1++;
    if (pairNum == lastPair)
      ans2++;
    openPair += isOpen;
    lastPair = pairNum;
  }

  cout << ans1 << " " << ans2 << endl;

  return 0;
}