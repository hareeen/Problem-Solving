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

void manachers(const string &s, vector<int> &res) {
  int N = s.length();
  res.clear();
  res.resize(N);

  int r = 0, p = 0;
  for (int i = 0; i < N; i++) {
    if (i <= r) res[i] = min(res[2 * p - i], r - i);
    while (i - res[i] - 1 >= 0 && i + res[i] + 1 < N &&
           s[i - res[i] - 1] == s[i + res[i] + 1])
      res[i]++;
    if (r < i + res[i]) r = i + res[i], p = i;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  string tmp;
  cin >> tmp;

  string st = "#";
  for (auto c : tmp) st.push_back(c), st.push_back('#');

  vector<int> mana;
  manachers(st, mana);

  cout << *max_element(iterall(mana)) << endl;
  return 0;
}