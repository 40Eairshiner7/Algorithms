//euler circuit(fleury)
//每遍历出一个连通图，如果发现当前点已经无法走通，则倒退输出整个连通图到某个可走通的点，该点为桥的端点，继续遍历连通块肯定可以回到该点，继续寻找下一块连通图
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#define MAXN 1005
using namespace std;
int n,edge[MAXN][MAXN];
stack<int> s;
void dfs(int x) {
    int i;
    s.push(x);
    for (int i=0; i<n; i++) {
        if (edge[i][x]>0) {
            edge[i][x]=0; edge[x][i]=0;
            dfs(i);
            break;
        }
    }
}
void fleury(int x) {
    int i,flag;
    s.push(x);
    while (!s.empty()) {
        flag=0;
        for (int i=0; i<n; i++) {
            if (edge[s.top()][i]>0) {
                flag=1; break;
            }
        }
        if (flag==0) {
            printf("%d ",s.top()+1);
            s.pop();
        }
        else {
            int tmp=s.top();
            s.pop();
            dfs(tmp);
        }
    }
}
int main() {
    return 0;
    
}