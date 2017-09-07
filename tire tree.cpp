#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
char str[1000005][6],cur[6];
struct Trie {
	int v;
	Trie *next[140];
};
Trie *root;
void createTrie(char *str) {
	int len=strlen(str),i,j;
	Trie *p=root, *q;
	for(i=0; i<len; ++i) {
		int id=str[i];
		if(p->next[id] == NULL) {
			q=(Trie *)malloc(sizeof(Trie));
			q->v=1;
			for(j=0; j<140; ++j) q->next[j] = NULL;
			p->next[id]=q;
		}
		p=p->next[id];
	}
	p->v=2;
}
int findTrie(char *str) {
	int len = strlen(str),i;
	Trie *p = root;
	for(i=0; i<len; ++i) {
		int id=str[i];
		p=p->next[id];
		if(p==NULL) return 0;
		if(p->v==2 && i==len-1) return 1;
	}
	return 0;
}
int main() {
	int n,m,i,j,ans=0;
	scanf("%d%d",&n,&m);
	for (i=0; i<n; i++) scanf("%s",str[i]);
	root = (Trie *) malloc (sizeof(Trie));
	for(i=0; i<140; ++i) root->next[i] = NULL;
	for (i=0; i<m; i++) {
		scanf("%s",cur);
		createTrie(cur);
	}
	for (i=0; i<n; i++) ans+=findTrie(str[i]);
	printf("%d",ans);
	return 0;
}
/*
5
4
Tommy
Alice 
Jacky
Ali
%%%%
 
Jack
Alice
Alic
Tom

1
*/