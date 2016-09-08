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
