//bzoj1010(dp+斜率优化)
//dp[i]=dp[j]+(sum[i]-sum[j]-C)^2
//dp[j]+(sum[i]-sum[j]-C)^2 <= dp[k]+(sum[i]-sum[k]-C)^2
//dp[j]-dp[k]+(sum[j]+C)^2-(sum[k]+C)^2+2*sum[i]*(sum[k]-sum[j]) <= 0
//( dp[j]-dp[k]+(sum[j]+C)^2-(sum[k]+C)^2 ) / ( 2*(sum[j]-sum[k]) ) <= sum[i]
#include <iostream>
#include <cstdio>
#include <algorithm>
#define inf 1000000000
#define LL long long
#define N 50005
using namespace std;
LL n,len,C,a[N],sum[N],q[N],dp[N];
double slop(int j,int k) {
	return ((double)(dp[j]-dp[k]+(sum[j]+C)*(sum[j]+C)-(sum[k]+C)*(sum[k]+C))) / ((double)(2*(sum[j]-sum[k])));
}
void solve() {
	int l=1,r=0;
	q[++r]=0;
	for (int i=1; i<=n; i++) {
		while (l<r && slop(q[l+1], q[l]) <= ((double)(sum[i]))) l++;
		int t=q[l];
		dp[i]=dp[t]+(sum[i]-sum[t]-C)*(sum[i]-sum[t]-C);
		while (l<r && slop(i, q[r]) < slop(q[r], q[r-1])) r--;
		q[++r]=i;
	}
}
int main() {
	scanf("%lld%lld",&n,&len);
	C=len+1;
	for (int i=1; i<=n; i++) scanf("%lld",&a[i]);
	for (int i=1; i<=n; i++) sum[i]=sum[i-1]+a[i];
	for (int i=1; i<=n; i++) sum[i]+=i;
	solve();
	printf("%lld",dp[n]);
	return 0;
}