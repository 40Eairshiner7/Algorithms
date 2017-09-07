//  1  --------------------
int x,y,rev;  
void extend_Euclid(int a, int b) {
	if(b==0) {
		x = 1;
		y = 0;
		return;
	}
	extend_Euclid(b, a%b);
	int t = x;
	x = y;
	y = t - a/b*y;
}
int main() {
	//b%mod的逆元
	int b,mod;
	while(cin>>b>>mod){
	   // x=0;y=0;
		extend_Euclid(b,mod);
		cout<<(x%mod+mod)%mod<<endl;
	}
	return 0;
}
//  2  --------------------
__int64 exGcd(__int64 a,__int64 b,__int64 &x,__int64 &y){  
	if(b==0){  
		x=1;  
		y=0;  
		return a;  
	}  
	__int64 g=exGcd(b,a%b,x,y);  
	__int64 temp=x;  
	x=y;  
	y=temp-(a/b)*y;  
	return g;  
}  