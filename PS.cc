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
  vector<i64> tree;

 public:
  segTree() {
    tree.clear();
    tree.resize(262144 + 1);
  }
  i64 init(int s, int e, int node, const vector<i64> &arr) {
    if (s == e)
      return tree[node] = arr[s];
    else
      return tree[node] = init(s, (s + e) / 2, node * 2, arr) +
                          init((s + e) / 2 + 1, e, node * 2 + 1, arr);
  }
  void update(int s, int e, int node, const int t, const int d) {
    if (e < t || t < s) return;
    if (s != e) {
      update(s, (s + e) / 2, node * 2, t, d);
      update((s + e) / 2 + 1, e, node * 2 + 1, t, d);
    }
    tree[node] += d;
  }
  i64 query(int s, int e, int node, const int l, const int r) {
    if (e < l || r < s)
      return 0;
    else if (l <= s && e <= r)
      return tree[node];
    else
      return query(s, (s + e) / 2, node * 2, l, r) +
             query((s + e) / 2 + 1, e, node * 2 + 1, l, r);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<i64> arr(N + 1);
  for (int i = 1; i <= N; i++) cin >> arr[i];

  vector<i64> diffarr(N + 1);
  for (int i = 1; i <= N; i++) diffarr[i] = arr[i] - arr[i - 1];

  auto sT = segTree();
  sT.init(1, N, 1, diffarr);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int qtype;
    cin >> qtype;
    if (qtype == 1) {
      int s, e, d;
      cin >> s >> e >> d;
      sT.update(1, N, 1, s, d);
      if (e != N) sT.update(1, N, 1, e + 1, -d);
    } else {
      int x;
      cin >> x;
      cout << sT.query(1, N, 1, 1, x) << '\n';
    }
  }

  return 0;
}