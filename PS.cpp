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

using psi = pair<string, int>;

void addZero(string &s, int n) {
  for(int i = 0; i < n; i++) s += '0';
}

void addDigit(psi &t, int adder) {
  addZero(t.first, adder);
  t.second += adder;
}

char ntoCh(int n) {
  return static_cast<char>(48 + n);
}

int chtoN(char ch) {
  return static_cast<int>(ch - '0');
}

psi add_(psi l, psi r) {
  if(l.second > r.second) swap(l, r);
  addDigit(l, r.second - l.second);
  if(l.first.length() > r.first.length()) swap(l, r);
  string ret;
  int carry = 0;
  string st_l = l.first, st_r = r.first;
  int lenL = st_l.length(), lenR = st_r.length();
  reverse(st_l.begin(), st_l.end());
  reverse(st_r.begin(), st_r.end());
  for(int i = 0; i < lenR; i++) {
    int plus;
    if(i < lenL) plus = carry + chtoN(st_l[i]) + chtoN(st_r[i]);
    else plus = carry + chtoN(st_r[i]);
    ret  += ntoCh(plus % 10);
    carry = plus / 10;
  }
  if(carry != 0) ret += ntoCh(carry);
  reverse(ret.begin(), ret.end());
  return psi(ret, l.second);
}

string mul_one(string s, int n) {
  string ret;
  int carry = 0;

  reverse(s.begin(), s.end());
  for(const auto &i:s) {
    int plus = carry + chtoN(i) * n;
    ret  += ntoCh(plus % 10);
    carry = plus / 10;
  }
  if(carry != 0) ret += ntoCh(carry);
  reverse(ret.begin(), ret.end());
  return ret;
}

psi mul_(psi l, psi r) {
  if(l.first.length() > r.first.length()) swap(l, r);
  string st_l = l.first, st_r = r.first;
  reverse(st_l.begin(), st_l.end());
  psi ret = psi(string("0"), 0);
  for(int i = 0; i < st_l.length(); i++) {
    int ntomul   = chtoN(st_l[i]);
    string toAdd = mul_one(st_r, ntomul);
    addZero(toAdd, i);
    ret = add_(ret, psi(toAdd, 0));
  }
  return psi(ret.first, l.second + r.second);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string a;
  int n;
  string filtered;
  int digit;
  cin >> a >> n;
  for(int i = 0; i < a.length(); i++) {
    if(a[i] == '.') digit = a.length() - i - 1;
    else filtered += a[i];
  }
  psi toCalc(filtered, digit);
  psi result("10", 0);
  while(n > 0) {
    if(n % 2) result = mul_(result, toCalc);
    toCalc = mul_(toCalc, toCalc);
    n     /= 2;
  }
  for(int i = 0; i < result.first.length() - 1; i++) {
    if(i == result.first.length() - result.second - 1) cout << '.';
    cout << result.first[i];
  }
  cout << endl;
  return 0;
} // main
