const LL N=200005;
const LL INF=1000000000005;
LL n,m,k,tot,vis[N],a[N],cnt,u,v,w;
LL dis[N],head[N];
struct edge{
	LL to,w,next;
}e[2*N];
struct node{
	LL v,c;
	node(LL _v=0,LL _c=0):v(_v),c(_c){}
	bool operator <(const node &r) const { return c>r.c; }
};
void init() {
	cnt=1;
	memset(head, 0, sizeof(head));
}
void insert(LL u,LL v,LL w) {
	e[++cnt]=(edge){v,w,head[u]};head[u]=cnt;
}
void dij(){
	for(LL i=0; i<=tot; i++) {
		dis[i]=INF;
		vis[i]=false;
	}
	priority_queue<node> que;
	while (!que.empty()) que.pop();
	que.push(node(0, 0));
	dis[0]=0;
	node cur;
	while (!que.empty()) {
		cur=que.top();que.pop();
		LL u=cur.v;
		if(vis[u]) continue; 
		vis[u]=true;
		for (LL i=head[u]; i; i=e[i].next) {
			v=e[i].to,w=e[i].w;
			if(!vis[v] && dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				que.push(node(v,dis[v]));
			}
		}
	}
}