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

#define M_iterall(container) container.begin(), container.e()

using namespace std;
using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

i64 init(vector<i64> &arr, vector<pli> &tree, int node, int s, int e)
{
  int mid = (s + e) / 2;
  if (s == e)
    return tree[node].first = arr[s];
  else
    return tree[node].first = init(arr, tree, node * 2, s, mid) + init(arr, tree, node * 2 + 1, mid + 1, e);
}

void update_range(vector<pli> &tree, int node, int s, int e, int left, int right, i64 diff)
{
  if (tree[node].second != 0)
  {
    tree[node].first += tree[node].second * (e - s + 1);
    if (s != e)
    {
      tree[node * 2].second += tree[node].second;
      tree[node * 2 + 1].second += tree[node].second;
    }
    tree[node].second = 0;
  }
  if (e < left || s > right)
    return;
  if (left <= s && e <= right)
  {
    tree[node].first += (e - s + 1) * diff;
    if (s != e)
    {
      tree[node * 2].second += diff;
      tree[node * 2 + 1].second += diff;
    }
    return;
  }

  int mid = (s + e) / 2;
  update_range(tree, node * 2, s, mid, left, right, diff);
  update_range(tree, node * 2 + 1, mid + 1, e, left, right, diff);

  tree[node].first = tree[node * 2].first + tree[node * 2 + 1].first;
  return;
}

i64 sum(vector<pli> &tree, int node, int s, int e, int left, int right)
{
  if (tree[node].second != 0)
  {
    tree[node].first += tree[node].second * (e - s + 1);
    if (s != e)
    {
      tree[node * 2].second += tree[node].second;
      tree[node * 2 + 1].second += tree[node].second;
    }
    tree[node].second = 0;
  }
  if (e < left || s > right)
    return 0;
  if (left <= s && e <= right)
    return tree[node].first;

  int mid = (s + e) / 2;
  return sum(tree, node * 2, s, mid, left, right) + sum(tree, node * 2 + 1, mid + 1, e, left, right);
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, M, K;
  cin >> N >> M >> K;

  vector<pli> tree(static_cast<int>(pow(2, static_cast<int>(log2(N) + 1) + 1)));
  vector<i64> arr(1);

  for (int i = 0; i < N; i++)
  {
    int t;
    cin >> t;
    arr.push_back(t);
  }

  init(arr, tree, 1, 1, N);

  for (int i = 0; i < M + K; i++)
  {
    int mode;
    cin >> mode;
    if (mode == 1)
    {
      int l, r, d;
      cin >> l >> r >> d;
      update_range(tree, 1, 1, N, l, r, d);
    }
    else
    {
      int l, r;
      cin >> l >> r;
      cout << sum(tree, 1, 1, N, l, r) << "\n";
    }
  }

  return 0;
}