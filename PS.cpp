#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

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
  int to_push = 1;
  cin >> N;
  stack<int> stk;
  vector<bool> output;
  for (int i = 0; i < N; i++)
  {
    int target;
    cin >> target;
    if (to_push <= target)
    {
      int diff = target - to_push;
      for (int j = 0; j <= diff; j++)
      {
        stk.push(to_push++);
        output.push_back(true);
      }
      stk.pop();
      output.push_back(false);
    }
    else
    {
      while (true)
      {
        if (stk.empty())
        {
          cout << "NO" << endl;
          return 0;
        }
        bool top_same = (stk.top() == target);
        stk.pop();
        output.push_back(false);
        if (top_same)
          break;
      }
    }
  }
  for (auto el : output)
    cout << (el ? '+' : '-') << '\n';
  return 0;
}
