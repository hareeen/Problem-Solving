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

  i64 N;
  cin >> N;

  vector<bool> isPrime(1000001, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i <= 100; i++)
  {
    if (isPrime[i])
      for (int j = 2 * i; j <= 1000000; j += i)
        isPrime[j] = false;
  }

  i64 res = 1;
  for (i64 p = 2; p * p <= N; p++)
  {
    if (isPrime[p] && N % p == 0)
    {
      N /= p;
      while (N % p == 0)
        res *= p, N /= p;
      res *= (p - 1);
    }
  }
  if (N != 1)
    res *= (N - 1);

  cout << res << endl;

  return 0;
}