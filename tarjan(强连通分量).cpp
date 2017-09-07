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
