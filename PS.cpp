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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int V, E;
	cin>>V>>E;
	int start_v;
	cin>>start_v;
	start_v--;
	vector<vector<pi> > adjL;
	adjL.resize(V);
	for(int i=0; i<E; i++) {
		int u,v,w;
		cin>>u>>v>>w;
		u--; v--;
		adjL[u].push_back(pi(v, w));
	}

	priority_queue<pi, vector<pi>, greater<pi> > pq;
	vector<int> dist(V, INT_MAX);
	dist[start_v]=0;
	pq.push(pi(0, start_v));

	while(!pq.empty()) {
		auto top_elem=pq.top();
		pq.pop();
		if(top_elem.first > dist[top_elem.second]) continue;
		for(auto [vertex, weight]:adjL[top_elem.second]) {
			if(dist[vertex]>top_elem.first+weight) {
				dist[vertex]=top_elem.first+weight;
				pq.push(pi(top_elem.first+weight, vertex));
			}
		}
	}
	for(auto &i:dist) {
		if(i==INT_MAX) cout<<"INF"<<'\n';
		else cout<<i<<'\n';
	}
	cout<<flush;
	return 0;
}
