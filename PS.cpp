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

int dx[9] = { 0, 1, 2, 0, 1, 2, 0, 1, 2 };
int dy[9] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };

int _sum(vector<int> arr) {
  int _s = 0;

  return accumulate(arr.begin(), arr.end(), _s);
}

int isSimple(vector<int> arr) {
  if(_sum(arr) != 1) return -1;

  for(int i = 0; i < arr.size(); i++) {
    if(arr[i] == 1) {
      return i;
    }
  }
  return -1;
}

vector<int> paper(vector<vector<int> > &data, pi st, pi ed) {
  auto sz = ed.first - st.first + 1;

  if(sz == 1) {
    vector<int> ret(3);
    ret[data[st.first][st.second]]++;
    return ret;
  }
  sz /= 3;
  vector<vector<int> > res;
  for(int i = 0; i < 9; i++) {
    res.push_back(paper(data, pi(st.first + sz * dx[i], st.second + sz * dy[i]),
      pi(ed.first - sz * dx[8 - i], ed.second - sz * dy[8 - i])));
  }

  vector<int> ret(3);
  int tpe = -2;
  bool compressAble = true;
  for(auto &i:res) {
    auto t = isSimple(i);
    if(t == -1) compressAble = false;
    if(tpe == -2) tpe = t;
    else compressAble &= (tpe == t);
    for(int j = 0; j < 3; j++) ret[j] += i[j];
  }
  if(compressAble) {
    ret.clear();
    ret.resize(3);
    ret[tpe]++;
  }
  return ret;
} // paper

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int N;
  cin >> N;
  vector<vector<int> > data(N, vector<int>(N));
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      int a;
      cin >> a;
      data[i][j] = a + 1;
    }
  }

  for(auto &i:paper(data, pi(0, 0), pi(N - 1, N - 1))) cout << i << '\n';
  return 0;
} // main
