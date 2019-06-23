#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define M_iterall(container) container.begin(), container.end()

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

  int N, K;
  vector<int> coins;
  cin >> N >> K;
  for (int i = 0; i < N; i++)
  {
    int tmp;
    cin >> tmp;
    coins.push_back(tmp);
  }

  reverse(M_iterall(coins));
  int res = 0;
  for (const auto &el : coins)
    res += K / el, K %= el;
  cout << res << endl;

  return 0;
}
