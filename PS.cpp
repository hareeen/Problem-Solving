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

int init(vector<int> &a, vector<int> &tree, int node, int s, int e) {
	if(s==e) return tree[node]=a[s];
	else return tree[node]=init(a, tree, node*2, s, (s+e)/2)+init(a, tree, node*2+1, (s+e)/2+1, e);
}

//l에서 r이 구하는 거
int sum(vector<int> &tree, int node, int l, int r, int s, int e) {
	if(e<l || r<s) return 0;
	else if(l<=s && e<=r) return tree[node];
	else return sum(tree, node*2, l, r, s, (s+e)/2)+sum(tree, node*2+1, l, r, (s+e)/2+1, e);
}

void update(vector<int> &tree, int node, int s, int e, int idx, int diff) {
	if(idx<s || idx>e) return;
	tree[node]+=diff;
	if(s!=e) {
		update(tree, node*2, s, (s+e)/2, idx, diff);
		update(tree, node*2+1, (s+e)/2+1, e, idx, diff);
	}
	return;
}

void process() {
	int N, M;
	vector<int> index;
	vector<int> idx_save;

	cin>>N>>M;
	index.resize(N+M+1);
	idx_save.resize(N);
	for(int i=0; i<N; i++) index[i]=1;
	for(int i=0; i<N; i++) idx_save[i]=N-i-1;

	int top=N;
	int tree_s=static_cast<int>(pow(2, ceil(log2(N+M+1))+1));
	vector<int> tree(tree_s);

	init(index, tree, 1, 0, index.size()-1);
	for(int i=0; i<M; i++) {
		int query;
		cin>>query;
		query--;

		cout<<sum(tree, 1, idx_save[query]+1, index.size()-1, 0, index.size()-1)<<" ";
		update(tree, 1, 0, index.size()-1, idx_save[query], -1);
		idx_save[query]=top++;
		update(tree, 1, 0, index.size()-1, idx_save[query], 1);
	}
	cout<<'\n';
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin>>t;
	for(int i=0; i<t; i++) process();
	cout<<flush;
	return 0;
}
