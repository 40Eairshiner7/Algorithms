//sum(a,n)=1+a^1+a^2+...+a^n
const LL MOD = 10000000;
LL sum(LL a,LL n) {  
	if(n == 0) return 1;  
	LL t = sum(a,(n-1)/2);  
	if(n & 1) {  
		LL cur = pow(a,(n+1)/2);  
		t = (t + t % MOD * cur % MOD) % MOD;  
	}  
	else {  
		LL cur = pow(a,(n+1)/2);  
		t = (t + t % MOD * cur % MOD) % MOD;  
		t = (t + (LL)pow(a,n)) % MOD;  
	}  
	return t;  
} 
int main(int argc, char *argv[]) {
	cout << sum(2, 3) << endl;
	return 0;
}