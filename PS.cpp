#include <iostream>
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

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pli = pair<ll, ll>;

int N, M;
int sz;
vector<int> arr;
vector<int> tree_min, tree_max;

int init(vector<int> &_arr, vector<int> &_tree, int node, int start, int end, bool min_max) {
	if(start==end) return _tree[node]=_arr[start];
	else if(min_max) return _tree[node]=min(init(_arr, _tree, node*2, start, (start+end)/2, min_max), init(_arr, _tree, node*2+1, (start+end)/2+1, end, min_max));
	else return _tree[node]=max(init(_arr, _tree, node*2, start, (start+end)/2, min_max), init(_arr, _tree, node*2+1, (start+end)/2+1, end, min_max));
}

//left, right: 구하는 구간
int tree_prce(vector<int> &_tree, int node, int start, int end, int left, int right, bool min_max) {
	if(right<start || end<left) return min_max?INT_MAX:INT_MIN;
	else if(left<=start && end<=right) return _tree[node];
	else if(min_max) return min(tree_prce(_tree, node*2, start, (start+end)/2, left, right, min_max), tree_prce(_tree, node*2+1, (start+end)/2+1, end, left, right, min_max));
	else return max(tree_prce(_tree, node*2, start, (start+end)/2, left, right, min_max), tree_prce(_tree, node*2+1, (start+end)/2+1, end, left, right, min_max));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin>>N>>M;
	for(int i=0; i<N; i++) {
		int tmp;
		cin>>tmp;
		arr.push_back(tmp);
	}
	sz = static_cast<int>(pow(2, ceil(log2(N))+1));
	tree_min.resize(sz, INT_MAX);
	tree_max.resize(sz, INT_MIN);
	init(arr, tree_min, 1, 0, N-1, true);
	init(arr, tree_max, 1, 0, N-1, false);

	for(int i=0; i<M; i++) {
		int l, r;
		cin>>l>>r;
		cout<<tree_prce(tree_min, 1, 0, N-1, l-1, r-1, true)<<"\n";
	}
	return 0;
}
