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
  vector<int> lis;
  cin >> N;
  for(int i = 0; i < N; i++) {
    int a;
    cin >> a;
    input.push_back(a);
  }
  for(const auto &i:input) {
    auto it = lower_bound(lis.begin(), lis.end(), i, greater<int>());
    if(it == lis.end()) lis.push_back(i);
    else *it = i;
  }
  cout << lis.size() << endl;
  return 0;
} // main
