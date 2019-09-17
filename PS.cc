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
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

class segTree {
 private:
  vector<int> tree;

 public:
  segTree(int N) {
    tree.clear();
    tree.resize(N);
  }
  int init(int s, int e, int node, const vector<int> &arr) {
    if (s == e)
      return tree[node] = arr[s];
    else
      return tree[node] = init(s, (s + e) / 2, node * 2, arr) +
                          init((s + e) / 2 + 1, e, node * 2 + 1, arr);
  }
  void update(int s, int e, int node, const int tar, const int diff) {
    if (tar < s || e < tar) return;
    tree[node] -= diff;
    if (s != e) {
      update(s, (s + e) / 2, node * 2, tar, diff);
      update((s + e) / 2 + 1, e, node * 2 + 1, tar, diff);
    }
  }
  int query(int s, int e, int node, const int l, const int r) {
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

  N++;

  vector<int> st(N), fi(N);
  for (int i = 1; i < N; i++) cin >> st[i];
  for (int i = 1; i < N; i++) cin >> fi[i];

  for (int i = 1; i < N; i++) st[i]--, fi[i]--;

  vector<int> mp(N);
  for (int i = 1; i < N; i++) mp[st[i]] = i;
  for (int i = 1; i < N; i++) fi[i] = mp[fi[i]];

  vector<int> mp2(N);
  for (int i = 1; i < N; i++) mp2[fi[i]] = i;

  int ans = 0;
  auto sT = segTree(262144);
  for (int i = 1; i < N; i++) {
    ans += (mp2[i] - sT.query(1, N, 1, 1, mp2[i]) - 1);
    sT.update(1, N, 1, mp2[i], 1);
    ans %= 2;
  }

  cout << (ans ? "Impossible" : "Possible") << endl;

  return 0;
}