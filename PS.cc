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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, L;
  cin >> N >> L;

  vector<int> arr(N);
  for (int i = 0; i < N; i++) cin >> arr[i];
  while (arr.size() % L) arr.push_back(numeric_limits<int>::max());

  vector<int> fmin, rmin;

  for (int i = 0; i < N; i += L) {
    int tmp = numeric_limits<int>::max();
    for (int j = 0; j < L; j++) {
      tmp = min(tmp, arr[i + j]);
      fmin.push_back(tmp);
    }
  }

  for (int i = 0; i < N; i += L) {
    int tmp = numeric_limits<int>::max();
    for (int j = 0; j < L; j++) {
      tmp = min(tmp, arr[arr.size() - i - j - 1]);
      rmin.push_back(tmp);
    }
  }
  reverse(iterall(rmin));

  for (int i = 0; i < N; i++) {
    if (i - L + 1 < 0)
      cout << fmin[i] << " ";
    else
      cout << min(fmin[i], rmin[i - L + 1]) << " ";
  }
  cout << endl;

  return 0;
}