#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ti = tuple<int, int, int>;
using pli = pair<ll, ll>;
using pti = tuple<ll, ll, ll>;

// Classes


// Global Variables
int N;
vector<int> slimes;

// Function


// Main
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  // Code Start
  cin>>N;
  for(int i=0;i<N;i++) {
    int _t;
    cin>>_t;
    slimes.push_back(_t);
  }
  sort(slimes.begin(), slimes.end(), greater<int>());

  int _merged=slimes[0]+slimes[1], res=slimes[0]*slimes[1];
  for(int i=2;i<N;i++) {
    res+=(_merged*slimes[i]);
    _merged+=slimes[i];
  }

  cout<<res<<endl;
  return 0;
}
