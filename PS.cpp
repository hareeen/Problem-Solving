#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>

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
  vector<char> que;
  for (const auto &i : s)
  {
    que.push_back(i);
    if (que.size() >= 4)
    {
      bool isMatch = true;
      char match[4] = {'P', 'A', 'P', 'P'};
      for (int i = 1; i <= 4; i++)
        isMatch = isMatch && (match[i - 1] == que[que.size() - i]);
      if (isMatch)
        for (int i = 0; i < 3; i++)
          que.pop_back();
    }
  }
  cout << ((que.size() == 1 && que[0] == 'P') ? "PPAP" : "NP") << endl;
  return 0;
}
