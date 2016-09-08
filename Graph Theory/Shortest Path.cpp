//Dijkstra
#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN=2010;
const int INF=10000;
bool vis[MAXN];
int cost[MAXN][MAXN],lowcost[MAXN],n,bg;
void dij(){
	for(int i=0; i<n; i++) {
		lowcost[i]=INF;
		vis[i]=false;
	}
	lowcost[bg]=0;
	for(int j=0; j<n; j++) {
		int k=-1;
		int minn=INF;
		for(int i=0; i<n; i++) {
			if(!vis[i] && lowcost[i]<minn) {
				minn=lowcost[i];
				k=i;
			}
		}
		if(k == -1) break;
		vis[k]=true;
		for(int i=0; i<n; i++) {
			if(!vis[i] && lowcost[k]+cost[k][i]<lowcost[i]) {
				lowcost[i]=lowcost[k]+cost[k][i];
			}
		}
	}
}
int main() {
	int m;
	scanf("%d%d",&m,&n);
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i!=j) cost[i][j]=INF;
			if (i!=j) cost[j][i]=INF;
			if (i==j) cost[i][i]=0;
		}
	}
	int a,b,c;
	for (int i=0; i<m; i++) {
		scanf("%d%d%d",&a,&b,&c);
		cost[a-1][b-1]=c;
		cost[b-1][a-1]=c;
	}
	bg=n-1;
	dij();
	printf("%d",lowcost[0]);
	return 0;
}



//spfa
#include <iostream>
#include <cstdio>
#define LL __int64
using namespace std;
const int MAXN=1000005;
const int INF=1000000005;
int n,m;
struct edge {
	int v,next,cost;
}e[MAXN];
struct node {
	int ed;
}u[MAXN];
bool vis[MAXN];
LL dist[MAXN];
int q[3*MAXN];
int input[MAXN][4];
void addedge (int a,int b,int cost,int i) {
	e[i].v=b;
	e[i].next=u[a].ed;
	e[i].cost=cost;
	u[a].ed=i;
}
void spfa(int s) {
	memset(vis, false, sizeof(vis));
	memset(q, 0, sizeof(q));
	for(int i=1; i<=n; i++) dist[i]=INF;
	vis[s]=true; dist[s]=0; q[0]=s;
	int push=1,pop=0;
	while(push!=pop){
		int cur=q[pop]; 
		vis[cur]=false;
		for(int i=u[cur].ed; i!=-1; i=e[i].next) {
			int v=e[i].v;
			if(dist[v] > dist[cur]+e[i].cost) {
				dist[v] = dist[cur]+e[i].cost;
				if(!vis[v]) {
					vis[v]=true; 
					q[push++]=v;
				}
			}
		}
		pop++;
	}
}

int main() {
	int t;
	scanf("%d",&t);
	while (t--) {
		LL result=0;
		scanf("%d%d",&n,&m);
		for (int i=1; i<=n; i++) u[i].ed=-1;
		for (int i=0; i<m; i++) {
			scanf("%d%d%d",&input[i][0],&input[i][1],&input[i][2]);
			addedge(input[i][0],input[i][1],input[i][2],i);
		}
		spfa(1);
		for (int i=1; i<=n; i++) result+=dist[i];
		for (int i=1; i<=n; i++) u[i].ed=-1;
		for (int i=0; i<m; i++) addedge(input[i][1],input[i][0],input[i][2],i);
		spfa(1);
		for (int i=1; i<=n; i++) result+=dist[i];
		printf("%I64d\n",result);
	}
	return 0;
}