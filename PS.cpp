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
int N, M, V;
vector<vector<int> > adjaList;
vector<bool> visited;

// Global Variables


// Function
void DFS(int _v) {
	cout<<_v+1<<" ";
	visited[_v]=true;
	for(auto i:adjaList[_v]) if(!visited[i]) DFS(i);
	return;
}

void BFS(int _v) {
	visited[_v]=true;
	queue<int> _que;
	_que.push(_v);
	while(!_que.empty()) {
		for(auto i:adjaList[_que.front()]) {
			if(!visited[i]) {
				_que.push(i);
				visited[i]=true;
			}
		}
		cout<<_que.front()+1<<" ";
		_que.pop();
	}
}

// Main
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	// Code Start
	cin>>N>>M>>V;
	V--;
	adjaList.resize(N);
	for(int i=0; i<M; i++) {
		int _v1, _v2;
		cin>>_v1>>_v2;
		_v1--; _v2--;
		adjaList[_v1].push_back(_v2);
		adjaList[_v2].push_back(_v1);
	}

	for(int i=0;i<N;i++) sort(adjaList[i].begin(), adjaList[i].end());

	visited.clear();
	visited.resize(N);
	DFS(V);
	cout<<endl;

	visited.clear();
	visited.resize(N);
	BFS(V);
	cout<<endl;

	return 0;
}
