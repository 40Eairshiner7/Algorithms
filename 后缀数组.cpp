#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define inf 0x7fffffff
#define ll long long
using namespace std;
const int MAXN = 200005;
//inline ll read() {
//	ll x=0,f=1;char ch=getchar();
//	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
//	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
//    return x*f;
//}
char str[MAXN],s[MAXN];
int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN],sa[MAXN],r[MAXN];
int cmp(int *r,int a,int b,int l) { return r[a]==r[b] && r[a+l]==r[b+l]; }
void da(int *r,int n,int m) {
	int i,j,p,*y=wb,*x=wa,*t;
	
	//此处为基数排序 Ws[i]先记录i出现了几次 后记录i在所有数中排第几 sa[i]记录排第i的数的编号 
	for(i=0; i<m; i++) Ws[i]=0;
	for(i=0; i<n; i++) Ws[x[i]=r[i]]++;
	for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
	for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
	
	//循环到排名不同的字符串有n个 
	for(j=1,p=1; p<n; j*=2,m=p) {
		
		//对第二关键字进行排序 末尾填补0的字符串必定在前j项 
		for(p=0,i=n-j; i<n; i++) y[p++]=i;
		for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		
		//对已经按照第二关键字排序好的字符串数组进行第一关键字排序 
		for(i=0; i<n; i++) wv[i]=x[y[i]];
		for(i=0; i<m; i++) Ws[i]=0;
		for(i=0; i<n; i++) Ws[wv[i]]++;
		for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
		for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
		
		//利用sa数组求出rank数组 即x[i] 
		t=x,x=y,y=t,x[sa[0]]=0,p=1; 
		for(i=1; i<n; i++) x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	return;
}
