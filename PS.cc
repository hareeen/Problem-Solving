#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstring>

#define iterall(container) container.begin(), container.end()

using namespace std;

using i64 = long long;
using i128 = __int128;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

class segTree {
 private:
  vector<i64> tree;

 public:
  segTree() {
    tree.clear();
    tree.resize(262144 + 128);
  }
  i64 init(int s, int e, int node, vector<i64> &arr) {
    if (s == e)
      return tree[node] = arr[s];
    else
      return tree[node] = min(init(s, (s + e) / 2, node * 2, arr),
                              init((s + e) / 2 + 1, e, node * 2 + 1, arr));
  }
  void update(int s, int e, int tar, int node, i64 newel) {
    if (s > tar || e < tar) return;
    if (s != e) {
      update(s, (s + e) / 2, tar, node * 2, newel);
      update((s + e) / 2 + 1, e, tar, node * 2 + 1, newel);
      tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    } else
      tree[node] = newel;

    return;
  }
  i64 query(int s, int e, int l, int r, int node) {
    if (e < l || r < s)
      return numeric_limits<i64>::max();
    else if (l <= s && e <= r)
      return tree[node];
    else
      return min(query(s, (s + e) / 2, l, r, node * 2),
                 query((s + e) / 2 + 1, e, l, r, node * 2 + 1));
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<i64> arr(1);
  for (int i = 0; i < N; i++) {
    i64 t;
    cin >> t;
    arr.push_back(t);
  }

  auto sT = segTree();
  sT.init(1, N, 1, arr);

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int m, a, b;
    cin >> m >> a >> b;
    if (m == 1)
      sT.update(1, N, a, 1, b);
    else
      cout << sT.query(1, N, a, b, 1) << '\n';
  }

  return 0;
}