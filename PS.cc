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

  vector<vector<int>> map(101, vector<int>(101));
  for (int i = 1; i <= N; i++)
  {
    int sx, sy, w, h;
    cin >> sx >> sy >> w >> h;
    for (int x = 0; x < w; x++)
      for (int y = 0; y < h; y++)
        map[sx + x][sy + y] = i;
  }

  vector<int> ans(N + 1);
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j <= 100; j++)
      ans[map[i][j]]++;

  for (int i = 1; i <= N; i++)
    cout << ans[i] << '\n';

  return 0;
}