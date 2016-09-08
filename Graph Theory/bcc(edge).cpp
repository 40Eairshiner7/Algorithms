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