#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>
#include <bitset>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;
using uint = unsigned int;
using ll = long long;
using pi = pair<int, int>;
using ti = tuple<int, int, int>;
using pli = pair<ll, ll>;
using pti = tuple<ll, ll, ll>;

// Classes
int C, B;
vector<int> calories;

// Global Variables


// Function


// Main
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  // Code Start
  cin>>C>>B;
  for(int i=0;i<B;i++) {
    int _t;
    cin>>_t;
    calories.push_back(_t);
  }

  bitset<21> _bits;
  _bits.set();
  auto _pow=_bits.to_ulong();
  int _max=-1;

  for(uint i=0;i<=_pow;i++) {
    _bits=bitset<21>(i);
    auto _sum=0;
    for(int j=0;j<B;j++) _sum+=_bits[j]?calories[j]:0;
    _max=max(_max, _sum>C?-1:_sum);
  }

  cout<<_max<<endl;
  return 0;
}
