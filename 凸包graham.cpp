#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#define eps 1e-8
#define PI 3.1415926535897932
using namespace std;
const int N = 1015;
int n,top;
double ans,r;
struct data{
	double x,y;
}p[N],s[N];
double dis(data a,data b) { return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)); }
double cross(data p1,data p2,data p0) { return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y); }
bool cmp(data a,data b) {
	if(cross(a,b,p[0])==0)return dis(a,p[0])<dis(b,p[0]);
	return cross(a,b,p[0])>0;
}
void init() {
	for (int i=0; i<n; i++) {
		scanf("%lf%lf",&p[i].x,&p[i].y);
	}
}
void graham() {
	top=2;data t;
	int k=0;
	for(int i=1; i<n; i++) {
	    if( (p[k].y>p[i].y) || (p[k].y==p[i].y && p[k].x>p[i].x) )k=i;
	}
	t=p[0]; p[0]=p[k]; p[k]=t;
	sort(p+1,p+n,cmp);
	s[0]=p[0],s[1]=p[1],s[2]=p[2];
	for(int i=3; i<n; i++) {
		while(top && cross(p[i],s[top],s[top-1])>=0) top--;
        s[++top]=p[i];
	}
    s[++top]=p[0];
	for(int i=0; i<top; i++) ans+=dis(s[i],s[i+1]);
}
int main() {
	while (scanf("%d%lf",&n,&r)!=EOF) {
		init();
		graham();
		printf("%d\n",(int)(ans+0.5));
	}
	return 0;
}