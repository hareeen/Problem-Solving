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

  string s;
  cin >> s;
  reverse(iterall(s));

  int i = 0, io = 0, ioi = 0, ioj = 0, ioio = 0;
  for (auto ch : s) {
    if (ch == 'O') {
      if (i > 0)
        i--, io++;
      else if (ioi > 0)
        io += 2, ioio++, ioi--;
    } else if (ch == 'I') {
      if (io > 0)
        io--, ioi++;
      else
        i++;
    } else {
      if (io > 0)
        io--, ioj++;
      else if (ioi > 0)
        ioi--, ioj++, i++;
    }
    ioio = min(ioio, io / 2);
  }

  cout << ioi + ioj + ioio << endl;

  return 0;
}