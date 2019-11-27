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
  vector<pi> tree;

 public:
  segTree() {
    tree.clear();
    tree.resize(262144 + 1);
  }
  pi init(int s, int e, int node, const vector<int> &arr) {
    if (s == e)
      return tree[node] = {arr[s], s};
    else
      return tree[node] = min(init(s, (s + e) / 2, node * 2, arr),
                              init((s + e) / 2 + 1, e, node * 2 + 1, arr));
  }
  pi update(int s, int e, int node, const int t, const int n) {
    if (e < t || t < s) return tree[node];
    if (s == e)
      return tree[node] = {n, t};
    else
      return tree[node] = min(update(s, (s + e) / 2, node * 2, t, n),
                              update((s + e) / 2 + 1, e, node * 2 + 1, t, n));
  }
  pi query(int s, int e, int node, const int l, const int r) {
    if (s > r || e < l) return {numeric_limits<int>::max(), -1};
    if (l <= s && e <= r)
      return tree[node];
    else
      return min(query(s, (s + e) / 2, node * 2, l, r),
                 query((s + e) / 2 + 1, e, node * 2 + 1, l, r));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<int> arr(N + 1);
  for (int i = 1; i <= N; i++) cin >> arr[i];

  int Q;
  cin >> Q;

  auto mT = segTree();
  mT.init(1, N, 1, arr);

  for (int i = 0; i < Q; i++) {
    int type, a, b;
    cin >> type >> a >> b;
    if (type == 1) mT.update(1, N, 1, a, b);
    if (type == 2) cout << mT.query(1, N, 1, a, b).second << '\n';
  }
  return 0;
}