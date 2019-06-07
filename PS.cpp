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
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

using psi = pair<string, int>;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

<<<<<<< HEAD
  int n;
  cin >> n;
  vector<pi> v1, v2;
  vector<pii> ans;
  for (int i = 0; i < n; i++)
  {
    int a;
    cin >> a;
    v1.push_back(pi(a, i));
  }
  for (int i = 0; i < n; i++)
  {
    int a;
    cin >> a;
    v2.push_back(pi(a, i));
  }
  sort(v1.begin(), v1.end(), greater<pair<int, int>>());
  sort(v2.begin(), v2.end(), greater<pair<int, int>>());
  for (int i = 0; i < n - 1; i++)
  {
    int diff = v1[i].first - v2[i].first;
    if (diff < 0)
    {
      cout << "NO" << endl;
      return 0;
    }
    ans.push_back(pii(pi(v1[i].second, v1[i + 1].second), diff));
    v1[i].first -= diff;
    v1[i + 1].first += diff;
  }
  if (v1.back().first != v2.back().first)
  {
    cout << "NO" << endl;
    return 0;
  }
  cout << ans.size() << endl;
  for (auto i : ans)
    cout << i.first.first + 1 << " " << i.first.second + 1 << " " << i.second << '\n';
=======
  string s1, s2;
  cin >> s1 >> s2;
  vector<vector<psi> > vec(s1.length() + 1, vector<psi>(s2.length() + 1));
  for(int i = 0; i < s1.length(); i++) {
    for(int j = 0; j < s2.length(); j++) {
      if(s1[i] == s2[j]) { vec[i + 1][j + 1] = psi(vec[i][j].first + s1[i], vec[i][j].second + 1); } else {
        if(vec[i + 1][j].second > vec[i][j + 1].second) vec[i + 1][j + 1] = vec[i + 1][j];
        else vec[i + 1][j + 1] = vec[i][j + 1];
      }
    }
  }
  cout << vec[s1.length()][s2.length()].second << endl;
  cout << vec[s1.length()][s2.length()].first << endl;
>>>>>>> b67830bba782553386d56eb76ca5da1cfd14b42d
  return 0;
} // main
