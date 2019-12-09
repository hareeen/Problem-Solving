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

class disjointSet {
 private:
  vector<int> uf, ng;

 public:
  disjointSet(int N) {
    uf.clear();
    uf.resize(N + 1);
    for (int i = 0; i <= N; i++) uf[i] = i;

    ng.clear();
    ng.resize(N + 1, 1);
  }
  int find(int x) {
    if (x == uf[x])
      return x;
    else
      return uf[x] = find(uf[x]);
  }
  bool sameset(int u, int v) { return find(u) == find(v); }
  void merge(int u, int v) {
    if (sameset(u, v)) return;
    ng[find(v)] += ng[find(u)];
    uf[find(u)] = uf[find(v)];
  }
  bool commit(int u) {
    bool ret = ng[find(u)];
    if (ret) ng[find(u)]--;
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, L;
  cin >> N >> L;

  vector<pi> arr(N);
  for (int i = 0; i < N; i++) cin >> arr[i].first >> arr[i].second;

  auto dS = disjointSet(L);
  for (auto [a, b] : arr) {
    dS.merge(a, b);
    cout << ((dS.commit(a) || dS.commit(b)) ? "LADICA" : "SMECE") << '\n';
  }
  
  return 0;
}