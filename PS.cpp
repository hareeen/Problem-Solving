#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

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
  vector<int> v(10001);
  cin >> N;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    v[t]++;
  }
  for (int i = 1; i <= 10000; i++)
    for (int j = 0; j < v[i]; j++)
      cout << i << '\n';
  return 0;
}
