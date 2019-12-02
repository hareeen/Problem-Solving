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

const int inf = numeric_limits<int>::min() / 3;

pi merge(const pi a, const pi b) {
  vector<int> v;
  v.push_back(a.first);
  v.push_back(a.second);
  v.push_back(b.first);
  v.push_back(b.second);
  sort(iterall(v), greater<int>());
  return {v[0], v[1]};
}

class segTree {
 private:
  vector<pi> tree;

 public:
  segTree() { tree.resize(262144, {inf, inf}); }

  pi init(int s, int e, int nd, const vector<int> &arr) {
    if (s == e)
      return tree[nd] = {arr[s], inf};
    else
      return tree[nd] = merge(init(s, (s + e) / 2, nd * 2, arr),
                              init((s + e) / 2 + 1, e, nd * 2 + 1, arr));
  }

  void update(int s, int e, int nd, const int t, const int nb) {
    if (t < s || e < t)
      return;
    else if (s == e)
      tree[nd] = {nb, inf};
    else {
      update(s, (s + e) / 2, nd * 2, t, nb);
      update((s + e) / 2 + 1, e, nd * 2 + 1, t, nb);
      tree[nd] = merge(tree[nd * 2], tree[nd * 2 + 1]);
    }
  }

  pi query(int s, int e, int nd, const int l, const int r) {
    if (r < s || e < l) return {inf, inf};
    if (l <= s && e <= r)
      return tree[nd];
    else
      return merge(query(s, (s + e) / 2, nd * 2, l, r),
                   query((s + e) / 2 + 1, e, nd * 2 + 1, l, r));
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

  auto sT = segTree();
  sT.init(1, N, 1, arr);

  int Q;
  cin >> Q;

  auto ss = [](pi p) -> int { return p.first + p.second; };
  for (int i = 0; i < Q; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1)
      sT.update(1, N, 1, a, b);
    else
      cout << ss(sT.query(1, N, 1, a, b)) << '\n';
  }

  return 0;
}