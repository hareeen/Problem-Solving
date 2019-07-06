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

  int N;
  int M;
  unordered_set<int> s;
  cin>>N;
  for (int i = 0; i < N; i++)
  {
    int a;
    cin >> a;
    s.insert(a);
  }
  cin>>M;
  for (int i = 0; i < M; i++)
  {
    int a;
    cin >> a;
    cout << (s.find(a) != s.end()) << " ";
  }
  cout << endl;

  return 0;
}
