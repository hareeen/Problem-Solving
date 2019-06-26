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

char toCh(int n)
{
  return static_cast<char>(n + 65);
}

int toInt(char c)
{
  if (c == '.')
    return -1;
  else
    return static_cast<int>(c) - 65;
}

void order(vector<vector<int>> &tree, int node, int mode)
{
  if (node == -1)
    return;
  switch (mode)
  {
  case 0:
    cout << toCh(node);
    order(tree, tree[node][0], mode);
    order(tree, tree[node][1], mode);
    break;
  case 1:
    order(tree, tree[node][0], mode);
    cout << toCh(node);
    order(tree, tree[node][1], mode);
    break;
  case 2:
    order(tree, tree[node][0], mode);
    order(tree, tree[node][1], mode);
    cout << toCh(node);
    break;

  default:
    break;
  }
  if (node == 0)
    cout << endl;
  return;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<vector<int>> tree(N, vector<int>(2, -1));
  for (int i = 0; i < N; i++)
  {
    char u, v1, v2;
    cin >> u >> v1 >> v2;
    tree[toInt(u)][0] = toInt(v1);
    tree[toInt(u)][1] = toInt(v2);
  }
  for (int i = 0; i < 3; i++)
    order(tree, 0, i);
  return 0;
}
