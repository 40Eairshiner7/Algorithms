#include <iostream>
#include <cstdio>
#include <cstring>
#define LL long long
using namespace std;
const LL N = 30005;
LL n,m,u,v,cnt,cur,ans,dir;
LL deep[N],ancestor[N][20],binary[20],head[N];
struct edge{
    LL next,to;
}e[2*N];
void init() {
    binary[0]=1;
    for (int i=1; i<=17; i++) binary[i]=2*binary[i-1];
}
void addedge(LL x,LL y) {
    e[++cnt].next=head[x],e[cnt].to=y,head[x]=cnt;
}
void getfa(LL x) {
    for (LL i=1; i<=16; i++) {
        if (deep[x]>=binary[i]) ancestor[x][i]=ancestor[ancestor[x][i-1]][i-1];
        else break;
    }
}
void dfs(LL cur) {
    getfa(cur);
    for (LL i=head[cur]; i!=0; i=e[i].next) {
        if (e[i].to != ancestor[cur][0]) {
            ancestor[e[i].to][0]=cur;
            deep[e[i].to]=deep[cur]+1;
            dfs(e[i].to);
        }
    }
}
LL lca(LL x,LL y) {
    if (deep[x]<deep[y]) swap(x, y);
    LL t=deep[x]-deep[y];
    for (LL i=0; binary[i]<=t; i++)
        if (t & binary[i]) x=ancestor[x][i];
    for (LL i=16; i>=0; i--)
        if (ancestor[x][i]!=ancestor[y][i])
            x=ancestor[x][i],y=ancestor[y][i];
    if (x==y) return x;
    return ancestor[x][0];
}
int main() {
    init();
    
    dfs(1);

    return 0;
}
