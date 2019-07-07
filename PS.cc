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

  int K;
  stack<int> stk;
  cin >> K;
  for (int i = 0; i < K; i++)
  {
    int a;
    cin >> a;
    if (a == 0)
      stk.pop();
    else
      stk.push(a);
  }

  int _s = 0;
  while (!stk.empty())
    _s += stk.top(), stk.pop();
  cout << _s << endl;

  return 0;
}
