#include <iostream>
#define LL long long
using namespace std;
LL multi(LL a,LL b,LL m) {
	LL ans = 0;
	a %= m;
	while(b) {
		if(b & 1) {
			ans = (ans + a) % m;
			b--;
		}
		b >>= 1;
		a = (a + a) % m;
	}
	return ans;
}
LL quick_mod(LL a,LL b,LL m) {
	LL ans = 1;
	a %= m;
	while(b) {
		if(b & 1) {
			ans = multi(ans,a,m);
			b--;
		}
		b >>= 1;
		a = multi(a,a,m);
	}
	return ans;
}
int main(int argc, char *argv[]) {
	cout << quick_mod(3, 4, 10000000) << endl;
	return 0;
}


// 1  1/2  1/3  1/4 = 25/13