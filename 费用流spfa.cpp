bool spfa() {
	for(int i=0; i<=T; i++) dis[i]=inf;
	int head=0,tail=1;
	dis[0]=0; q[0]=0; inq[0]=1;
	while(head!=tail) {
		int now=q[head++];
		if(head==1601) head=0;
		for(int i=last[now]; i; i=e[i].next)
			if(e[i].v && e[i].c+dis[now]<dis[e[i].to]) {
				dis[e[i].to]=e[i].c+dis[now];
				from[e[i].to]=i;
				if(!inq[e[i].to]) {
					inq[e[i].to]=1;
					if(dis[e[i].to]<dis[q[head]]) {
						head--;
						if(head==-1) head=1600;
						q[head]=e[i].to;
					}else {
						q[tail++]=e[i].to;
						if(tail==1601) tail=0;
					}
				}
			}
		inq[now]=0;
	}
	if(dis[T]==inf) return 0;
	return 1;
}
void mcf() {
	int x=inf;
	for(int i=from[T]; i; i=from[e[i].from]) x=min(e[i].v,x);
	for(int i=from[T]; i; i=from[e[i].from]) {
		ans+=x*e[i].c;
		e[i].v-=x;
		e[i^1].v+=x;
	}
}
int solve() { while (spfa()) mcf(); }





//int n,m,k,cnt,flow,S,T,timer,ss,tt,cc;
//int last[N],q[N],h[N],mark[N],inq[N],from[N];
//int A[N];
//LL ans,dis[N],d[N];
//struct edge{
//	int from,to,next,v,t,c;
//}e[M];
//LL Min(LL xx,LL yy) {
//	if (xx<yy) return xx;
//	return yy;
//}
//void insert(int u,int v,int w,int c) {
//	e[++cnt]=(edge){u,v,last[u],w,0,c};last[u]=cnt;
//	e[++cnt]=(edge){v,u,last[v],0,0,-c};last[v]=cnt;
//}
//void init() {
//	ans=0;cnt=1;S=0;T=n+2;timer=1;
//	memset(last,0,sizeof(last));
//	for (int i=1; i<=n; i++) {
//		A[i]=read();
//		if (A[i]-A[i-1]>0) insert(S, i, A[i]-A[i-1], 0);
//		else insert(i, T, A[i-1]-A[i], 0);
//		insert(i+1, i, INF, 0);
//	}
//	insert(n+1, T, A[n], 0);
//	for (int i=1; i<=m; i++) {
//		ss=read();
//		tt=read();
//		cc=read();
//		insert(ss, tt+1, INF, cc);
//	}
//}
//	bool spfa() {
//			for(int i=0; i<=T; i++) dis[i]=INF;
//			int head=0,tail=1;
//			dis[0]=0; q[0]=0; inq[0]=1;
//			while(head!=tail) {
//				int now=q[head++];
//				if(head==1501) head=0;
//				for(int i=last[now]; i; i=e[i].next)
//					if(e[i].v && e[i].c+dis[now]<dis[e[i].to]) {
//						dis[e[i].to]=e[i].c+dis[now];
//						from[e[i].to]=i;
//						if(!inq[e[i].to]) {
//							inq[e[i].to]=1;
//							q[tail++]=e[i].to;
//							if(tail==1001) tail=0;
//	//						if(dis[e[i].to]<dis[q[head]]) {
//	//							head--;
//	//							if(head==-1) head=1501;
//	//							q[head]=e[i].to;
//	//						}else {
//	//							q[tail++]=e[i].to;
//	//							if(tail==1501) tail=0;
//	//						}
//						}
//					}
//				inq[now]=0;
//			}
//			if(dis[T]==INF) return 0;
//			return 1;
//		}
//		void mcf() {
//			int x=INF;
//			for(int i=from[T]; i; i=from[e[i].from]) x=Min(e[i].v,x);
//			for(int i=from[T]; i; i=from[e[i].from]) {
//				ans+=x*e[i].c;
//				e[i].v-=x;
//				e[i^1].v+=x;
//			}
//		}
//		void solve() { while (spfa()) mcf(); }