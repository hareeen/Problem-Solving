#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <functional>

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

void hanoi(int current, int target, int slates) {
  int remain = 6 - target - current;

  if(slates == 1) {
    cout << current << " " << target << '\n';
    return;
  }
  hanoi(current, remain, slates - 1);
  cout << current << " " << target << '\n';
  hanoi(remain, target, slates - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  cout << static_cast<int>(pow(2, N) - 1) << endl;
  hanoi(1, 3, N);
} // main
