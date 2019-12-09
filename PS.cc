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

i64 su(i64 l, i64 r) {
  if (l > r) return 0;
  if ((r - l + 1) % 2)
    return (l + r) / 2 * (r - l + 1);
  else
    return (r - l + 1) / 2 * (l + r);
}
i64 su(pli p) { return su(p.first, p.second); }

pli split(pli p, int len) {
  // i64 len = static_cast<i64>(le);
  i64 f = (p.first - p.second * su(1, len - 1)) / len;
  i64 left = f * ((len + 1) / 2) + su(1, (len + 1) / 2 - 1) * p.second;
  // cout << f << " " << left << endl;
  return {left, p.first - left};
}

bool intersect(int s, int e, int l, int r) { return !(e < l || r < s); }

i64 tot(int s, int e, int l, int r) {
  if (!intersect(s, e, l, r))
    return 0;
  else
    return su(max(1, s - l + 1), min(e - l + 1, r - l + 1));
}

class segTree {
 private:
  vector<i64> tree;
  vector<pli> lazy;

 public:
  segTree() {
    tree.clear();
    tree.resize(262144 + 1);
    lazy.clear();
    lazy.resize(262144 + 1);
  }
  i64 init(int s, int e, int nd, const vector<i64> &arr) {
    if (s == e)
      return tree[nd] = arr[s];
    else
      return tree[nd] = init(s, (s + e) / 2, nd * 2, arr) +
                        init((s + e) / 2 + 1, e, nd * 2 + 1, arr);
  }
  void propagate(int s, int e, int nd) {
    if (lazy[nd] == pli(0, 0)) return;
    tree[nd] += lazy[nd].first;

    if (s != e) {
      auto [pl, pr] = split(lazy[nd], e - s + 1);
      // cout << lazy[nd].first << " " << lazy[nd].second << " " << e - s + 1
      //      << " " << pl << " " << pr << endl;
      lazy[nd * 2].first += pl;
      lazy[nd * 2].second += lazy[nd].second;
      lazy[nd * 2 + 1].first += pr;
      lazy[nd * 2 + 1].second += lazy[nd].second;
    }

    lazy[nd] = {0, 0};
  }
  void update(int s, int e, int nd, const int l, const int r) {
    propagate(s, e, nd);
    if (!intersect(s, e, l, r)) return;
    if (l <= s && e <= r) {
      lazy[nd].first += tot(s, e, l, r);
      lazy[nd].second++;
      propagate(s, e, nd);
      return;
    }
    update(s, (s + e) / 2, nd * 2, l, r);
    update((s + e) / 2 + 1, e, nd * 2 + 1, l, r);
    tree[nd] = tree[nd * 2] + tree[nd * 2 + 1];
  }
  i64 query(int s, int e, int nd, const int l, const int r) {
    propagate(s, e, nd);
    if (!intersect(s, e, l, r))
      return 0;
    else if (l <= s && e <= r)
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

  vector<i64> arr(N + 1);
  for (int i = 1; i <= N; i++) cin >> arr[i];

  auto sT = segTree();
  sT.init(1, N, 1, arr);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int t;
    cin >> t;

    if (t == 1) {
      int l, r;
      cin >> l >> r;
      sT.update(1, N, 1, l, r);
    } else {
      int x;
      cin >> x;
      cout << sT.query(1, N, 1, x, x) << '\n';
    }
  }

  return 0;
}