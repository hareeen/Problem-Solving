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

bool isPossible(const int &N, vector<vector<int>> &arr1, vector<vector<int>> &arr2, int qx, int qy)
{
  return arr1[0][qx] + arr1[1][qy] + arr2[0][N - qx + qy] + arr2[1][qx + qy] == 0;
}

void updQueen(const int &N, vector<vector<int>> &arr1, vector<vector<int>> &arr2, int qx, int qy, int diff)
{
  arr1[0][qx] += diff;
  arr1[1][qy] += diff;
  arr2[0][N - qx + qy] += diff;
  arr2[1][qx + qy] += diff;
  return;
}

i64 solve(const int &N, vector<vector<int>> &arr1, vector<vector<int>> &arr2, int qn)
{
  if (qn == N)
    return 1;

  i64 ret = 0;
  for (int j = 0; j < N; j++)
  {
    if (isPossible(N, arr1, arr2, qn, j))
    {
      updQueen(N, arr1, arr2, qn, j, 1);
      ret += solve(N, arr1, arr2, qn + 1);
      updQueen(N, arr1, arr2, qn, j, -1);
    }
  }

  return ret;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  auto arr1 = vector<vector<int>>(2, vector<int>(N, 0));
  auto arr2 = vector<vector<int>>(2, vector<int>(2 * N, 0));
  cout << solve(N, arr1, arr2, 0) << endl;

  return 0;
}