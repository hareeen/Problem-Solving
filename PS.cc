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

template <class T>
class myset : public unordered_set<T>
{
public:
  bool contains(T element)
  {
    return this->find(element) != this->end();
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  myset<int> s;
  for (int i = 0; i < N; i++)
  {
    string command;
    cin >> command;

    if (command == "add")
    {
      int t;
      cin >> t;
      s.insert(t);
    }
    if (command == "remove")
    {
      int t;
      cin >> t;
      if (s.contains(t))
        s.erase(t);
    }
    if (command == "check")
    {
      int t;
      cin >> t;
      cout << static_cast<int>(s.contains(t)) << '\n';
    }
    if (command == "toggle")
    {
      int t;
      cin >> t;
      if (s.contains(t))
        s.erase(t);
      else
        s.insert(t);
    }
    if (command == "all")
    {
      for (int i = 1; i <= 20; i++)
        s.insert(i);
    }
    if (command == "empty")
    {
      s.clear();
    }
  }

  return 0;
}