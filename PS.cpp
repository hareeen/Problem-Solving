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
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> ti;

vector<pi> states;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  // Code Start
  int n,m,t;
  cin>>n>>m>>t;
  int cnt=0;
  while(true) {
    if(n*cnt>t) break;
    states.push_back(pi((t-n*cnt)%m, -(cnt+(t-n*cnt)/m)));
    cnt++;
  }
  sort(states.begin(), states.end());
  cout<<-states[0].second<<" "<<states[0].first<<endl;
  return 0;
}
