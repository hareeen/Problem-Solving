#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>
#include <bitset>
#include <utility>
#include <iterator>

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

int N, M;
vector<int> Ai;

ll get_balloons(int _balloon) {
	int s=0;
	for(auto i:Ai) s+=(_balloon%i);
	return s;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N>>M;
	for(int i=0;i<N;i++) {
		int t;
		cin>>t;
		Ai.push_back(t);
	}

	ll l=0, r=LLONG_MAX;
	while(l!=r) {
		ll mid=(l+r)/2;
		if(get_balloons(mid)<M) l=mid+1;
		else r=mid;
	}

	cout<<l;
	return 0;
}
