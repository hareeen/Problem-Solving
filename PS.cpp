#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;
using i64 = long long;
using pi  = pair<int, int>;
using pli = pair<i64, i64>;
using ti  = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

bool contains(pli x, pli a, pli b) {
  return (a.first <= x.first) && (x.first <= b.first) && (a.second <= x.second) && (x.second <= b.second);
}

void sumOfZ(pli &target, pli st, pli ed, i64 acc, i64 num) {
  if(!contains(target, st, ed)) return;

  if(st == ed) {
    if(st == target) {
      cout << num << endl;
      exit(0);
    }
    return;
  }
  auto mid = pli((st.first + ed.first) / 2, (st.second + ed.second) / 2);
  sumOfZ(target, st, mid, acc / 4, num);
  sumOfZ(target, pli(mid.first + 1, st.second), pli(ed.first, mid.second), acc / 4, num + acc);
  sumOfZ(target, pli(st.first, mid.second + 1), pli(mid.first, ed.second), acc / 4, num + 2 * acc);
  sumOfZ(target, pli(mid.first + 1, mid.second + 1), ed, acc / 4, num + 3 * acc);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  i64 N, r, c;
  cin >> N >> r >> c;
  auto target = pli(c, r);
  auto sz     = static_cast<i64>(pow(2, N));

  sumOfZ(target, pli(0, 0), pli(sz - 1, sz - 1), sz * sz / 4, 0);
  return 0;
} // main
