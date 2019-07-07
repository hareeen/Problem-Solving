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

  string s;
  cin >> s;
  stack<char> stk1, stk2;
  for (char el : s)
    stk1.push(el);

  int N;
  cin >> N;
  for (int i = 0; i < N; i++)
  {
    char mode;
    cin >> mode;
    switch (mode)
    {
    case 'L':
      if(!stk1.empty()) {
        stk2.push(stk1.top());
        stk1.pop();
      }
      break;

    case 'D':
      if(!stk2.empty()) {
        stk1.push(stk2.top());
        stk2.pop();
      }
      break;

    case 'B':
      if(!stk1.empty()) stk1.pop();
      break;

    case 'P':
      char c;
      cin >> c;
      stk1.push(c);
      break;

    default:
      break;
    }
  }

  string outp;
  while(!stk1.empty()) outp.push_back(stk1.top()),stk1.pop();
  reverse(M_iterall(outp));
  while(!stk2.empty()) outp.push_back(stk2.top()),stk2.pop();
  cout<<outp<<endl;

  return 0;
}
