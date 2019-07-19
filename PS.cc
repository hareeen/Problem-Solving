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

class disjointSet
{
private:
  vector<int> uf;

public:
  disjointSet(const int N)
  {
    uf.clear();
    for (int i = 0; i < N; i++)
      uf.push_back(i);
  }
  int find(const int n)
  {
    if (uf[n] == n)
      return n;
    else
      return uf[n] = find(uf[n]);
  }
  void merge(const int u, const int v)
  {
    uf[find(u)] = uf[find(v)];
    return;
  }
  bool isSameset(const int u, const int v)
  {
    return find(u) == find(v);
  }
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N, K;
  cin >> N >> K;

  queue<tuple<int, int, pi>> que;
  queue<tuple<int, int, pi>> que2;
  vector<vector<int>> civilMap(N, vector<int>(N, -1));
  for (int i = 0; i < K; i++)
  {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    que.push({0, i, pi(x, y)});
    que2.push({0, i, pi(x, y)});
    civilMap[x][y] = i;
  }

  int dx[5] = {0, 0, 1, -1};
  int dy[5] = {1, -1, 0, 0};

  int last = -1;

  int union_count = 0;
  auto dS = disjointSet(K);
  while (!que.empty())
  {
    auto [currentYear, civil, corrd] = que.front();
    que.pop();

    if (last != currentYear)
    {
      while (!que2.empty())
      {
        auto [curY, civ, cor] = que2.front();
        que2.pop();
        for (int i = 0; i < 4; i++)
        {
          int nextX = cor.first + dx[i], nextY = cor.second + dy[i];
          if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && civilMap[nextX][nextY] != -1 && !dS.isSameset(civilMap[nextX][nextY], civ))
          {
            dS.merge(civilMap[nextX][nextY], civ);
            union_count++;
          }
        }
      }
      if (union_count == K - 1)
      {
        cout << currentYear << endl;
        break;
      }
    }

    for (int i = 0; i < 4; i++)
    {
      int nextX = corrd.first + dx[i], nextY = corrd.second + dy[i];
      if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N && civilMap[nextX][nextY] == -1)
      {
        civilMap[nextX][nextY] = civil;
        que.push({currentYear + 1, civil, pi(nextX, nextY)});
        que2.push({currentYear + 1, civil, pi(nextX, nextY)});
      }
    }

    last = currentYear;
  }

  return 0;
}