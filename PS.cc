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

  int N, M;
  cin >> N;
  cin >> M;

  vector<vector<int>> inc(N, vector<int>(N, INT_MAX / 2));
  for (int i = 0; i < N; i++)
    inc[i][i] = 0;

  for (int i = 0; i < M; i++)
  {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    inc[u][v] = min(inc[u][v], w);
  }

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      for (int k = 0; k < N; k++)
        inc[k][j] = min(inc[k][j], inc[k][i] + inc[i][j]);

  for (const auto &vec : inc)
  {
    for (const auto &el : vec)
      cout << (el >= INT_MAX / 2 ? 0 : el) << " ";
    cout << '\n';
  }

  return 0;
}