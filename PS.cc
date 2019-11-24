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

i64 LLmin_half = numeric_limits<i64>::min() / 2;

class segmentTree {
 private:
  vector<i64> treeL, treeR, tree, su;

 public:
  segmentTree() {
    treeL.resize(262144 + 1);
    treeR.resize(262144 + 1);
    tree.resize(262144 + 1);
    su.resize(262144 + 1);
  }
  void init(int s, int e, int node, const vector<i64> &arr) {
    if (s == e) {
      treeL[node] = treeR[node] = tree[node] = su[node] = arr[s];
      return;
    }
    init(s, (s + e) / 2, node * 2, arr);
    init((s + e) / 2 + 1, e, node * 2 + 1, arr);
    treeL[node] = max(treeL[node * 2], treeL[node * 2 + 1] + su[node * 2]);
    treeR[node] = max(treeR[node * 2 + 1], treeR[node * 2] + su[node * 2 + 1]);
    tree[node] = max({tree[node * 2], tree[node * 2 + 1],
                      treeR[node * 2] + treeL[node * 2 + 1]});
    su[node] = su[node * 2] + su[node * 2 + 1];
    return;
  }
  tuple<i64, i64, i64, i64> query(int s, int e, int node, const int l,
                                  const int r) {
    if (r < s || e < l)
      return {LLmin_half, LLmin_half, LLmin_half, 0};
    else if (l <= s && e <= r)
      return {treeL[node], treeR[node], tree[node], su[node]};
    else {
      auto [ll, lr, lt, ls] = query(s, (s + e) / 2, node * 2, l, r);
      auto [rl, rr, rt, rs] = query((s + e) / 2 + 1, e, node * 2 + 1, l, r);
      return {max(ll, ls + rl), max(rr, rs + lr), max({lt, rt, lr + rl}),
              ls + rs};
    }
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

  auto sT = segmentTree();
  sT.init(1, N, 1, arr);

  int Q;
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    cout << get<2>(sT.query(1, N, 1, l, r)) << '\n';
  }

  return 0;
}