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
#define lson t[rt].ls 
#define rson t[rt].rs 
int m,mod;
int cnt=0;
int num=0;
struct Stree{
	struct node{
		int ls,rs,maxx;
	}t[200010<<2];
	int root;
	Stree(){
		root=0;
	}
	void pushup(int rt){
		t[rt].maxx=max(t[lson].maxx,t[rson].maxx);
	}
	void update(int &rt,int l,int r,int k,int x){
		if(!rt) rt=++cnt;
		if(l==r){
			t[rt].maxx=x;
			return;
		}
		int mid=(l+r)>>1;
		if(k<=mid) update(lson,l,mid,k,x);
		else update(rson,mid+1,r,k,x);
		pushup(rt);
	}
	int query(int rt,int l,int r,int L,int R){
		if(!rt) return 0;
		if(L<=l && r<=R) return t[rt].maxx;
		int res=0;
		int mid=(l+r)>>1;
		if(L<=mid) res=max(res,query(lson,l,mid,L,R));
		res%=mod;
		if(R>mid) res=max(res,query(rson,mid+1,r,L,R));
		res%=mod;
		return res;
	}
}Q;
signed main(){
	auto solve=[&](){
		read(m),read(mod);
		int las=0;
		int cnt=m;
		while(m--){
			char op;
			int x;
			cin>>op;
			read(x);
			if(op=='A'){
				x+=las;
				x%=mod;
				Q.update(Q.root,1,cnt,++num,x);
			}
			else{
				las=Q.query(Q.root,1,cnt,num-x+1,num);
				cout<<las<<endl;
			}
		}
		return;
	};
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}


