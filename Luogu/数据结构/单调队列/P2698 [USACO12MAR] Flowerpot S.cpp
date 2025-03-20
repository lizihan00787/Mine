#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
using namespace std;
int T=1;
int n,d;
struct node{
	int x,y;
}a[100010];
struct que{
	int q[100010],h,t;
	que(){
		h=1,t=0;
	}
	void add(int x,int flag){
		if(!flag) while(h<=t && a[q[t]].y>a[x].y) t--;
		else while(h<=t && a[q[t]].y<a[x].y) t--;
		q[++t]=x;
	}
}q1,q2;
bool cmp(node a,node b){
	return a.x<b.x;
}
signed main(){
	auto solve=[&](){
		read(n),read(d);
		for(int i=1;i<=n;++i) read(a[i].x),read(a[i].y);
		sort(a+1,a+n+1,cmp);
		int ans=0x3f3f3f3f3f3f3f3f;
		q1.h=q2.h=1,q1.t=q2.t=0;
		for(int i=1,j=0;i<=n;++i){
			while(q1.h<=q1.t && q1.q[q1.h]<i) q1.h++;
			while(q2.h<=q2.t && q2.q[q2.h]<i) q2.h++;
			while(a[q1.q[q1.h]].y-a[q2.q[q2.h]].y<d && j<n){
				j++;
				q1.add(j,1);
				q2.add(j,0);
			}
			if(q1.h<=q1.t && q2.h<=q2.t && a[q1.q[q1.h]].y-a[q2.q[q2.h]].y>=d){
				ans=min(ans,a[j].x-a[i].x);
			}
		}
		cout<<(ans==0x3f3f3f3f3f3f3f3f?-1:ans)<<endl;
		return;
	};
	io();
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}

