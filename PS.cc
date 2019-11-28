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

pli psum(const pli l, const pli r) { return {0, l.second + r.second}; }

class perSegTree {
 private:
  vector<vector<pli>> tree;

 public:
  perSegTree() {
    tree.clear();
    tree.resize(262144 + 1);
  }
  pli init(int s, int e, int node, const vector<i64> &arr) {
    if (s == e)
      tree[node].push_back({0, arr[s]});
    else
      tree[node].push_back(psum(init(s, (s + e) / 2, node * 2, arr),
                                init((s + e) / 2 + 1, e, node * 2 + 1, arr)));
    return tree[node].front();
  }
  void update(int s, int e, int node, const int t, const int d, const i64 cnt) {
    if (e < t || t < s) return;
    if (s != e) {
      update(s, (s + e) / 2, node * 2, t, d, cnt);
      update((s + e) / 2 + 1, e, node * 2 + 1, t, d, cnt);
    }
    tree[node].push_back({cnt, tree[node].back().second + d});
  }
  i64 query(int s, int e, int node, const int l, const int r, const i64 cnt) {
    if (e < l || r < s)
      return 0;
    else if (l <= s && e <= r) {
      auto iter = lower_bound(iterall(tree[node]),
                              pli(cnt, numeric_limits<i64>::max()));
      iter--;
      return iter->second;
    } else
      return query(s, (s + e) / 2, node * 2, l, r, cnt) +
             query((s + e) / 2 + 1, e, node * 2 + 1, l, r, cnt);
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

  auto psT = perSegTree();
  psT.init(1, N, 1, arr);

  int Q, qCount = 0;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int qType;
    cin >> qType;
    if (qType == 1) {
      int t, n;
      cin >> t >> n;
      qCount++;
      // cout << t << " " << psT.query(1, N, 1, t, t, qCount) << endl;
      psT.update(1, N, 1, t, n - psT.query(1, N, 1, t, t, qCount), qCount);
    } else {
      int k, s, e;
      cin >> k >> s >> e;
      cout << psT.query(1, N, 1, s, e, k) << '\n';
    }
  }

  return 0;
}