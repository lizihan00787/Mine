#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
template<typename P>
inline void read(P &x){
   	P res=0,f=1;
   	char ch=getchar();
   	while(ch<'0' || ch>'9'){
   		if(ch=='-') f=-1;
   		ch=getchar();
   	}
   	while(ch>='0' && ch<='9'){
   		res=res*10+ch-'0';
   		ch=getchar();
	}
	x=res*f;
}
int n;
int a[300010];
int gx[300010];
map<int,int> q;
map<int,int> apper;
signed main(){
	read(n);
	for(int i=1;i<=n;++i){
		read(a[i]);
	}
	for(int i=1;i<=n;++i){
		if(q[a[i]]==0){
			q[a[i]]=i;
			apper[a[i]]++;
			continue;
		}
		int now=i;
		int las=q[a[i]];
		gx[i]=(now-las-1)*apper[a[i]]+gx[las];
		apper[a[i]]++;
		q[a[i]]=i;
	}
	int ans=0;
	for(int i=1;i<=n;++i) ans+=gx[i];
	cout<<ans<<endl;
	return 0;
}


