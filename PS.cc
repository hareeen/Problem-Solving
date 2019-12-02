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

class segTree {
 private:
  vector<int> tree;

 public:
  segTree() { tree.resize(1048576); }

  void update(int s, int e, int nd, const int t, const int d) {
    if (t < s || e < t)
      return;
    else if (s != e) {
      update(s, (s + e) / 2, nd * 2, t, d);
      update((s + e) / 2 + 1, e, nd * 2 + 1, t, d);
    }
    tree[nd] += d;
  }

  int query(int s, int e, int nd, const int l, const int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r)
      return tree[nd];
    else
      return query(s, (s + e) / 2, nd * 2, l, r) +
             query((s + e) / 2 + 1, e, nd * 2 + 1, l, r);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<int> arr(N);
  vector<pi> wI;
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
    wI.push_back({arr[i], i});
  }

  sort(iterall(wI));

  int cnt = 0, lval = -1;
  for (auto [val, idx] : wI) {
    if (lval != val) cnt++;
    arr[idx] = cnt;
    lval = val;
  }

  auto sT = segTree();
  for (int i = 0; i < N; i++) {
    cout << i - sT.query(1, N, 1, 1, arr[i]) + 1 << '\n';
    sT.update(1, N, 1, arr[i], 1);
  }

  return 0;
}