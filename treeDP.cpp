#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
struct edge{
    int v,w;
};
vector<edge>E[100004];
int sum1[100004];
int sum2[100004];
int mod=707063423;
int f[100005];
int sum=0;
void addedge(int u,int v,int w){
    edge x;
    x.v=u;
    x.w=w;
    E[v].push_back(x);
    x.v=v;
    E[u].push_back(x);
}
void dfs1(int root,int fa,int w)
{
    for(int i=0;i<E[root].size();i++){
        if(E[root][i].v!=fa)dfs1(E[root][i].v,root,E[root][i].w);
    }
    sum1[fa]+=w*f[root]+sum1[root];
    sum1[fa]%=mod;
    f[fa]+=f[root];
}
void dfs2(int root,int fa)
{
    for(int i=0;i<E[root].size();i++) {
        edge x=E[root][i];
        int u=root;
        int v=x.v;
        int w=x.w;
        if(v==fa)continue ;
        sum2[v]=sum2[root]-w*f[v];
        sum2[v]+=(sum-f[v])*w;
        if(v!=fa)dfs2(v,root);
    }
}
int main()
{
    int n,i;
    //freopen("1.in","r",stdin);
    cin>>n;
    for(i=1;i<=n;i++){
        scanf("%d",&f[i]);
        sum+=f[i];
    }
    for(i=1;i<=n-1;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
    }
    dfs1(1,0,0);
    sum2[1]=sum1[1];
    dfs2(1,0);
    int p;
    cin>>p;
    while(p--){
        int x;
        scanf("%d",&x);
        while(sum2[x]<0)sum2[x]+=mod;
        printf("%d\n",sum2[x]%mod);
    }

}