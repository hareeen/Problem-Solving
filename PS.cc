#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <unordered_set>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

#define M_iterall(container) container.begin(), container.end()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M;
  cin >> N >> M;
  vector<int> six, one;
  for (int i = 0; i < M; i++)
  {
    int a, b;
    cin >> a >> b;
    six.push_back(a);
    one.push_back(b);
  }

  int ms = *min_element(M_iterall(six));
  int os = *min_element(M_iterall(one));
  vector<int> ret;
  for (int i = 0; i < 6; i++)
    ret.push_back((N + i) / 6 * min(ms, os * 6) + (N + i) % 6 * os);
  cout << *min_element(M_iterall(ret)) << endl;

  return 0;
}
