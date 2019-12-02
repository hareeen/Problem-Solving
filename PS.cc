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
  segTree() { tree.resize(1048576, numeric_limits<int>::max()); }

  void update(int s, int e, int nd, const int t, const int nb) {
    if (t < s || e < t)
      return;
    else if (s == e)
      tree[nd] = nb;
    else {
      update(s, (s + e) / 2, nd * 2, t, nb);
      update((s + e) / 2 + 1, e, nd * 2 + 1, t, nb);
      tree[nd] = min(tree[nd * 2], tree[nd * 2 + 1]);
    }
  }

  int query(int s, int e, int nd, const int l, const int r) {
    if (r < s || e < l) return numeric_limits<int>::max();
    if (l <= s && e <= r)
      return tree[nd];
    else
      return min(query(s, (s + e) / 2, nd * 2, l, r),
                 query((s + e) / 2 + 1, e, nd * 2 + 1, l, r));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<ti> stud(N);
  for (int i = 1; i <= N; i++) {
    int t;
    cin >> t;
    get<0>(stud[--t]) = i;
  }
  for (int i = 1; i <= N; i++) {
    int t;
    cin >> t;
    get<1>(stud[--t]) = i;
  }
  for (int i = 1; i <= N; i++) {
    int t;
    cin >> t;
    get<2>(stud[--t]) = i;
  }

  sort(iterall(stud));

  int ans = 0;
  auto sT = segTree();
  for (int i = 0; i < N; i++) {
    // cout << get<1>(stud[i]) << " " << get<2>(stud[i]) << endl;
    if (sT.query(1, N, 1, 1, get<1>(stud[i])) > get<2>(stud[i])) ans++;
    sT.update(1, N, 1, get<1>(stud[i]), get<2>(stud[i]));
  }

  cout << ans << endl;

  return 0;
}