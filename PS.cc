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

i64 calc_treeh(vector<int> &arr, int n)
{
  i64 s = 0;
  for (const auto &el : arr)
    s += max(0, el - n);
  return s;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  i64 N, M;
  cin >> N >> M;

  vector<int> arr;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    arr.push_back(t);
  }

  int l = 0, r = INT_MAX;
  while (l < r)
  {
    int mid = (l + r) / 2;
    i64 res = calc_treeh(arr, mid);
    if (res <= M)
      r = mid;
    else
      l = mid + 1;
  }

  for(int i=l+1;i>=l-1;i--) {
    if(calc_treeh(arr, i)>=M) {
      cout<<i<<endl;
      break;
    }
  }

  return 0;
}