#include <iostream>
using namespace std;
const long long p = 100000007;
long long qpow(long long a,long long b)
{
	long long ans;
	for(ans=1;b;b>>=1,a=a*a%p)
		if(b&1)ans=ans*a%p;
	return ans;
}
long long getc(long long n,long long m)
{
	if(n<m)return 0;
	if(m>n-m)m=n-m;
	long long s1=1,s2=1;
	for(long long i=0;i<m;i++)
	{
		s1=s1*(n-i)%p;
		s2=s2*(i+1)%p;
	}
	return s1*qpow(s2,p-2)%p;
}
long long lucas(long long n,long long m)
{
	if(m==0)return 1;
	return getc(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main() {
	cout << lucas(5, 3) << endl;
	return 0;
}