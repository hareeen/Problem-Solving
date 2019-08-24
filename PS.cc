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

  stack<int> stk;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    if (s == "push") {
      int x;
      cin >> x;
      stk.push(x);
    }
    if (s == "pop") {
      if (stk.empty()) {
        cout << -1 << '\n';
      } else {
        cout << stk.top() << '\n';
        stk.pop();
      }
    }
    if (s == "size") cout << stk.size() << '\n';
    if (s == "empty") cout << stk.empty() << '\n';
    if (s == "top") cout << (stk.empty() ? -1 : stk.top()) << '\n';
  }

  return 0;
}