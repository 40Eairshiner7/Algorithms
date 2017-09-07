/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
#define inf 1000000000
using namespace std;
int ans,n,t1,t2,rt,size;
int tr[50001][2],fa[50001],num[50001];
//记录y拉住x的那一边 然后用那一边去拉tr[x][r] x再去拉住y
void rotate(int x,int &k) {
	int y=fa[x],z=fa[y],l,r;
	if(tr[y][0]==x) l=0;
	else l=1;
	r=l^1;
	if(y==k) k=x;
	else{
		if(tr[z][0]==y) tr[z][0]=x;
		else tr[z][1]=x;
	}
	fa[x]=z;
	fa[y]=x;
	fa[tr[x][r]]=y;
	tr[y][l]=tr[x][r];
	tr[x][r]=y;
}
void splay(int x,int &k) {
	int y,z;
	while(x!=k) {
		y=fa[x],z=fa[y];
		if(y!=k) {
			if((tr[y][0]==x)^(tr[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void ins(int &k,int x,int last) {
	 if(k==0){size++;k=size;num[k]=x;fa[k]=last;splay(k,rt);return;}
	 if(x<num[k])ins(tr[k][0],x,k);
	 else ins(tr[k][1],x,k);
 }
void ask_before(int k,int x) {
	 if(k==0)return;
	 if(num[k]<=x){t1=num[k];ask_before(tr[k][1],x);}
	 else ask_before(tr[k][0],x);
 }
void ask_after(int k,int x) {
   if(k==0)return;
   if(num[k]>=x){t2=num[k];ask_after(tr[k][0],x);}
   else ask_after(tr[k][1],x);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) {
		int x;
		if(scanf("%d",&x)==EOF) x=0;
		t1=-inf;t2=inf;
	    ask_before(rt,x);
	    ask_after(rt,x);
	    if(i!=1) ans+=min(x-t1,t2-x);
	    else ans+=x;
	    ins(rt,x,0);
	}
	printf("%d",ans);
	return 0;
}

/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/

#include <iostream>
#include <cstdio>
using namespace std;
struct data{
	int l,r,f,s,v,num;
}tr[100001];
int n,m,l,tot,root,delta;
void pushup(int x){tr[x].s=tr[tr[x].l].s+tr[tr[x].r].s+1;}
void zig(int &x) {
	int y=tr[x].f;
	int z=tr[y].f;
	if(y==tr[z].l)tr[z].l=x;
	else tr[z].r=x;
	tr[x].f=z;
	tr[y].l=tr[x].r;
	tr[tr[x].r].f=y;
	tr[x].r=y;
	tr[y].f=x;
	pushup(y); pushup(x);
	if(y==root)root=x;
}
void zag(int &x) {
	int y=tr[x].f;
	int z=tr[y].f;
	if(y==tr[z].l) tr[z].l=x;
	else tr[z].r=x;
	tr[x].f=z;
	tr[y].r=tr[x].l;
	tr[tr[x].l].f=y;
	tr[y].f=x;
	tr[x].l=y;
	pushup(y); pushup(x);
	if(y==root)root=x;	
}
void splay(int &x,int d) {
	while(tr[x].f!=d) {
		if(tr[tr[x].f].l==x)zig(x);
		else zag(x);
	}
}
void insert(int k) {
	if(!root) {
		root=++tot;
		tr[tot].num=k;
		tr[tot].s=1;
		return;
	}
	int p=root,z;
	while(p) {
		z=p;
		++tr[p].s;
		if(k<tr[p].num)p=tr[p].l;
		else p=tr[p].r;
	}
	if(tr[z].num>k)tr[z].l=++tot;
	else tr[z].r=++tot;
	tr[tot].num=k;tr[tot].s=1;tr[tot].f=z;
	splay(tot,0);
 }
int find(int x,int k) {
	if(k<=tr[tr[x].r].s)return find(tr[x].r,k);
	if(k==tr[tr[x].r].s+1)return tr[x].num;
	return find(tr[x].l,k-tr[tr[x].r].s-1);
}
int dec(int &x,int f) {
	if(!x)return 0;
	int k;
	if(tr[x].num+delta<m) {
		k=dec(tr[x].r,x)+tr[tr[x].l].s+1;
		tr[tr[x].r].s=tr[x].s-k;
		x=tr[x].r;tr[x].f=f;
	}
	else {
		k=dec(tr[x].l,x);
		tr[x].s-=k;
	}
	return k;
}
int main() {
	scanf("%d%d",&n,&m);
	while(n--) {
		char c[1];
		int k;
		scanf("%s%d",&c,&k);
		if(c[0]=='I'&&k>=m)insert(k-delta);
		if(c[0]=='F')printf("%d\n",k<=tr[root].s?find(root,k)+delta:-1);
		if(c[0]=='A')delta+=k;
		if(c[0]=='S'){delta-=k;l+=dec(root,0);}
	}
	printf("%d\n",l);
	return 0;
}