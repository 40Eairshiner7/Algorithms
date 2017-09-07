#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define maxn 50005
#define eps 1e-8
using namespace std;
struct P{
	double x,y;
};
P operator -(P a,P b) {
	P t;
	t.x=a.x-b.x,t.y=a.y-b.y;
	return t;
}
bool cmp(P a,P b) { if (fabs(a.x-b.x)<eps) return a.y<b.y; return a.x<b.x; }
int dis(P a) { return a.x*a.x+a.y*a.y; }
double cross(P a,P b) { return a.x*b.y-a.y*b.x; }
int n;
P p[maxn],CH[maxn];
int CovexHull(){
	sort(p+1,p+n+1,cmp);
	int m=0;
	for(int i=1;i<=n;i++){
		while(m>1&&cross(CH[m]-CH[m-1],p[i]-CH[m-1])<=0)m--;
		CH[++m]=p[i];
	}
	int k=m;
	for(int i=n-1;i>=1;i--){
		while(m>k&&cross(CH[m]-CH[m-1],p[i]-CH[m-1])<=0)m--;
		CH[++m]=p[i];
	}
	return m;
}
int RotatingCalipers(int m){
	int ans=0;
	CH[0]=CH[m];
	int j=1;
	for (int i=1; i<=m; i++) {
		while (cross(CH[i]-CH[i-1], CH[j%m+1]-CH[i-1])>cross(CH[i]-CH[i-1], CH[j]-CH[i-1])) j=j%m+1;
		ans=max(ans, max( max(dis(CH[j]-CH[i]),dis(CH[j]-CH[i-1])) , max(dis(CH[j%m+1]-CH[i]),dis(CH[j%m+1]-CH[i-1]))) );
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lf%lf",&p[i].x,&p[i].y);
	int m=CovexHull();
	int ans=RotatingCalipers(m);
	printf("%d\n",ans);
	return 0;
}