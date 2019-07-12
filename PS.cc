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

int dx[4] = {1, 0, 0, -1}, dy[4] = {0, -1, 1, 0};

int dfs(const int &N, vector<vector<int>> &arr, vector<vector<int>> &check, int corr1, int corr2)
{
  if (check[corr1][corr2] != 1)
    return check[corr1][corr2];
  for (int i = 0; i < 4; i++)
  {
    int c1_new = corr1 + dx[i], c2_new = corr2 + dy[i];
    if (0 <= c1_new && c1_new < N && 0 <= c2_new && c2_new < N && arr[c1_new][c2_new] > arr[corr1][corr2])
      check[corr1][corr2] = max(check[corr1][corr2], dfs(N, arr, check, c1_new, c2_new) + 1);
  }
  return check[corr1][corr2];
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<vector<int>> arr(N);
  vector<vector<int>> check(N, vector<int>(N, 1));
  vector<pair<int, pi>> cor;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      arr[i].push_back(t);
      cor.push_back(make_pair(t, pi(i, j)));
    }
  }

  sort(iterall(cor));
  reverse(iterall(cor));

  for (const auto &[height, corr] : cor)
    if (check[corr.first][corr.second] == 1)
      dfs(N, arr, check, corr.first, corr.second);

  int ret = INT_MIN;
  for (const auto &subarr : check)
    for (const auto &el : subarr)
      ret = max(ret, el);

  cout << ret << '\n';
  return 0;
}