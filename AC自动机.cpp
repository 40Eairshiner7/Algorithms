#include <iostream>
#include <cstdio>
using namespace std;
char s[51],m[1000001];
int T,n,sz,ans;
int a[500001][27],q[500001],point[500001],danger[500001];
bool mark[500001];
void ins() {
	int now=1,l=strlen(s);
	for(int i=0;i<l;i++) {
		int t=s[i]-'a'+1;
		if (a[now][t]) now=a[now][t];
		else now=a[now][t]=++sz;
	}
	danger[now]++;
}
void acmach() {
	int t=0,w=1,now;
	q[0]=1;
	point[1]=0;
	while(t<w) {
		now=q[t++];
		for(int i=1; i<=26; i++) {
			if(!a[now][i])continue;
			int k=point[now];
			while(!a[k][i]) k=point[k];
			point[a[now][i]]=a[k][i];
			q[w++]=a[now][i];
		}
	}
}
void solve() {
	int k=1,l=strlen(m);
	for(int i=0; i<l; i++) {
		mark[k]=1;
		int t=m[i]-'a'+1;
		while(!a[k][t]) k=point[k];
		k=a[k][t];
		if(!mark[k]) {
			for(int j=k; j; j=point[j]) {
				ans+=danger[j];
				danger[j]=0;
			}
		}
	}
	printf("%d\n",ans);
}
int main() {
	scanf("%d",&T);
	while(T--) {
		sz=1;
		ans=0;
		scanf("%d",&n);
		for(int i=1;i<=26;i++)a[0][i]=1;
		while(n--) {
			scanf("%s",s);
			ins();
		}
		acmach();
		scanf("%s",m);
		solve();
		for(int i=1;i<=sz;i++) {
			point[i]=danger[i]=mark[i]=0;
			for(int j=1;j<=26;j++) a[i][j]=0;
		}
	}
	return 0;
}