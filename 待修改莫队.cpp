#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define LL long long
using namespace std;
const int N = 10005;
const int M = 1000005;
struct data{
	int l,r,lpos,rpos,id,tim,last,res;
}q[N],c[N];
int n,m,size,s[M],a[N],cnt1,cnt2,num[N],ans,l,r,tim;
char str[3];

bool cmp(data x,data y) {
	if (x.lpos==y.lpos) {
		if (x.rpos==y.rpos) return x.tim<y.tim;
		return x.rpos<y.rpos;
	}
	return x.tim<y.tim;
}
bool cmp_id(data x,data y) { return x.id<y.id; }

void init() {
	cnt1=cnt2=ans=0;
	memset(s, 0, sizeof(s));
	for (int i=1; i<=n; i++) scanf("%d",&a[i]),num[i]=a[i];
	for (int i=1; i<=m; i++) {
		scanf("%s",str);
		if (str[0]=='Q') {
			++cnt1;
			scanf("%d%d",&q[cnt1].l,&q[cnt1].r);
			q[cnt1].lpos=(q[cnt1].l-1)/size+1;
			q[cnt1].rpos=(q[cnt1].r-1)/size+1;
			q[cnt1].id=cnt1;
			q[cnt1].tim=cnt2;
		}else if (str[0]=='R') {
			++cnt2;
			scanf("%d%d",&c[cnt2].l,&c[cnt2].r);
			c[cnt2].last=num[c[cnt2].l];
			num[c[cnt2].l]=c[cnt2].r;
		}
	}
}
void change(int from,int to) {
	if (l<=from && from<=r) {
		if (s[a[from]]==1) ans--;
		s[a[from]]--;
		if (s[to]==0) ans++;
		s[to]++;
	}
	a[from]=to;
}
void update(int pos,int type) {
	int tmp=s[a[pos]];
	s[a[pos]]+=type;
	if (tmp==0 && s[a[pos]]==1) ans++;
	else if (tmp==1 && s[a[pos]]==0) ans--;
}
void solve() {
	l=1,r=0,tim=0;
	for (int i=1; i<=cnt1; i++) {
		while(q[i].tim<tim) {
			change(c[tim].l, c[tim].last);
			tim--;
		}
		while(q[i].tim>tim) {
			tim++;
			change(c[tim].l, c[tim].r);
		}
		while(r<q[i].r) r++,update(r, 1);
		while(r>q[i].r) r--,update(r+1, -1);
		while(l<q[i].l) l++,update(l-1, -1);
		while(l>q[i].l) l--,update(l, 1);
		q[i].res=ans;
	}
}
int main() {
	scanf("%d%d",&n,&m);
	size=sqrt(n);
	init();
	sort(q+1, q+cnt1+1, cmp);
	solve();
	sort(q+1, q+cnt1+1, cmp_id);
	for (int i=1; i<=cnt1; i++) {
		printf("%d\n",q[i].res);
	}
	return 0;
}