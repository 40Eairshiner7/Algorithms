#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
using namespace std;
const int N = 50005;
const int M = 50005;
struct data{
	int l,r,pos,id;
	LL nu,de;
}q[N];
int n,m,block,s[N],a[N];
LL ans;
LL gcd(LL x,LL y) { return x == 0 ? y : gcd(y%x,x); }
bool cmp(data x,data y) {
	if (x.pos==y.pos) return x.r<y.r;
	return x.pos<y.pos;
}
bool cmp_id(data x,data y) { return x.id<y.id; }
void init() {
	ans=0;
	memset(s, 0, sizeof(s));
	for (int i=1; i<=n; i++) scanf("%d",&a[i]);
	for (int i=1; i<=m; i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].pos=(q[i].l-1)/block+1;
		q[i].id=i;
	}
}
void update(int num,int add) {
	ans-=(s[num])*(s[num]);
	s[num]+=add;
	ans+=(s[num])*(s[num]);
}
void solve() {
	for (int i=1,l=1,r=0; i<=m; i++) {
		for (; r<q[i].r; r++) update(a[r+1], 1);
		for (; r>q[i].r; r--) update(a[r], -1);
		for (; l<q[i].l; l++) update(a[l], -1);
		for (; l>q[i].l; l--) update(a[l-1], 1);
		if (q[i].l==q[i].r) {
			q[i].nu=0,q[i].de=1;
			continue;
		}
		q[i].nu=ans-((LL)q[i].r-(LL)q[i].l+1);
		q[i].de=(LL)(q[i].r-q[i].l+1)*(LL)(q[i].r-q[i].l);
		LL k=gcd((LL)q[i].nu, (LL)q[i].de);
		q[i].nu/=k,q[i].de/=k;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	block=sqrt(n);
	init();
	sort(q+1, q+m+1, cmp);
	solve();
	sort(q+1, q+m+1, cmp_id);
	for (int i=1; i<=m; i++) {
		printf("%lld/%lld\n",q[i].nu,q[i].de);
	}
	return 0;
}