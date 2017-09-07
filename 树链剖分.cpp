#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define inf 0x7fffffff
#define N 30005 
#define M 60005
using namespace std;
int n,q,cnt,sz;
int v[N],dep[N],size[N],head[N],fa[N];
int pos[N],belong[N];
struct data{int to,next; }e[M];
struct seg{int l,r,mx,sum; }t[100005];

void insert(int u,int v) {
	e[++cnt].to=v; e[cnt].next=head[u]; head[u]=cnt;
	e[++cnt].to=u; e[cnt].next=head[v]; head[v]=cnt;
}

//输入
void init() {
	scanf("%d",&n);
	for (int i=0; i<n-1; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		insert(x, y);
	}
	for (int i=1; i<=n; i++) scanf("%d",&v[i]);
}

//计算size 以此找到重边
void dfs1(int k) {
	size[k]=1;
	for (int i=head[k]; i; i=e[i].next) {
		if (e[i].to==fa[k]) continue;
		fa[e[i].to]=k;
		dep[e[i].to]=dep[k]+1;
		dfs1(e[i].to);
		size[k]+=size[e[i].to];
	}
}

//连接重边成重链
void dfs2(int k,int chain) {
	int m=0;
	pos[k]=++sz;//分配x结点在线段树中的编号
	belong[k]=chain;
	for (int i=head[k]; i; i=e[i].next)
		if (dep[e[i].to]>dep[k] && size[e[i].to]>size[m])
			m=e[i].to;//选择子树最大的儿子继承重链
	if(m==0) return;
	dfs2(m, chain);
	for (int i=head[k]; i; i=e[i].next)
		if (dep[e[i].to]>dep[k] && e[i].to!=m)
			dfs2(e[i].to, e[i].to);//其余儿子新开重链
}

//建线段树
void build(int k,int l,int r) {
	t[k].l=l,t[k].r=r;
	if (l==r) return;
	int mid=(l+r)/2;
	build(k*2, l, mid);
	build(k*2+1, mid+1, r);
}

//线段树单点修改
void change(int k,int x,int y) {	
	int l=t[k].l,r=t[k].r,mid=(l+r)/2;
	if (l==r) { t[k].mx=t[k].sum=y; return; }
	if (x<=mid) change(k*2, x, y);
	else change(k*2+1, x, y);
	t[k].mx=max(t[k*2].mx, t[k*2+1].mx);
	t[k].sum=t[k*2].sum+t[k*2+1].sum;
}

//线段树区间求和
int querySum(int k,int x,int y) {
	int l=t[k].l,r=t[k].r,mid=(l+r)/2;
	if(l==x && y==r) return t[k].sum;
	if (mid>=y) return querySum(k*2, x, y);
	else if(mid<x) return querySum(k*2+1, x, y);
	return querySum(k*2, x, mid)+querySum(k*2+1, mid+1, y);
}

//线段树区间求最大值
int queryMx(int k,int x,int y) {
	int l=t[k].l,r=t[k].r,mid=(l+r)/2;
	if(l==x && y==r) return t[k].mx;
	if (mid>=y) return queryMx(k*2, x, y);
	else if(mid<x) return queryMx(k*2+1, x, y);
	return max(queryMx(k*2, x, mid), queryMx(k*2+1, mid+1, y));
}

int solveSum(int x,int y) {
	int sum=0;
	while (belong[x]!=belong[y]) {
		//直到遇到公共祖先为止 dep值小的一边一直往上查询和 查询一次比较一次dep
		if (dep[belong[x]]<dep[belong[y]]) swap(x, y);
		sum+=querySum(1, pos[belong[x]], pos[x]);
		x=fa[belong[x]];
	}
	if (pos[x]>pos[y]) swap(x, y);
	sum+=querySum(1, pos[x], pos[y]);
	return sum;
}
int solveMx(int x,int y) {
	int mx=-inf;
	while (belong[x]!=belong[y]) {
		//直到遇到公共祖先为止 dep值小的一边一直往上查询最大值 查询一次比较一次dep
		if (dep[belong[x]]<dep[belong[y]]) swap(x, y);
		mx=max(mx, queryMx(1, pos[belong[x]], pos[x]));
		x=fa[belong[x]];
	}
	if (pos[x]>pos[y]) swap(x, y);
	mx=max(mx, queryMx(1, pos[x], pos[y]));
	return mx;
}
void solve() {
	build(1, 1, n);
	for (int i=1; i<=n; i++) change(1, pos[i], v[i]);
	scanf("%d",&q);
	char str[10];
	for (int i=0; i<q; i++) {
		int x,y; scanf("%s%d%d",str,&x,&y);
		if (str[0]=='C') { v[x]=y; change(1, pos[x], y); }
		else {
			if(str[1]=='M') printf("%d\n",solveMx(x, y));
			else printf("%d\n",solveSum(x, y));
		}
	}
}
int main() {
	init();
	dfs1(1);
	dfs2(1, 1);
	solve();
	return 0;
}