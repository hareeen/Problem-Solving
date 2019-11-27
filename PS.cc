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

class mergeTree {
 private:
  vector<vector<int>> tree;

 public:
  mergeTree() {
    tree.clear();
    tree.resize(262144 + 1);
  }
  void init(int s, int e, int node, vector<int> &arr) {
    for (int i = s; i <= e; i++) tree[node].push_back(arr[i]);
    sort(iterall(tree[node]));
    if (s != e) {
      init(s, (s + e) / 2, node * 2, arr);
      init((s + e) / 2 + 1, e, node * 2 + 1, arr);
    }
  }
  int query(int s, int e, int node, const int l, const int r, const int k) {
    if (r < s || e < l)
      return 0;
    else if (l <= s && e <= r)
      return distance(upper_bound(iterall(tree[node]), k), tree[node].end());
    else
      return query(s, (s + e) / 2, node * 2, l, r, k) +
             query((s + e) / 2 + 1, e, node * 2 + 1, l, r, k);
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

  auto mT = mergeTree();
  mT.init(1, N, 1, arr);

  int l, r, k;
  cin >> l >> r >> k;

  auto last_ans = mT.query(1, N, 1, l, r, k);
  cout << last_ans << '\n';
  for (int i = 1; i < Q; i++) {
    cin >> l >> r >> k;
    l ^= last_ans, r ^= last_ans, k ^= last_ans;
    last_ans = mT.query(1, N, 1, l, r, k);
    cout << last_ans << '\n';
  }

  return 0;
}