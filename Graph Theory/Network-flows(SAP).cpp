//network-flows
//( http://www.cnblogs.com/wally/p/3274438.html )
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <vector>
#define INF 1000000005
#define N 505
#define M 20005
using namespace std;
int n,m,a[N],p[N];
struct edge{
	int from,to,cap,flow,next;
	edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f) {}
};
vector<edge> edges;
vector<int> G[N];
int minn(int a,int b) {
	if (a<b) return a;
	return b;
}
void init() {
	for (int i=0; i<n; i++) G[i].clear();
	edges.clear();
}
void addedges(int from,int to,int cap) {
	edges.push_back(edge(from,to,cap,0));
	edges.push_back(edge(to,from,0,0));
	m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}
int maxflow(int s,int t) {
	int flow=0;
	for (;;) {
		memset(a, 0, sizeof(a));
		queue<int> Q;
		Q.push(s);
		a[s]=INF;
		while (!Q.empty()) {
			int x=Q.front(); Q.pop();
			for (int i=0; i<G[x].size(); i++) {
				edge& e = edges[G[x][i]];
				if (!a[e.to] && e.cap>e.flow) {
					p[e.to]=i;
					a[e.to]=minn(a[x], e.cap-e.flow);
					Q.push(e.to);
				}
			}
			if (a[t]) break;
		}
		if (!a[t]) break;
		for (int u=t; u!=s; u=edges[p[u]].from) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
		}
		flow += a[t];
	}
	return flow;
}