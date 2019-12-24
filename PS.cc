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

const i64 mod = 1e9 + 7;
const int ed = 200001;

class segTree {
 private:
  vector<i64> tree;

 public:
  segTree() {
    tree.clear();
    tree.resize(524288 + 1);
  }

  void update(int s, int e, int nd, const int t, const i64 d) {
    if (t < s || e < t) return;
    if (s <= t && t <= e) tree[nd] += d, tree[nd] %= mod;
    if (s != e) {
      update(s, (s + e) / 2, nd * 2, t, d);
      update((s + e) / 2 + 1, e, nd * 2 + 1, t, d);
    }
  }

  i64 query(int s, int e, int nd, const int l, const int r) {
    if (l <= s && e <= r)
      return tree[nd] % mod;
    else if (e < l || r < s)
      return 0;
    else
      return (query(s, (s + e) / 2, nd * 2, l, r) +
              query((s + e) / 2 + 1, e, nd * 2 + 1, l, r)) %
             mod;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  auto sT1 = segTree(), sT2 = segTree();
  i64 su = 0, ans = 1;
  for (i64 i = 0; i < N; i++) {
    i64 k;
    cin >> k, k++;

    if (i != 0)
      ans *= ((2 * sT1.query(1, ed, 1, k, ed) - su -
               (2 * sT2.query(1, ed, 1, k, ed) - i) * k) %
              mod);
    su += k;
    su %= mod;
    ans %= mod;

    sT1.update(1, ed, 1, k, k);
    sT2.update(1, ed, 1, k, 1);
  }

  cout << (ans + mod) % mod << endl;
  return 0;
}