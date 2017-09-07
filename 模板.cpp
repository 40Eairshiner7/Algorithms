//segment tree
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

const int maxp=200005;
int a[maxp],st[4*maxp+5];
int maxn(int a,int b) {
    if (a>b) return a;return b;
}
void build(int node,int bg,int ed) {
    if (bg==ed) {
        st[node]=a[bg];
        return;
    }
    build(node*2,bg,(bg+ed)/2);
    build(node*2+1,(bg+ed)/2+1,ed);
    st[node]=maxn(st[node*2],st[node*2+1]);
    return;
}
void update(int node,int bg,int ed,int pos,int num) {
    if (bg==ed) {
        st[node]=num;
        return;
    }
    int mid=(bg+ed)/2;
    if (pos<=mid) update(node*2,bg,(bg+ed)/2,pos,num);
    else update(node*2+1,(bg+ed)/2+1,ed,pos,num);
    st[node]=maxn(st[node*2],st[node*2+1]);
    return;
}
int query(int node,int bg,int ed,int l,int r) {
    if (ed<l || bg>r) return -1;
    if (bg>=l && ed<=r) return st[node];
    int p1=query(node*2,bg,(bg+ed)/2,l,r);
    int p2=query(node*2+1,(bg+ed)/2+1,ed,l,r);
    if (p2==-1) return p1;
    if (p1==-1) return p2;
    if (p1>p2) return p1;
    return p2;
}
int main() {
    int n,m;
    while (scanf("%d%d",&n,&m)!=EOF) {
        memset(a,0,sizeof(a));
        memset(st,0,sizeof(st));
        for (int i=0; i<n; i++) {
            scanf("%d",&a[i]);
        }
        build(1,0,n);
        string s;
        for (int i=0; i<m; i++) {
            cin >> s;
            if (s=="Q") {
                int l,r;
                scanf("%d%d",&l,&r);
                printf("%d\n",query(1,0,n,l-1,r-1));
            }
            else if (s=="U") {
                int p,num;
                scanf("%d%d",&p,&num);
                update(1,0,n,p-1,num);
            }
        }
    }
    return 0;
}




//dijkstra
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
//dijkstra+heap(nlogn)
const int INF=0x3f3f3f3f;
const int MAXN=1000010;
struct qnode{
    int v,c;
    qnode(int _v=0,int _c=0):v(_v),c(_c){}
    bool operator <(const qnode &r)const {
        return c>r.c;
    }
};
struct Edge{
    int v,cost;
    Edge(int _v=0,int _cost=0):v(_v),cost(_cost){}
};
vector<Edge>E[MAXN];
bool vis[MAXN];
int dist[MAXN];
void Dijkstra(int n,int start)//点的编号从1开始
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dist[i]=INF;
    priority_queue<qnode>que;
    while(!que.empty()) que.pop();
    dist[start]=0;
    que.push(qnode(start,0));
    qnode tmp;
    while(!que.empty()) {
        tmp=que.top();
        que.pop();
        int u=tmp.v;
        if(vis[u])continue;
        vis[u]=true;
        for(int i=0;i<E[u].size();i++) {
            int v=E[tmp.v][i].v;
            int cost=E[u][i].cost;
            if(!vis[v]&&dist[v]>dist[u]+cost) {
                dist[v]=dist[u]+cost; que.push(qnode(v,dist[v]));
            }
        }
    }
}
void addedge(int u,int v,int w) {
    E[u].push_back(Edge(v,w));
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




//quick_pow
while(n)
{
	if(n&1) res= res * a;
	n >>= 1;
	a = a * a;
}




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




//dfs hungarian
int ix,n,m,matching[N],ei,nd[N];;
bool check[N];
struct Edge {
    int to,next;
}e[N];
bool dfs(int u)
{
    for (int i = nd[u]; i != -1; i=e[i].next) {
        int v = e[i].to;
        if (!check[v]) {
            check[v] = true;
            if (matching[v] == -1 || dfs(matching[v])) {
                matching[v] = u;
                matching[u] = v;
                return true;
            }
        }
    }
    return false;
}
int hungarian() {
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    for (int u=0; u<n; ++u) {
        if (matching[u] == -1) {
            memset(check, false, sizeof(check));
            if (dfs(u)) ++ans;
        }
    }
    return ans;
}
int main() {
	while (scanf("%d",&n)!=EOF) {
		ei=0;
		memset(nd,-1,sizeof(nd));
		for (int i=0; i<n; i++) {
			int num,id,to;
			scanf("%d: (%d)",&id,&num);
			for (int j=0; j<num; j++) {
				scanf("%d",&to);
				e[ei].to=to;
				e[ei].next=nd[id];
				nd[id]=ei++;
			}
		}
		int ans=hungarian();
		printf("%d\n",n-ans);
	}
	return 0;
}




//bfs hungarian
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#define LL __int64
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define N 1005
#define INF 1000000005

using namespace std;
int n,matching[N],ei,nd[N],que[N],pre[N],push,pop,check[N];

struct Edge {
    int to,Next;
}e[N];

int Hungarian() {
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    memset(check, -1, sizeof(check));
    for (int i=0; i<n; ++i) {
        if (matching[i] == -1) {
            push=1; pop=0;
            que[0] = i;
            pre[i] = -1;
            bool flag = false;
            while (push!=pop && !flag) {
                int u = que[pop];
                for (int ix = nd[u]; (ix != -1 && !flag); ix = e[ix].Next) {
                    int v = e[ix].to;
                    if (check[v] != i) {
                        check[v] = i;
                        que[push++]=matching[v];
                        if (matching[v] >= 0) pre[matching[v]] = u;
                        else {
                            flag = true;
                            int d=u, f=v;
                            while (d != -1) {
                                int t = matching[d];
                                matching[d] = f;
                                matching[f] = d;
                                d = pre[d];
                                f = t;
                            }
                        }
                    }
                }
                pop++;
            }
            if (matching[i] != -1) ++ans;
        }
    }
    return ans;
}

int main() {
	while (scanf("%d",&n)!=EOF) {
		ei=0;
		memset(nd,-1,sizeof(nd));
		for (int i=0; i<n; i++) {
			int num,id,to;
			scanf("%d: (%d)",&id,&num);
			for (int j=0; j<num; j++) {
				scanf("%d",&to);
				e[ei].to=to;
				e[ei].Next=nd[id];
				nd[id]=ei++;
			}
		}
		int ans=Hungarian();
		printf("%d\n",n-ans);
	}
	return 0;
}




//bfs hungarian
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cstdlib>
#define LL __int64
#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((a)<(b)?(a):(b))
#define N 1005
#define INF 1000000005

using namespace std;
int n,m,matching[N],ei,nd[N],que[N],pre[N],push,pop,check[N];

struct Edge {
    int to,Next;
}e[N];

queue<int> Q;
vector<int> G[N];
typedef vector<int>::iterator iterator_t;
int Hungarian()
{
    int ans = 0;
    memset(matching, -1, sizeof(matching));
    memset(check, -1, sizeof(check));
    for (int i=0; i<n; ++i) {
        if (matching[i] == -1) {
            while (!Q.empty()) Q.pop();
            Q.push(i);
            pre[i] = -1;
            bool flag = false;
            while (!Q.empty() && !flag) {
                int u = Q.front();
                for (iterator_t ix = G[u].begin(); ix != G[u].end() && !flag; ++ix) {
                    int v = *ix;
                    if (check[v] != i) {
                        check[v] = i;
                        Q.push(matching[v]);
                        if (matching[v] >= 0) {
                            pre[matching[v]] = u;
                        } else {
                            flag = true;
                            int d=u, f=v;
                            while (d != -1) {
                                int t = matching[d];
                                matching[d] = f;
                                matching[f] = d;
                                d = pre[d];
                                f = t;
                            }
                        }
                    }
                }
                Q.pop();
            }
            if (matching[i] != -1) ++ans;
        }
    }
    return ans;
}

int main() {
	while (scanf("%d",&n)!=EOF) {
		ei=0;
		memset(nd,-1,sizeof(nd));
		for (int i=0; i<n; i++) {
			G[i].clear();
			int num,id,to;
			scanf("%d: (%d)",&id,&num);
			for(int j=0; j<num; j++) {
                scanf("%d",&to);
                G[id].push_back(to);
            }
		}
		int ans=Hungarian();
		printf("%d\n",n-ans);
	}
	return 0;
}




//tarjan(point)
void tarjan(int index,int fa) {
    int child=0;
    low[index]=dfn[index]=++stamp;
    for(int i=0; i<vec[index].size(); i++) {
        int tmp=vec[index][i];
        if(!dfn[tmp]) {
            child++;
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>=dfn[index]) iscut[index]++;
            //if there are at least one v that low[v]>=dfn[u],u is cut point.
        }
        else low[index]=min(low[index],dfn[tmp]);
    }
    if(index==1) iscut[index]=child-1;
}




//tarjan(edge)
void tarjan(int index,int fa) {
    dfn[index]=low[index]=++stamp;
    for(int i=0; i<vec[index].size(); i++) {
        int tmp=vec[index][i];
        if(!dfn[tmp]) {
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>dfn[index]) cnt++;
        }
        else low[index]=min(low[index],dfn[tmp]);
    }
}




//fenwick tree
int bit[N],a[N];
int lowbit(int x){
    return x&(-x);
}
void plus(int pos,int num) {
    while(pos <= n) {
        bit[pos] += num;
        pos += lowbit(pos);
    }
}
int sum(int end) {
    int ans = 0;
    while(end > 0){
        ans += bit[end];
        end -= lowbit(end);
    }
    return ans;
}




//strongly connected components
int n,m,dfn[N],low[N],stp,scnt,s[N],scc,vis[N],num[N],tmp,u,v,outcnt[N];
bool ins[N];
vector<int> vec[N];
int Min(int a,int b) { if (a>b) return b; return a; }
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
        int tmp=-1;
        while (tmp!=x) {
            tmp=s[scnt--];
            vis[tmp]=scc;
            ins[tmp]=false;
            num[scc]++;
        }
    }
}
void find_scc(){
    stp=scc=scnt=0;
    memset(outcnt, 0, sizeof(outcnt));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(ins, false, sizeof(ins));
    for(int i=1; i<=n; i++)
        if(!dfn[i])
            tarjan(i);
}




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




//bcc(point)
#include <iostream>
#include <cstring>
using namespace std;
struct Edge{
    int u,v;
}e[maxm];
int n,m,stamp,dfn[maxn],low[maxn],iscut[maxn],bccno[maxn],scnt,stack[maxn],bcc_cnt;
//iscut[index]纪录点index是不是割点，bccno[index]纪录index点属于第几个双连通分量，bcc_cnt为双连通的编号，scnt纪录栈顶元素编号
vector<int> vec[maxn],bcc[maxn];
void tarjan(int index,int fa) {
    int child=0,tmp;
    dfn[index]=low[index]=++stamp;
    //重新开始遍历一个新的点
    for(int i=0; i<vec[index].size(); i++) {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp]) {
            stack[++scnt]=vec[index][i],child++;//将边入栈
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);//更新low[index]
            if(low[tmp]>=dfn[index]) {//如果low[tmp]>=dfn[index]则遍历出一个点双连通分量
                iscut[index]=1;
                bcc[++bcc_cnt].clear();
                while(1) {
                    //将遍历到的点双连通分量从头到尾推入bcc[bcc_cnt]
                    int num=stack[scnt--];
                    if(bccno[e[num].u]!=bcc_cnt) {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u]=bcc_cnt;
                    }
                    if(bccno[e[num].v]!=bcc_cnt) {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v]=bcc_cnt;
                    }
                    //将所有边从起始点到终止点都记录下来
                    if(e[num].u==index && e[num].v==tmp) break;
                }
            }
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa) {
            stack[++scnt]=vec[index][i];
            low[index]=min(low[index], dfn[tmp]);
        }
        //返祖边，无法形成双连通分量，更新当前节点index的low[index]
    }
    if(fa<0 && child==1) iscut[index]=0;
}
void find_bcc() {
    // 割顶的bccno值无意义 
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
}
int main() {
    return 0;
}




//bcc(edge)
#include <iostream>
#include <cstring>
using namespace std;
struct Edge{
    int u,v;
}e[maxm];
int n,m,stamp,dfn[maxn],low[maxn],bccno[maxn],bcc_cnt;
vector<int> vec[maxn],bcc[maxn];
bool g[maxn][maxn],isbridge[maxm];
void tarjan(int index,int fa) {
    int tmp;
    dfn[index]=low[index]=++stamp;
    for(int i=0; i<vec[index].size(); i++) {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp]) {
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>dfn[index])
                isbridge[vec[index][i]]=isbridge[vec[index][i]^1]=1;
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa)
            low[index]=min(low[index], dfn[tmp]);
    }
}
void dfs(int index) {
    dfn[index]=1;
    bccno[index]=bcc_cnt;
    for(int i=0; i<vec[index].size(); i++) {
        int tmp=vec[index][i];
        if(isbridge[tmp]) continue;
        //遇到桥则跳过，相当于删除所有的桥
        if(!dfn[e[tmp].v]) dfs(e[tmp].v);
    }
}
void find_bcc(){
    bcc_cnt=stamp=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(isbridge,0,sizeof(isbridge));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    for(int i=1; i<=n; i++)
        if(!dfn[i])
            tarjan(i, -1);
    memset(dfn,0,sizeof(dfn));
    //用tarjan算法找出所有桥以后，通过删除所有桥找到所有边双连通分量
    for(int i=1; i<=n; i++)
        if(!dfn[i]) {
            bcc_cnt++;
            dfs(i);
            //深搜遍历所有该点所在的边双连通分量所关联的点，并标记，从而计算双连通分量个数
        }
    }
}
int main() {
    return 0;
}




//euler circuit(fleury)
//每遍历出一个连通图，如果发现当前点已经无法走通，则倒退输出整个连通图到某个可走通的点，该点为桥的端点，继续遍历连通块肯定可以回到该点，继续寻找下一块连通图
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#define MAXN 1005
using namespace std;
int n,edge[MAXN][MAXN];
stack<int> s;
void dfs(int x) {
    int i;
    s.push(x);
    for (int i=0; i<n; i++) {
        if (edge[i][x]>0) {
            edge[i][x]=0; edge[x][i]=0;
            dfs(i);
            break;
        }
    }
}
void fleury(int x) {
    int i,flag;
    s.push(x);
    while (!s.empty()) {
        flag=0;
        for (int i=0; i<n; i++) {
            if (edge[s.top()][i]>0) {
                flag=1; break;
            }
        }
        if (flag==0) {
            printf("%d ",s.top()+1);
            s.pop();
        }
        else {
            int tmp=s.top();
            s.pop();
            dfs(tmp);
        }
    }
}
int main() {
    return 0;
}
