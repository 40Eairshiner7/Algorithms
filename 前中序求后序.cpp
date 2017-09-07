//hdu1710(前序中序求后序 不能处理输入的数含有0的情况)
#include <iostream>
#include <cstdio>
using namespace std;
int pre[1005],in[1005],n,cnt;
int post[1005][3];
void dfs(int l,int r,int fa,int type) {
	if(l>r) return;
	int rt=++cnt;
	if(l==r) {
		post[fa][type]=in[l];
		//printf("%d ",in[l]);
		return;
	}
	for(int i=l; i<=r; i++) {
		if(in[i]==pre[rt]) {
			dfs(l,i-1,pre[rt],0);
			dfs(i+1,r,pre[rt],1);
			break;
		}
	}
	post[fa][type]=pre[rt];
	//printf("%d",pre[rt]);
	//if(rt>1) printf(" ");
}
void back(int num) {
	if (post[num][0]!=-1) back(post[num][0]);
	if (post[num][1]!=-1) back(post[num][1]);
	printf("%d",num);
	if (num!=pre[1]) printf(" ");
}
int main() {
	while(~scanf("%d",&n)) {
		for(int i=1; i<=n; i++) {
			scanf("%d",pre+i);
			post[i][0]=-1;
			post[i][1]=-1;
		}
		for(int i=1; i<=n; i++) scanf("%d",in+i);
		cnt=0;
		post[0][0]=post[0][1]=-1;
		dfs(1,n,0,0);
		back(pre[1]);
		printf("\n");
	}
}
/*

9
1 2 4 7 3 5 8 9 6
4 7 2 1 8 5 9 3 6

7 4 2 8 9 5 6 3 1

*/