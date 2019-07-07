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

  int N;
  cin >> N;
  deque<int> deq;
  for (int i = 0; i < N; i++)
  {
    string cmd;
    cin >> cmd;
    if (cmd == "push_front")
    {
      int a;
      cin >> a;
      deq.push_front(a);
    }
    if (cmd == "push_back")
    {
      int a;
      cin >> a;
      deq.push_back(a);
    }
    if (cmd == "pop_front")
    {
      if (deq.empty())
        cout << -1 << '\n';
      else
        cout << deq.front() << '\n', deq.pop_front();
    }
    if (cmd == "pop_back")
    {
      if (deq.empty())
        cout << -1 << '\n';
      else
        cout << deq.back() << '\n', deq.pop_back();
    }
    if (cmd == "size")
    {
      cout << deq.size() << '\n';
    }
    if (cmd == "empty")
    {
      cout << static_cast<int>(deq.empty()) << '\n';
    }
    if (cmd == "front")
    {
      if (deq.empty())
        cout << -1 << '\n';
      else
        cout << deq.front() << '\n';
    }
    if (cmd == "back")
    {
      if (deq.empty())
        cout << -1 << '\n';
      else
        cout << deq.back() << '\n';
    }
  }

  return 0;
}
