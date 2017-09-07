void rmq_isit(bool ok)
{
	for(int i=1;i<=n;i++)
		mm[i][0]=mi[i][0]=a[i];
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			if(ok)
				mm[i][j]=max(mm[i][j-1],mm[i+(1<<(j-1))][j-1]);
			else
				mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
		}

	}
}
int rmq(int l,int r)
{
	int k=0;
	while((1<<(k+1))<=r-l+1)
		k++;
	//printf("%d %d %d %d\n",l,l+(1<<k),r-(1<<k)+1,r-(1<<k)+1+(1<<k));
	int ans1=max(mm[l][k],mm[r-(1<<k)+1][k]);
	int ans2=min(mi[l][k],mi[r-(1<<k)+1][k]);
	return ans1-ans2;
}