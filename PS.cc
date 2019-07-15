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

  vector<pi> line;
  for (int i = 0; i < N; i++)
  {
    int l, r;
    cin >> l >> r;
    if (l > r)
      swap(l, r);
    line.push_back(pi(l, r));
  }

  sort(iterall(line));

  int ans = 0;
  int left = line[0].first, right = line[0].second;
  for (int i = 1; i < N; i++)
  {
    if (left <= line[i].first && line[i].first <= right)
      right = max(right, line[i].second);
    else
      ans += (right - left), left = line[i].first, right = line[i].second;
  }

  cout << ans + right - left << endl;
  return 0;
}