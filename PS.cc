#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <cmath>
#include <cstdio>
#include <cstring>

#define iterall(container) container.begin(), container.end()

using namespace std;

using i64 = long long;
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

void process() {
  int N;
  cin >> N;

  vector<pi> edge(N);
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int color;
      cin >> color;

      if (color)
        edge[i].first++, edge[j].first++;
      else
        edge[i].second++, edge[j].second++;
    }
  }

  cout << accumulate(
              edge.begin(), edge.end(), N * (N - 1) * (N - 2) / 3,
              [](int x, pi p) -> int { return x - p.first * p.second; }) /
              2
       << '\n';
  return;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int T;
  cin >> T;

  for (int i = 0; i < T; i++) process();

  return 0;
}