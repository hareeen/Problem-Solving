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

bool comp(const pi &left, const pi &right)
{
  return left.first <= right.first && left.second <= right.second;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<pi> arr;
  for (int i = 0; i < N; i++)
  {
    int a, b;
    cin >> a >> b;
    if (a < b)
      swap(a, b);
    arr.push_back(pi(a, b));
  }

  sort(iterall(arr));

  vector<int> dp(1, 1);

  for (int i = 1; i < N; i++)
  {
    int ret = 1;
    for (int j = 0; j < i; j++)
      if (arr[j].second <= arr[i].second)
        ret = max(ret, dp[j] + 1);
    dp.push_back(ret);
  }

  cout << *max_element(iterall(dp)) << endl;

  return 0;
}