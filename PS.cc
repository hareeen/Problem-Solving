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
    tree.resize(131072 + 128);
  }
  i64 init(int s, int e, int node, vector<i64> &arr) {
    if (s == e)
      return tree[node] = arr[s];
    else
      return tree[node] = init(s, (s + e) / 2, node * 2, arr) +
                          init((s + e) / 2, e, node * 2 + 1, arr);
  }
  void update(int s, int e, int tar, int node, i64 diff) {
    if (s > tar || e < tar) return;
    if (s != e) {
      update(s, (s + e) / 2, tar, node * 2, diff);
      update((s + e) / 2 + 1, e, tar, node * 2 + 1, diff);
    }
    tree[node] += diff;
    return;
  }
  int query(int s, int e, int node, int rank) {
    if (s == e) return s;
    auto lft = tree[node * 2];
    if (rank <= lft)
      return query(s, (s + e) / 2, node * 2, rank);
    else
      return query((s + e) / 2 + 1, e, node * 2 + 1, rank - lft);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, K;
  cin >> N >> K;

  auto target_rank = (K + 1) / 2;
  auto sT = segTree();

  vector<int> arr;
  for (int i = 0; i < K; i++) {
    int t;
    cin >> t;
    arr.push_back(t);
    sT.update(1, 65536, t + 1, 1, 1);
  }

  i64 ans = 0;
  for (int i = K + 1; i <= N; i++) {
    ans += (static_cast<i64>(sT.query(1, 65536, 1, target_rank)) - 1);
    // cout << sT.query(1, 65536, 1, target_rank) << endl;

    int t;
    cin >> t;
    arr.push_back(t);
    sT.update(1, 65536, t + 1, 1, 1);
    sT.update(1, 65536, arr[i - K - 1] + 1, 1, -1);
  }

  cout << ans + static_cast<i64>(sT.query(1, 65536, 1, target_rank)) - 1
       << endl;
  return 0;
}