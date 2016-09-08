//tarjan(point)
void tarjan(int index,int fa) {
	int child=0;
	low[index]=dfn[index]=++stamp;
	for(int i=0; i<vec[index].size(); i++) {
		int tmp=vec[index][i];
		if(!dfn[tmp]) {
			child++;
			tarjan(tmp,index);
			low[index]=min(low[index],low[tmp]);
			if(low[tmp]>=dfn[index]) iscut[index]++;
			//if there are at least one v that low[v]>=dfn[u],u is cut point.
		}
		else low[index]=min(low[index],dfn[tmp]);
	}
	if(index==1) iscut[index]=child-1;
}




//tarjan(edge)
void tarjan(int index,int fa) {
	dfn[index]=low[index]=++stamp;
	for(int i=0; i<vec[index].size(); i++) {
		int tmp=vec[index][i];
		if(!dfn[tmp]) {
			tarjan(tmp,index);
			low[index]=min(low[index],low[tmp]);
			if(low[tmp]>dfn[index]) cnt++;
		}
		else low[index]=min(low[index],dfn[tmp]);
	}
}