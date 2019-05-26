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

string compress(vector<vector<int> > &data, pi st, pi ed) {
  // printf("%d %d %d %d\n", st.first, st.second, ed.first, ed.second);
  if(st == ed) return data[st.first][st.second] == 0 ? "0" : "1";

  auto mid = pi((st.first + ed.first) / 2, (st.second + ed.second) / 2);
  vector<string> res;
  res.push_back(compress(data, st, mid));
  res.push_back(compress(data, pi(st.first, mid.second + 1), pi(mid.first, ed.second)));
  res.push_back(compress(data, pi(mid.first + 1, st.second), pi(ed.first, mid.second)));
  res.push_back(compress(data, pi(mid.first + 1, mid.second + 1), ed));

  auto st_ret      = string();
  auto canCompress = true;
  auto tpe         = -1;
  for(auto &str:res) {
    canCompress &= (str.size() == 1);
    if(tpe == -1) {
      tpe = (str[0] == '0' ? 0 : 1);
    } else if((str[0] == '0' ? 0 : 1) != tpe) {
      canCompress = false;
    }
    st_ret += str;
    // cout << str << endl;
  }
  if(canCompress) return tpe == 0 ? "0" : "1";
  else return "(" + st_ret + ")";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  vector<vector<int> > data;
  cin >> N;
  for(auto i = 0; i < N; i++) {
    vector<int> tmp;
    string inp;
    cin >> inp;
    for(const auto &i:inp) tmp.push_back(i == '0' ? 0 : 1);
    data.push_back(tmp);
  }

  cout << compress(data, pi(0, 0), pi(N - 1, N - 1)) << endl;
  return 0;
} // main
