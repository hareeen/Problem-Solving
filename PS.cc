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

d64 solve(int bit, int select, int idx, const int N, const vector<pi> &vecs) {
  if (idx == N) {
    if (select != N / 2) return numeric_limits<d64>::max();

    pi vecSum = {0, 0};
    auto it = vecs.begin();
    while (bit > 0) {
      vecSum.first += (((bit % 2) * 2 - 1) * it->first);
      vecSum.second += (((bit % 2) * 2 - 1) * it->second);
      bit /= 2;
      it++;
    }
    for (; it != vecs.end(); it++) {
      vecSum.first -= it->first;
      vecSum.second -= it->second;
    }

    auto x = static_cast<d64>(vecSum.first);
    auto y = static_cast<d64>(vecSum.second);
    return sqrt(x * x + y * y);
  }

  return min(solve(bit * 2, select, idx + 1, N, vecs),
             solve(bit * 2 + 1, select + 1, idx + 1, N, vecs));
}

void process() {
  int N;
  cin >> N;

  vector<pi> arr(N);
  for (int i = 0; i < N; i++) cin >> arr[i].first >> arr[i].second;

  cout << prec(12) << solve(0, 0, 0, N, arr) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int tc;
  cin >> tc;
  for (int i = 0; i < tc; i++) process();

  return 0;
}