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

int ufFind(vector<int> &parent, int n)
{
  if (parent[n] == n)
    return n;
  else
    return parent[n] = ufFind(parent, parent[n]);
}

void ufUnion(vector<int> &parent, int u, int v)
{
  parent[ufFind(parent, u)] = ufFind(parent, v);
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, Q;
  cin >> N >> Q;

  vector<int> parent_final(1), parent(1);
  for (int i = 0; i < N - 1; i++)
  {
    int t;
    cin >> t;
    parent_final.push_back(--t);
    parent.push_back(i + 1);
  }

  vector<pi> query1;
  vector<pair<int, pi>> query2;
  for (int i = 0; i < N + Q - 1; i++)
  {
    int x;
    cin >> x;
    if (x == 0)
    {
      int b;
      cin >> b;
      query1.push_back(pi(i, --b));
    }
    else
    {
      int c, d;
      cin >> c >> d;
      query2.push_back(make_pair(i, pi(--c, --d)));
    }
  }

  reverse(iterall(query1));
  reverse(iterall(query2));

  vector<bool> result;
  auto iter1 = query1.begin();
  auto iter2 = query2.begin();
  for (int i = N + Q - 2; i >= 0; i--)
  {
    if (iter1 != query1.end() && (*iter1).first == i)
    {
      ufUnion(parent, (*iter1).second, parent_final[(*iter1).second]);
      iter1++;
    }
    else
    {
      result.push_back(ufFind(parent, (*iter2).second.first) == ufFind(parent, (*iter2).second.second));
      iter2++;
    }
  }

  reverse(iterall(result));

  for (const auto &el : result)
    cout << (el ? "YES" : "NO") << '\n';

  return 0;
}