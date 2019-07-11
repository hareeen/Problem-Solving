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

  vector<vector<int>> arr(4);
  for (int i = 0; i < N; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    arr[0].push_back(a);
    arr[1].push_back(b);
    arr[2].push_back(c);
    arr[3].push_back(d);
  }

  vector<int> leftArr, rightArr;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      leftArr.push_back(arr[0][i] + arr[1][j]);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      rightArr.push_back(arr[2][i] + arr[3][j]);
  sort(iterall(rightArr));

  i64 res = 0;
  for (const int &el : leftArr)
  {
    auto bsearch = equal_range(iterall(rightArr), -el);
    res += distance(bsearch.first, bsearch.second);
  }

  cout << res << endl;

  return 0;
}