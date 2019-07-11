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

#define iterall(container) container.begin(), container.end()

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

  int N;
  cin >> N;

  priority_queue<int> pq;
  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    if (t == 0)
    {
      if (!pq.empty())
        cout << pq.top() << '\n', pq.pop();
      else
        cout << 0 << '\n';
    }
    else
      pq.push(t);
  }

  return 0;
}