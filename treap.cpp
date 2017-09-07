//treap1
//http://hzwer.com/1712.html
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct data{
	int l,r,v,size,rnd,w;
}tr[100005];
int n,size,root,ans;
//更新结点信息
void update(int k) {
	tr[k].size=tr[tr[k].l].size+tr[tr[k].r].size+tr[k].w;
}
void rturn(int &k) {
	int t=tr[k].l;
	tr[k].l=tr[t].r;
	tr[t].r=k;
	tr[t].size=tr[k].size;
	update(k);
	k=t;
}
void lturn(int &k) {
	int t=tr[k].r;
	tr[k].r=tr[t].l;
	tr[t].l=k;
	tr[t].size=tr[k].size;
	update(k);
	k=t;
}
void insert(int &k,int x) {
	if(k==0) {
		size++;
		k=size;
		tr[k].size=tr[k].w=1;
		tr[k].v=x;
		tr[k].rnd=rand();
		return;
	}
	tr[k].size++;
    if(tr[k].v==x) tr[k].w++;
	//每个结点顺便记录下与该节点相同值的数的个数
	else if(x>tr[k].v) {
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd<tr[k].rnd) lturn(k);
	}
	else {
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd<tr[k].rnd) rturn(k);
	} 
}
void del(int &k,int x) {
    if(k==0) return; 
	if(tr[k].v==x) {
		if(tr[k].w>1) {
			tr[k].w--;
			tr[k].size--;
			return;
			//若不止相同值的个数有多个，删去一个
		}
		if(tr[k].l*tr[k].r==0) k=tr[k].l+tr[k].r;//有一个儿子为空
		else if(tr[tr[k].l].rnd<tr[tr[k].r].rnd) rturn(k),del(k,x);
		else lturn(k),del(k,x);
	}
	else if(x>tr[k].v) tr[k].size--,del(tr[k].r,x);
	else tr[k].size--,del(tr[k].l,x);
}
int query_rank(int k,int x) {
    if(k==0) return 0;
	if(tr[k].v==x) return tr[tr[k].l].size+1;
	else if(x>tr[k].v) return tr[tr[k].l].size+tr[k].w+query_rank(tr[k].r,x);
	return query_rank(tr[k].l,x);
}
int query_num(int k,int x) {
    if(k==0) return 0;
	if(x<=tr[tr[k].l].size) return query_num(tr[k].l,x);
    else if(x>tr[tr[k].l].size+tr[k].w) return query_num(tr[k].r,x-tr[tr[k].l].size-tr[k].w);
    return tr[k].v;
}
void query_pro(int k,int x) {
    if(k==0) return;
    if(tr[k].v<x) {
		ans=k;
		query_pro(tr[k].r,x);
	}
    else query_pro(tr[k].l,x);
}
void query_sub(int k,int x) {
	if(k==0) return;
	if(tr[k].v>x) {
		ans=k;
		query_sub(tr[k].l,x);
	}
	else query_sub(tr[k].r,x);
}
int main() {
	scanf("%d",&n);
	int opt,x;
	for(int i=1; i<=n; i++) {
		scanf("%d%d",&opt,&x);
		switch(opt) {
			case 1:insert(root,x);break;
			case 2:del(root,x);break;
			case 3:printf("%d\n",query_rank(root,x));break;
			case 4:printf("%d\n",query_num(root,x));break;
			case 5:ans=0;query_pro(root,x);printf("%d\n",tr[ans].v);break;
			case 6:ans=0;query_sub(root,x);printf("%d\n",tr[ans].v);break;
		}
	}
	return 0;
}
/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
//treap2
//http://hzwer.com/896.html
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
struct data{
	int l,r,num,rnd,s;
}tr[100001];
int n,mn;
int root,size,leave,delta;
void update(int k){ tr[k].s=tr[tr[k].l].s+tr[tr[k].r].s+1; }
void rturn(int &k) {
	int t=tr[k].l;
	tr[k].l=tr[t].r;
	tr[t].r=k;
	tr[t].s=tr[k].s;
	update(k);
	k=t;
}
void lturn(int &k) {
	int t=tr[k].r;
	tr[k].r=tr[t].l;
	tr[t].l=k;
	tr[t].s=tr[k].s;
	update(k);
	k=t;
}
void insert(int &k,int x) {
	if(k==0) {
		size++;
		k=size;
		tr[k].rnd=rand();
		tr[k].num=x;
		tr[k].s=1;
		return;
	}
	tr[k].s++;
	if(x<tr[k].num) {
		insert(tr[k].l,x);
		if(tr[tr[k].l].rnd<tr[k].rnd) rturn(k);
	}
	else {
		insert(tr[k].r,x);
		if(tr[tr[k].r].rnd<tr[k].rnd) lturn(k);
	}
}
int del(int &k,int x) {
	int t;
	if(k==0) return 0;
	if(tr[k].num<x) { t=tr[tr[k].l].s+1; k=tr[k].r; return t+del(k,x); }
	else { t=del(tr[k].l,x); tr[k].s-=t; return t; }
}
int find(int k,int x) {
	if(tr[tr[k].l].s+1==x) return tr[k].num+delta;
	else if(tr[tr[k].l].s+1<x) return find(tr[k].r,x-tr[tr[k].l].s-1);
	return find(tr[k].l,x);
}
int main() {
	srand(time(0));
	scanf("%d%d",&n,&mn);
	char ch[1];int x;
	while(n--) {
		scanf("%s%d",ch,&x);
		if(ch[0]=='I') if(x>=mn) insert(root,x-delta) ;
	    if(ch[0]=='A') delta+=x;
	    if(ch[0]=='S') { delta-=x; leave+=del(root,mn-delta); }
	    if(ch[0]=='F') {
			if(x>tr[root].s) printf("-1");
			else printf("%d",find(root,tr[root].s-x+1));
			printf("\n");
		}
	}
	printf("%d",leave);
	return 0;
}