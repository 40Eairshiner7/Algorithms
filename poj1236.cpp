/*
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define M 100100
#define N 5000
using namespace std;
int n,m,cnt,t,divg,belong[N],head[M],Next[M],to[M],dfn[N],low[N],in[N],out[N],p,stack[N],innum,outnum;
bool vis[N],fg[N];
inline void add(int u,int v) 
{
	     to[cnt]=v; Next[cnt]=head[u]; head[u]=cnt++;
}
void read()
{
     memset(vis,0,sizeof vis);
     memset(dfn,0,sizeof dfn);
     memset(in,0,sizeof in);
     memset(out,0,sizeof out);
     memset(head,-1,sizeof head);cnt=0;
     divg=0; p=0; t=0;
     scanf("%d",&n);
     for(int i=1,a;i<=n;i++)
         while(scanf("%d",&a),a) add(i,a);
 }
 void dfs(int u)
 {
     t++;
     dfn[u]=low[u]=t;
     stack[++p]=u; fg[u]=true;
     for(int i=head[u];~i;i=Next[i])
     {
         if(!dfn[to[i]])
         {
             dfs(to[i]);
             low[u]=min(low[u],low[to[i]]);
         }
         else if(fg[to[i]]) low[u]=min(low[u],dfn[to[i]]);
     }
     if(dfn[u]==low[u])
     {
         divg++;
         int tmp=-1;
         while(tmp!=u)
         {
             tmp=stack[p--];
             belong[tmp]=divg;
             fg[tmp]=false;
         }
     }
 }
 void go()
 {
     for(int i=1;i<=n;i++)
         if(!dfn[i]) dfs(i);
     for(int i=1;i<=n;i++)
         for(int j=head[i];~j;j=Next[j])
             if(belong[i]!=belong[to[j]])
                 out[belong[i]]++,in[belong[to[j]]]++;
     innum=outnum=0;
     for(int i=1;i<=divg;i++)
     {
         if(!in[i]) innum++;
         if(!out[i]) outnum++;
     }
     printf("%d\n",innum);
     if(divg==1) printf("0\n");
     else printf("%d\n",max(innum,outnum));
 }
 int main()
 {
     read();
     go();
     return 0;
 }
*/


#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1005;
int n,m,dfn[N],low[N],stp,scnt,s[N],scc,vis[N],incnt[N],outcnt[N];
bool ins[N];
vector<int> vec[N];
int Min(int a,int b) { if (a>b) return b; return a; }
int Max(int a,int b) { if (a<b) return b; return a; }
void tarjan(int x) {
	dfn[x]=low[x]=++stp;
	ins[x]=true, s[++scnt]=x;
	for(int i=0; i<vec[x].size(); i++) {
		int tmp=vec[x][i];
		if(!dfn[tmp]) {
			tarjan(tmp);
			low[x]=Min(low[x],low[tmp]);
		}
		else if(ins[tmp]) low[x]=Min(low[x],dfn[tmp]);
	}
	if(dfn[x]==low[x]) {
		scc++;
		int tmp;
		do{
			tmp=s[scnt--];
			ins[tmp]=false;
			vis[tmp]=scc;
		}while (tmp!=x);
	}
}
void find_scc(){
	stp=scc=scnt=0;
	memset(incnt, 0, sizeof(incnt));
	memset(outcnt, 0, sizeof(outcnt));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(ins,false,sizeof(ins));
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
}
int main() {
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		while (scanf("%d",&m),m!=0) {
			if (m==0) break;
			vec[i].push_back(m);
		}
	}
	find_scc();
	for (int i=1; i<=n; i++) {
		for (int j=0; j<vec[i].size(); j++) {
			if (dfn[i]==dfn[vec[i][j]]) continue;
			incnt[dfn[i]]++;
			outcnt[dfn[vec[i][j]]]++;
		}
	}
	int ans1=0,ans2=0;
	for (int i=1; i<=n; i++) {
		if (incnt[i]==0) ans1++;
		if (outcnt[i]==0) ans2++;
	}
	printf("%d\n%d\n",ans1,ans2);
	return 0;
}


/*

Sample Input
5
2 4 3 0
4 5 0
0
0
1 0
Sample Output
1
2

*/