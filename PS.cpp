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

using pii = pair<pi, int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n;
  cin >> n;
  vector<pi> v1, v2;
  vector<pii> ans;
  for(int i = 0; i < n; i++) {
    int a;
    cin >> a;
    v1.push_back(pi(a, i));
  }
  for(int i = 0; i < n; i++) {
    int a;
    cin >> a;
    v2.push_back(pi(a, i));
  }
  sort(v1.begin(), v1.end(), greater<pair<int, int> >());
  sort(v2.begin(), v2.end(), greater<pair<int, int> >());
  for(int i = 0; i < n - 1; i++) {
    int diff = v1[i].first - v2[i].first;
    if(diff < 0) {
      cout << "NO" << endl;
      return 0;
    }
    ans.push_back(pii(pi(v1[i].second, v1[i + 1].second), diff));
    v1[i].first     -= diff;
    v1[i + 1].first += diff;
  }
  if(v1.back().first != v2.back().first) {
    cout << "NO" << endl;
    return 0;
  }
  cout << ans.size() << endl;
  for(auto i:ans) cout << i.first.first << " " << i.first.second << " " << i.second << '\n';
  return 0;
} // main
