#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using d64 = long double;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

#define iterall(cont) cont.begin(), cont.end()
#define prec(n) setprecision(n) << fixed

inline i64 smod(i64 a, i64 m) { return ((a % m) + m) % m; }
inline __int128 smod(__int128 a, __int128 m) { return ((a % m) + m) % m; }

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

__int128 getInv(__int128 a, __int128 b) {
  if (a <= 1)
    return a;
  else if (a > b)
    return getInv(smod(a, b), b);
  else
    return smod((-getInv(smod(b, a), a) * b + 1) / a, b);
}

i64 inv(i64 a, i64 b) { return gcd(a, b) == 1 ? getInv(a, b) : -1; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  i64 a, b;
  cin >> a >> b;
  cout << a - b << " " << inv(b, a) << endl;

  return 0;
}