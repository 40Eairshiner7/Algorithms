//strongly connected components
int n,m,dfn[N],low[N],stp,scnt,s[N],scc,vis[N],num[N];
bool ins[N];
vector<int> vec[N];
int Min(int a,int b) {
	if (a>b) return b;
	return a;
}
void tarjan(int x) {
	dfn[x]=low[x]=++stp;
	ins[x]=1, s[++scnt]=x;
	for(int i=0; i<vec[x].size(); i++) {
		int tmp=vec[x][i];
		if(!dfn[tmp]) {
			tarjan(tmp);
			low[x]=Min(low[x],low[tmp]);
		}
		else if(ins[tmp]) {
			low[x]=Min(low[x],dfn[tmp]);
		}
	}
	if(dfn[x]==low[x]) {
		scc++;
		do{
			tmp=s[scnt--];
			ins[tmp]=false;
			vis[tmp]=scc;
			num[scc]++;
		}while (tmp!=x);
	}
}
void find_scc(){
	stamp=scc=scnt=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(instack,0,sizeof(instack));
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
}