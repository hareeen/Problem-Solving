#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>

using namespace std;
using i64 = long long;
using pi  = pair<int, int>;
using pli = pair<i64, i64>;
using ti  = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  vector<int> input;
  vector<vector<int> > dp;
  cin >> N;
  for(int i = 0; i < N; i++) {
    int a;
    cin >> a;
    input.push_back(a);
  }
  dp.resize(N, vector<int>(N));
  for(int intv = 1; intv < N; intv++) {
    for(int j = 0; j < N - intv; j++) {
      if(input[j] == input[j + intv]) dp[j][j + intv] = (intv == 1 ? 0 : dp[j + 1][j + intv - 1]);
      else dp[j][j + intv] = min(dp[j + 1][j + intv], dp[j][j + intv - 1]) + 1;
    }
  }
  cout << dp[0][N - 1] << endl;
  return 0;
} // main
