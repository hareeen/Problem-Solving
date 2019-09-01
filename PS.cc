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

bool dfs(int here, vector<bool> &vst, vector<int> &match,
         vector<vector<int>> &grp) {
  if (vst[here]) return false;
  vst[here] = true;
  for (auto there : grp[here]) {
    if (match[there] == -1 || dfs(match[there], vst, match, grp)) {
      match[there] = here;
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> grp(N + M);

  for (int i = 0; i < N; i++) {
    int sz;
    cin >> sz;
    for (int j = 0; j < sz; j++) {
      int k;
      cin >> k;
      k += (N - 1);
      grp[i].push_back(k);
      grp[k].push_back(i);
    }
  }

  int ans = 0;
  vector<int> match(N + M, -1);
  for (int i = 0; i < N; i++) {
    vector<bool> vst(N);
    if (dfs(i, vst, match, grp)) ans++;
  }

  cout << ans << endl;

  return 0;
}