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

void process() {
  i64 _a, _b, _i, n;
  cin >> _a >> _b >> _i >> n;

  __int128 a = _a, b = _b, ii = _i - 1;
  vector<__int128> vec;
  vec.push_back(10);
  for (__int128 i = 2; i < ii; i *= 2)
    vec.push_back((vec.back() * vec.back()) % b);

  int idx = 0;
  while (ii) {
    if (ii % 2) a = (a * vec[idx]) % b;
    ii /= 2, idx++;
  }

  for (int i = 0; i < n; i++) {
    a *= 10;
    cout << static_cast<i64>(a / b);
    a %= b;
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int T;
  cin >> T;
  for (int i = 0; i < T; i++) process();

  return 0;
}