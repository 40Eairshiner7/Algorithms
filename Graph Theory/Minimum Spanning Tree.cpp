//kruskal
struct edge{
	int a,b,sp;
}e[N];
int n,m,q,st,ed,minn,pre[205];
int finder(int a) {
	int r=a;
	while(pre[r]!=r) r=pre[r];
	int i=a;
	while(i!=r) {
		int j=pre[i];
		pre[i]=r;
		i=j;
	}
	return r;
}
void join(int x,int y) {
	int fx=finder(x),fy=finder(y);
	if (fx!=fy) pre[fx]=fy;
}
bool cmp(edge a,edge b) {
	return a.sp<b.sp;
}
int main() {
	int a,b,sp;
	while(scanf("%d%d",&n,&m)!=EOF) {
		for (int i=0; i<m; i++) {
			scanf("%d%d%d",&a,&b,&sp);
			e[i].a=a;  e[i].b=b;  e[i].sp=sp;
		}
		sort(e,e+m,cmp);
		scanf("%d",&q);
		for (int i=0; i<q; i++) {
			int flag=1;
			minn=INF;
			scanf("%d%d",&st,&ed);
			for (int j=0; j<m; j++) {
				for (int k=1; k<=n; k++) pre[k]=k;
				for (int k=j; k<m; k++) {
					join(e[k].a,e[k].b);
					if (finder(st)==finder(ed)) {
						flag=0;
						int cur=e[k].sp-e[j].sp;
						if (cur<minn) minn=cur;
						break;
					}
				}
			}
			if (flag==0) printf("%d\n",minn);
			else printf("-1\n");
		}
	}
	return 0;
}



//prim
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
const int INF=100000000;
const int MAXN=110;
bool vis[MAXN];
int lowc[MAXN],cost[MAXN][MAXN],n,m;
LL prim() {
	LL ans=0;
	memset(vis,false,sizeof(vis));
	vis[0]=true;
	for(int i=1; i<n; i++) lowc[i]=cost[0][i];
	for(int i=1; i<n; i++) {
		int minc=INF;
		int p=-1;
		for(int j=0; j<n; j++) {
			if(!vis[j] && minc>lowc[j]) {
				minc=lowc[j];
				p=j;
			}
		}
		if(minc==INF) return -1;
		ans+=minc;
		vis[p]=true;
		for(int j=0; j<n; j++) {
			if(!vis[j] && lowc[j]>cost[p][j]) lowc[j]=cost[p][j];
		}
	}
	return ans;
}
int main () {
	int a,b,c;
	while (scanf("%d%d",&m,&n),m!=0) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				cost[i][j]=INF;
				cost[j][i]=INF;
			}
		}
		for (int i=0; i<m; i++) {
			scanf("%d%d%d",&a,&b,&c);
			cost[a-1][b-1]=c;
			cost[b-1][a-1]=c;
		}
		LL result=prim();
		if (result!=-1) printf("%lld\n",result);
		else printf("?\n");
	}
}