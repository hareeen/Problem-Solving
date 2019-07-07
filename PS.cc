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

  int N, K;
  string s;
  cin >> N >> K;
  cin >> s;

  vector<pi> num_l;
  for (int i = 0; i < N; i++)
    num_l.push_back(pi(static_cast<int>(s[i] - '0'), -i));
  sort(M_iterall(num_l), greater<pi>());

  for (int i = 0; i < N; i++)
    num_l[i].second = -num_l[i].second;
  num_l.push_back(pi(0, N));

  vector<bool> check(N);
  int cur_pos = 0;
  while (true)
  {
    if (cur_pos == N)
    {
      for (int i = 0; i < K; i++)
        check[N - i - 1] = true;
      break;
    }
    if (K == 0)
      break;
    for (int i = 0; i <= N; i++)
    {
      if (cur_pos == num_l[i].second)
      {
        cur_pos++;
        break;
      }
      if (num_l[i].second > cur_pos && num_l[i].second - cur_pos <= K)
      {
        K -= (num_l[i].second - cur_pos);
        for (; cur_pos < num_l[i].second; cur_pos++)
          check[cur_pos] = true;
        cur_pos++;
        // cout << cur_pos << " " << K << endl;
        break;
      }
    }
  }

  for (int i = 0; i < N; i++)
    if (!check[i])
      cout << s[i];
  cout << endl;

  return 0;
}
