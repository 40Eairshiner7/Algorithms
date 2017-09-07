#include <iostream>  
#include <cstdio>   
#include <algorithm>      
#include <cstring>   
#define MM 440004    
#define INF 100000007  
using namespace std;  
struct Treap {  
	int root,treapCnt,key[MM],priority[MM],childs[MM][2],cnt[MM],size[MM];  
	Treap() {  
		root=0;  
		treapCnt=1;  
		priority[0]=INF;  
		size[0]=0;  
	}  
	void update(int x) {  
		size[x]=size[childs[x][0]]+cnt[x]+size[childs[x][1]];  
	}  
	void rotate(int &x,int t) {  
		int y=childs[x][t];  
		childs[x][t]=childs[y][1-t];  
		childs[y][1-t]=x;  
		update(x);  
		update(y);  
		x=y;  
	}  
	void insert(int &x,int k) {
		if(x) {  
			if(key[x]==k) cnt[x]++;  
			else{  
				int t=key[x]<k;  
				insert(childs[x][t],k);
				if(priority[childs[x][t]]<priority[x]) rotate(x,t);  
			}  
		}  
		else{  
			x=treapCnt++;  
			key[x]=k;  
			cnt[x]=1;  
			priority[x]=rand();  
			childs[x][0]=childs[x][1]=0;  
		}  
		update(x);  
	}  
	void erase(int &x,int k){
		if(key[x]==k) {  
			if(cnt[x]>1) cnt[x]--;  
			else {  
				if(childs[x][0]==0&&childs[x][1]==0) {  
					x=0;  
					return ;  
				}  
				int t=priority[childs[x][0]]>priority[childs[x][1]];  
				rotate(x,t);  
				erase(x,k);
			}  
		}  
		else erase(childs[x][key[x]<k],k);
		update(x);  
	}  
	int getkth(int &x,int k) {
		if(k<=size[childs[x][0]]) return getkth(childs[x][0],k);
		k-=(size[childs[x][0]]+cnt[x]);  
		if(k<=0) return key[x];  
		return getkth(childs[x][1],k);
	}
}treap;

int main() {
	int n, x, tot = 0;
	char op[5];
	scanf("%d", &n);
	while (n--) {
		scanf("%s", op);
		if (op[0] == 'Y') printf("Single dog!\n");
		else {
			scanf("%d", &x);
			if (op[0] == 'J') {
				tot++;
				treap.insert(root,x);
			}
			else if (op[0] == 'X') {
				tot--;
				treap.erase(root,x);
			}
			else if (op[0] == 'W') {
				if (x > tot || x < 1)  printf("0\n");
				else printf("%d\n", treap.getkth(root,x));
			}
		}
	}
	return 0;
}
