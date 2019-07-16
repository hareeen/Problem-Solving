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

void transp_assign(const int sz, vector<vector<int>> &here, vector<vector<int>> &there)
{
  for (int i = 0; i < sz; i++)
    for (int j = 0; j < sz; j++)
      there[i][j] = here[j][i];
  return;
}

// 1: left, 2:right
void merge(const int sz, vector<int> &target, int dir)
{
  list<pi> result;
  if (dir == 2)
    reverse(iterall(target));
  for (const auto el : target)
  {
    if (el == 0)
      continue;
    if (result.empty())
    {
      result.push_back(pi(el, 0));
      continue;
    }
    if (result.back().first == el && result.back().second == 0)
    {
      result.pop_back();
      result.push_back(pi(el + 1, 1));
    }
    else
      result.push_back(pi(el, 0));
  }

  reverse(iterall(result));
  target.clear();
  target.resize(sz - result.size());
  for (const auto [num, mg] : result)
    target.push_back(num);
  if (dir == 1)
    reverse(iterall(target));

  return;
}

class Board
{
private:
  int boardSize;
  vector<vector<int>> horizontal;
  vector<vector<int>> vertical;

public:
  Board(int N)
  {
    horizontal.clear();
    vertical.clear();
    boardSize = N;
    horizontal.resize(N, vector<int>(N));
    vertical.resize(N, vector<int>(N));
  }
  Board(const vector<vector<int>> &initial)
  {
    horizontal.clear();
    vertical.clear();
    boardSize = initial.size();
    horizontal.resize(boardSize);
    for (int i = 0; i < boardSize; i++)
    {
      for (const auto &el : initial[i])
        horizontal[i].push_back((el != 0 ? static_cast<int>(round(log2(el))) : 0));
    }
    vertical = decltype(vertical)(boardSize, vector<int>(boardSize, 0));
    transp_assign(boardSize, horizontal, vertical);
  }
  Board(const Board &initial)
  {
    boardSize = initial.boardSize;
    horizontal = decltype(horizontal)(initial.horizontal);
    vertical = decltype(vertical)(initial.vertical);
  }
  void move(int dir)
  {
    // left right up down
    if (dir == 1 || dir == 2)
    {
      for (auto &vec : horizontal)
        merge(boardSize, vec, dir);
      transp_assign(boardSize, horizontal, vertical);
    }
    else
    {
      for (auto &vec : vertical)
        merge(boardSize, vec, dir - 2);
      transp_assign(boardSize, vertical, horizontal);
    }
    return;
  }
  int getMax()
  {
    int ans = 0;
    for (const auto &vec : horizontal)
      for (const auto &el : vec)
        ans = max(el, ans);
    return (1 << ans);
  }
  vector<vector<int>> getBoard()
  {
    return horizontal;
  }
};

int solve(const int &sz, Board board, int depth)
{
  if (depth == 5)
    return board.getMax();
  else
  {
    int ans = 0;
    for (int i = 1; i <= 4; i++)
    {
      auto newBoard = Board(board);
      newBoard.move(i);
      ans = max(ans, solve(sz, newBoard, depth + 1));
    }
    return ans;
  }
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;

  vector<vector<int>> board(N);
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      int t;
      cin >> t;
      board[i].push_back(t);
    }
  }

  cout << solve(N, Board(board), 0) << endl;

  return 0;
}