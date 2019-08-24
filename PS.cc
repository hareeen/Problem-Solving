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

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N;
  cin >> N;

  vector<pi> vec;
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    vec.push_back({b, a});
  }

  sort(iterall(vec));

  int laste = 0, ans = 0;
  for (auto [e, s] : vec)
    if (laste <= s) laste = e, ans++;

  cout << ans << endl;

  return 0;
}