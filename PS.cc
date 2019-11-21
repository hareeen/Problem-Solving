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

void createSieve(int N, vector<bool> &sieve) {
  sieve.clear();
  sieve.resize(N + 1, true);
  sieve[0] = sieve[1] = false;
  for (int i = 2; i * i <= N; i++) {
    if (!sieve[i]) continue;
    for (int j = 2 * i; j <= N; j += i) sieve[j] = false;
  }
}

bool dfs(int here, vector<bool> &vst, vector<int> &match,
         const vector<vector<int>> &graph) {
  if (vst[here]) return false;
  vst[here] = true;
  for (auto there : graph[here]) {
    if (there == 0 || there == match[0]) continue;
    if (match[there] == -1 || dfs(match[there], vst, match, graph)) {
      match[there] = here;
      return true;
    }
  }
  return false;
}

int bmatch(const int N, int target, vector<bool> &vst, vector<int> &match,
           const vector<vector<int>> &graph, const vector<int> &dict) {
  int ret = 2;
  match[0] = target;
  match[target] = 0;
  for (int i = 1; i < N; i++) {
    if (dict[i] % 2) continue;
    vst = vector<bool>(N);
    if (i != target && dfs(i, vst, match, graph)) ret += 2;
  }

  // cout << target << " " << ret << endl;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<bool> sieve;
  createSieve(2000, sieve);

  int N;
  cin >> N;

  vector<int> dict(N);
  for (int i = 0; i < N; i++) cin >> dict[i];

  vector<vector<int>> graph(N);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (sieve[dict[i] + dict[j]]) graph[i].push_back(j);

  vector<int> success;
  for (int i = 1; i < N; i++) {
    if (!sieve[dict[0] + dict[i]]) continue;

    vector<bool> vst(N);
    vector<int> match(N, -1);

    if (bmatch(N, i, vst, match, graph, dict) == N) success.push_back(dict[i]);
  }

  sort(iterall(success));
  if (success.size())
    copy(iterall(success), ostream_iterator<int>(cout, " "));
  else
    cout << -1;
  cout << endl;

  return 0;
}