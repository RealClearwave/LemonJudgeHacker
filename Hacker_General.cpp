#include<bits/stdc++.h>
using namespace std;

int i,j,k,n,m,s,ans,fa[100005],f[100005],p1,p2,p3;

int find_fa(int k){
    if(fa[k]==k)return k;
    return fa[k]=find_fa(fa[k]);
}

int unite(int u,int v){
	int fu=find_fa(u),fv=find_fa(v);
	if(fu!=fv) fa[fu]=fv;
}

int find(int k){
    if(f[k]==k)return k;
    return f[k]=find(f[k]);
}

int _unite(int u,int v){
	int fu=find(u),fv=find(v);
	if(fu!=fv) f[fu]=fv;
}

int main(){
	freopen("line.in","r",stdin);
	freopen("line.out","w",stdout);
	ios_base::sync_with_stdio(false);
    cin>>n>>m;
    for(i=1;i<=n;i++) fa[i]=i,f[i]=i;
    for(i=1;i<=m;i++){
        cin>>p1>>p2>>p3;
        if(p1>3) throw runtime_error("OptionError:The option number is out of range. QAQ");
        if(p1==1)
            unite(p2,p3);
        else if(p1==2)
        	_unite(p2,p3);
        else if(find_fa(p2)==find_fa(p3)||find(p2)==find(p3))
            puts("Parallel");
        else if(find(p2)==find(find_fa(p3))||find(find_fa(p2))==find(p3))
            puts("Vertical");
        else 
        	puts("Unknown");
    }
    return 0;
}
