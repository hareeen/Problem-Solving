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

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  vector<bool> isPossible(d + c + 1);
  isPossible[0] = true;
  for (int i = 0; i <= d - a; i++)
    if (isPossible[i])
      isPossible[i + a] = isPossible[i + b] = isPossible[i + c] = true;

  cout << static_cast<int>(isPossible[d]) << endl;

  return 0;
}