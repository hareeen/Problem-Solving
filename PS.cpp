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

// Classes
int N, M, V;
vector<vector<int> > adjaList;
vector<bool> visited;

// Global Variables
string str;
vector<int> cnt(5);

// Function
int geti(char c) {
	auto s=string("quack");
	for(int i=0; i<5; i++) if(c==s[i]) return i;
	return 0;
}

bool isVaild(vector<int> v) {
	bool ret=true;
	for(int i=0; i<v.size()-1; i++) ret&=(v[i]>=v[i+1]);
	return ret;
}

// Main
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// Code Start
	cin>>str;
	int _res=-1;
	for(auto i:str) {
		cnt[geti(i)]++;
		if(!isVaild(cnt)) {
			cout<< -1<<endl;
			return 0;
		}
		_res=max(_res, *max_element(cnt.begin(), cnt.end())-*min_element(cnt.begin(), cnt.end()));
	}
	if(*max_element(cnt.begin(), cnt.end())-*min_element(cnt.begin(), cnt.end())==0) cout<<_res<<endl;
	else cout<<-1<<endl;
	return 0;
}
