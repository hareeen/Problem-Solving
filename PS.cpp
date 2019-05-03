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
using pi = pair<int, int>;
using pli = pair<i64, i64>;
using ti = tuple<int, int, int>;
using tli = tuple<i64, i64, i64>;

int num[10]={6,2,5,5,4,5,6,3,7,6};


char ItoC(int n) {
	return static_cast<char>(n+static_cast<int>('0'));
}

// lhs < rhs, isMin=true 면 true 반환, isMin=false면 반대로
bool compstring(const string& lhs, const string& rhs, bool isMin) {
	if(lhs.size()!=rhs.size()) return isMin^(lhs.size()>rhs.size());
	for(int i=0; i<lhs.size(); i++) if(lhs[i]!=rhs[i]) return isMin^(lhs[i]>rhs[i]);
	return false;
}

string dynamic(int n, bool isMin) {
	vector<vector<string> > dp(n+1, vector<string>(10, ""));
	const string init_str=isMin?"0000000000000000000000000000000000000000000000000000000":"0";
	for(int i=1; i<=n; i++) {
		for(int j=0; j<10; j++) {
			if(i<num[j]) {
				dp[i][j]=init_str;
				continue;
			}
			bool isVaild=false;
			dp[i][j]=init_str;
			for(int k=0; k<10; k++) {
				//cout<<dp[i-num[j]][k]+ItoC(j)<<" "<<dp[i][j]<<endl;
				if(dp[i-num[j]][k]=="" && j==0) continue;
				if(dp[i-num[j]][k]!=init_str && compstring(dp[i-num[j]][k]+ItoC(j), dp[i][j], isMin)) dp[i][j]=dp[i-num[j]][k]+ItoC(j);
			}
			//cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
		}
	}
	string res=init_str;
	for(auto &st:dp[n]) if(res==init_str || compstring(st, res, isMin)) res=st;
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin>>t;
	for(int i=0;i<t;i++) {
		int n;
		cin>>n;
		cout<<dynamic(n, true)<<" "<<dynamic(n, false)<<endl;
	}
	return 0;
}
