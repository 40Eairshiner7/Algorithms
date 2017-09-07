#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#define ll long long
#define inf 0x7fffffff
using namespace std;
ll a[15][15],deg[15];
int n,m;
ll det() {//求基尔霍夫矩阵去掉x行x列之后的行列式
    cout << endl;
	cout << endl;
	ll ans=1;
	for(int i=1;i<n;++i) {
		for(int j=i+1;j<n;++j) {
			while(a[j][i]) {
				ll t=a[i][i]/a[j][i];
				for(int k=i;k<n;k++) a[i][k]=(a[i][k]-a[j][k]*t);
				for(int k=i;k<n;k++) swap(a[i][k],a[j][k]);
				//ans=-ans;
			}
		}
		if(a[i][i]==0) return 0;
		ans*=a[i][i];
	}
	if(ans<0) ans=-ans;
	return ans;
}
int main() {
		scanf("%d%d",&n,&m);
		memset(a,0,sizeof(a));
		memset(deg,0,sizeof(deg));
		int u,v;
		for(int i=1;i<=m;++i) {
			scanf("%d%d",&u,&v);
			--a[u][v];--a[v][u];//邻接矩阵
			++deg[u];++deg[v];//度数矩阵
		}
		for(int i=1;i<=n;++i) a[i][i]=deg[i];
		printf("%lld\n",det());
	return 0;
}