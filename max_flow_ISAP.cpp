//HDU 3549
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int max_nodes = 50;
const int max_edges = 3005;
const int INF = 100005;

struct Edge{
	int from,to,capacity,flow;
}edges[max_edges];

vector<int> G[max_nodes];
int T,num_nodes,num_edges;
int source,sink;	// 源点和汇点
int p[max_nodes];   // 可增广路上的上一条弧的编号
int num[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int d[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
bool visited[max_nodes];

int Min(int a,int b) {
	if(a>b) return b;return a;
}

void build() {
	scanf("%d%d",&num_nodes,&num_edges);
	for(int i=0; i<=num_nodes; i++) {
		d[i]=16;
	}
	int u,v,cap=0,cnt=0;
	for(int i=0; i<num_edges; i++) {
		scanf("%d%d%d",&u,&v,&cap);
		//加正向弧  
		edges[cnt].from=u;
		edges[cnt].to=v;  
		edges[cnt].capacity=cap; 
		edges[cnt].flow=0; 
		G[u].push_back(cnt++);  
		//加反向弧  
		edges[cnt].from=v;
		edges[cnt].to=u;  
		edges[cnt].capacity=0;
		edges[cnt].flow=0;  
		G[v].push_back(cnt++); 
	}
	sink=num_nodes;
	source=1;
	d[sink] = 0;
}

// 预处理, 反向 BFS 构造 d 数组
void bfs() {
	memset(visited, 0, sizeof(visited));
	queue<int> Q;
	Q.push(sink);
	visited[sink] = 1;
	d[sink] = 0;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int ix = 0; ix < G[u].size(); ++ix) {
			Edge &e = edges[(G[u][ix])^1];
			if(!visited[e.from] && e.capacity > e.flow) {
				visited[e.from] = true;
				d[e.from] = d[u] + 1;
				Q.push(e.from);
			}
		}
	}
}

// 增广
int augment() {
	int u = sink, df = INF;
	// 从汇点到源点通过 p 追踪增广路径, df 为一路上最小的残量
	while(u != source) {
		Edge &e = edges[p[u]];
		df = Min(df, e.capacity - e.flow);
		u = edges[p[u]].from;
	}
	u = sink;
	// 从汇点到源点更新流量
	while(u != source) {
		edges[p[u]].flow += df;
		edges[p[u]^1].flow -= df;
		u = edges[p[u]].from;
	}
	return df;
}

int max_flow() {
	int flow = 0,u = source;
	bfs();
	memset(num, 0, sizeof(num));
	num[0]=num_nodes;
	for(int i = 1; i <= num_nodes; i++) num[d[i]]++;
	memset(cur, 0, sizeof(cur));
	while(d[source] < num_nodes) {
		if(u == sink) {
			flow += augment();
			u = source;
		}
		bool advanced = false;
		for(int i = cur[u]; i < G[u].size(); i++) { 
			Edge& e = edges[G[u][i]];
			if (e.capacity > e.flow && d[u] == d[e.to] + 1) {
				advanced = true;
				p[e.to] = G[u][i];
				cur[u] = i;
				u = e.to;
				break;
			}
		}
		if(!advanced) { // retreat
			int m = num_nodes - 1;
			for(int ix = 0; ix < G[u].size(); ++ix) {
				if(edges[G[u][ix]].capacity > edges[G[u][ix]].flow)
					m = Min(m, d[edges[G[u][ix]].to]);
			}
			if(--num[d[u]] == 0) break; // gap 优化
			num[d[u] = m+1]++;
			cur[u] = 0;
			if(u != source) u = edges[p[u]].from;
		}
	}
	for(int i=1; i<=num_nodes; i++) {
		G[i].clear();
	}
	return flow;
}

int main() {
	scanf("%d",&T);
	int num_cases=1;
	while(T--) {
		build();
		printf("Case %d: %d\n",num_cases,max_flow());
		num_cases++;
	}
    return 0;
}

/*
//这个也能AC
//HDU 3549
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int max_nodes = 50;
const int max_edges = 3005;
const int INF = 100005;

struct Edge{
    int from,to,capacity,flow;
}edges[max_edges];

vector<int> G[max_nodes];
int T,num_nodes,num_edges;
int source,sink;	// 源点和汇点
int p[max_nodes];   // 可增广路上的上一条弧的编号
int num[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int d[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
bool visited[max_nodes];

int Min(int a,int b) {
    if(a>b) return b;return a;
}

void build() {
    scanf("%d%d",&num_nodes,&num_edges);
    memset(d,0,sizeof(d));
    int u,v,cap=0,cnt=0;
    for(int i=0; i<num_edges; i++) {
        scanf("%d%d%d",&u,&v,&cap);
        //加正向弧
        edges[cnt].from=u;
        edges[cnt].to=v;
        edges[cnt].capacity=cap;
        edges[cnt].flow=0;
        G[u].push_back(cnt++);
        //加反向弧
        edges[cnt].from=v;
        edges[cnt].to=u;
        edges[cnt].capacity=0;
        edges[cnt].flow=0;
        G[v].push_back(cnt++);
    }
    sink=num_nodes;
    source=1;
    d[sink] = 0;
    num[0]=num_edges;
}

// 预处理, 反向 BFS 构造 d 数组
void bfs() {
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    Q.push(sink);
    visited[sink] = 1;
    d[sink] = 0;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(int ix = 0; ix < G[u].size(); ++ix) {
            Edge &e = edges[(G[u][ix])^1];
            if(!visited[e.from] && e.capacity > e.flow) {
                visited[e.from] = true;
                d[e.from] = d[u] + 1;
                Q.push(e.from);
            }
        }
    }
}

// 增广
int augment() {
    int u = sink, df = INF;
    // 从汇点到源点通过 p 追踪增广路径, df 为一路上最小的残量
    while(u != source) {
        Edge &e = edges[p[u]];
        df = Min(df, e.capacity - e.flow);
        u = edges[p[u]].from;
    }
    u = sink;
    // 从汇点到源点更新流量
    while(u != source) {
        edges[p[u]].flow += df;
        edges[p[u]^1].flow -= df;
        u = edges[p[u]].from;
    }
    return df;
}

int max_flow() {
    int flow = 0,u = source;
    //bfs();
    memset(num, 0, sizeof(num));
    num[0]=num_nodes;
    for(int i = 1; i <= num_nodes; i++) num[d[i]]++;
    memset(cur, 0, sizeof(cur));
    while(d[source] < num_nodes) {
        if(u == sink) {
            flow += augment();
            u = source;
        }
        bool advanced = false;
        for(int i = cur[u]; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (e.capacity > e.flow && d[u] == d[e.to] + 1) {
                advanced = true;
                p[e.to] = G[u][i];
                cur[u] = i;
                u = e.to;
                break;
            }
        }
        if(!advanced) { // retreat
            int m = num_nodes - 1;
            for(int ix = 0; ix < G[u].size(); ++ix) {
                if(edges[G[u][ix]].capacity > edges[G[u][ix]].flow)
                    m = Min(m, d[edges[G[u][ix]].to]);
            }
            if(--num[d[u]] == 0) break; // gap 优化
            num[d[u] = m+1]++;
            cur[u] = 0;
            if(u != source) u = edges[p[u]].from;
        }
    }
    for(int i=1; i<=num_nodes; i++) {
        G[i].clear();
    }
    return flow;
}

int main() {
    scanf("%d",&T);
    int num_cases=1;
    while(T--) {
        build();
        printf("Case %d: %d\n",num_cases,max_flow());
        num_cases++;
    }
    return 0;
}

*/
