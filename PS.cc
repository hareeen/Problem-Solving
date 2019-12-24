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

const i64 mod = 1e9 + 7;

void solve(i64 nd, i64 par, vector<pli> &sol,
           const vector<vector<pli>> &graph) {
  if (par != -1 && graph[nd].size() == 1) {
    sol[nd] = {0, 0};
    return;
  }
  for (auto [th, we] : graph[nd]) {
    if (th == par) continue;
    solve(th, nd, sol, graph);
    sol[nd].first += (sol[th].first + 1) * we;
    sol[nd].first %= mod;
    sol[nd].second +=
        (((sol[th].first + 1) * (sol[th].first + 1)) % mod) * we * we;
    sol[nd].second %= mod;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  i64 N;
  cin >> N;

  vector<vector<pli>> graph(N);
  for (int i = 0; i < N - 1; i++) {
    i64 u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    graph[u].push_back({v, w});
    graph[v].push_back({u, w});
  }

  vector<pli> sol(N);
  solve(0, -1, sol, graph);

  i64 ans = 0;
  for (auto [as, bs] : sol) {
    // cout << as << " " << bs << endl;
    i64 tmp = ((as * as) % mod - bs);
    if (tmp % 2) tmp += mod;
    ans += (tmp / 2 + as);
    ans %= mod;
  }

  cout << (ans + mod) % mod << endl;
  return 0;
}