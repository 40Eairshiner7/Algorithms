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