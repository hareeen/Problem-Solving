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
  deque<int> deq;
  for (int i = 0; i < N; i++)
    deq.push_back(i + 1);
  int ret = 0;
  for (int i = 0; i < M; i++)
  {
    int target;
    cin >> target;
    int _s = 0;
    while (deq.front() != target)
    {
      _s++;
      int tmp = deq.front();
      deq.pop_front();
      deq.push_back(tmp);
    }
    ret += min(_s, static_cast<int>(deq.size()) - _s);
    deq.pop_front();
  }
  cout << ret << endl;
  
  return 0;
}
