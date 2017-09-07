#include <iostream>  
#include <cstdio>  
#include <cstring>  
using namespace std;  
int n,l,o,r,deep,i;  
int lr[10005][3];  
bool root[10005];  
void dfs(int cur,int curdeep) {  
	if (lr[cur][0]!=-1) dfs(lr[cur][0],curdeep+1);  
	if (lr[cur][1]!=-1) dfs(lr[cur][1],curdeep+1);  
	if ((lr[cur][1]==-1 || lr[cur][1]>cur) && (lr[cur][0]==-1 || cur>lr[cur][0]) && deep!=-1) {  
		if (deep<curdeep) deep=curdeep;  
	}else deep=-1;
}  
int main() {  
	scanf("%d",&n);   
	memset(root,true,sizeof(root));  
	deep=1;  
	for (i=0; i<n; i++) {  
		scanf("%d%d%d",&l,&o,&r);  
		lr[o][0]=l;  
		lr[o][1]=r;  
		if (l!=-1) root[l]=false;  
		if (r!=-1) root[r]=false;  
	}  
	for (i=1; i<=n; i++) if (root[i]==true) break;  
	dfs(i,1);  
	printf("%d",deep);  
	return 0;  
}
/*
5
-1 1 -1
1 2 3
-1 3 -1
2 4 5
-1 5 -1
*/