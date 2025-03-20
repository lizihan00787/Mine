#include<bits/stdc++.h>
#define int long long
#define endl "\n"
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
#define lson (rt<<1)
#define rson (rt<<1|1)
#define mid ((l+r)>>1)
#define len (r-l+1)
int n,m,r,mod;
const int Max=2e5+10;
struct edge{
	int to,nxt;
}e[Max<<1];
int w[Max],wt[Max];
int head[Max],cnt=0;
void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
int son[Max],id[Max],fa[Max],num,dep[Max],siz[Max],top[Max];
int res=0;
struct t{
	struct node{
		int sum;
		int laz;
	}t[Max<<2];
	void pushup(int rt) {t[rt].sum=(t[lson].sum+t[rson].sum)%mod;}
	void pushdown(int rt,int lenn){
		t[lson].laz+=t[rt].laz;
		t[rson].laz+=t[rt].laz;
		t[lson].sum+=t[rt].laz*(lenn-(lenn>>1));
		t[rson].sum+=t[rt].laz*(lenn>>1);
		t[lson].sum%=mod;
		t[rson].sum%=mod;
		t[rt].laz=0;
	}
	void build(int rt,int l,int r){
		if(l==r){
			t[rt].sum=wt[l];
			if(t[rt].sum>mod) t[rt].sum%=mod;
			return;
		}
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushup(rt);
	}
	void update(int rt,int l,int r,int L,int R,int k){
		if(L<=l && r<=R){
			t[rt].laz+=k;
			t[rt].sum+=k*len;
			return;
		}
		else{
			if(t[rt].laz) pushdown(rt,len);
			if(L<=mid) update(lson,l,mid,L,R,k);
			if(R>mid) update(rson,mid+1,r,L,R,k);
			pushup(rt);
		}
	}
	void query(int rt,int l,int r,int L,int R){
		if(L<=l && r<=R) {res+=t[rt].sum,res%=mod;return;}
		else{
			if(t[rt].laz) pushdown(rt,len);
			if(L<=mid) query(lson,l,mid,L,R);
			if(R>mid) query(rson,mid+1,r,L,R);
		}
	}
}S;
int qrange(int x,int y){
	int ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=0;
		S.query(1,1,n,id[top[x]],id[x]);
		ans+=res;
		ans%=mod;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	res=0;
	S.query(1,1,n,id[x],id[y]);
	ans+=res;
	return ans%mod;
}
void updrange(int x,int y,int k){
	k%=mod;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		S.update(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	S.update(1,1,n,id[x],id[y],k);
}
int qson(int x){
	res=0;
	S.query(1,1,n,id[x],id[x]+siz[x]-1);
	return res;
}
void updson(int x,int k){
	S.update(1,1,n,id[x],id[x]+siz[x]-1,k);
}
void dfs1(int x,int f,int de){
	dep[x]=de;
	fa[x]=f;
	siz[x]=1;
	int maxx=-1;
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==f) continue;
		dfs1(to,x,de+1);
		siz[x]+=siz[to];
		if(siz[to]>maxx) son[x]=to,maxx=siz[to];
	}
}
void dfs2(int x,int tp){
	id[x]=++num;
	wt[num]=w[x];
	top[x]=tp;
	if(!son[x]) return;
	dfs2(son[x],tp);
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa[x] || to==son[x]) continue;
		dfs2(to,to);
	}
}
signed main(){
	auto solve=[&](){
		read(n),read(m),read(r),read(mod);
		for(int i=1;i<=n;++i) read(w[i]);
		for(int i=1;i<n;++i){
			int u,v;
			read(u),read(v);
			add(u,v),add(v,u);
		}
		dfs1(r,0,1);
		dfs2(r,r);
		S.build(1,1,n);
		while(m--){
			int op,x,y,z;
			read(op);
			if(op==1){
				read(x),read(y),read(z);
				updrange(x,y,z);
			}
			else if(op==2){
				read(x),read(y);
				cout<<qrange(x,y)<<endl;
			}
			else if(op==3){
				read(x),read(y);
				updson(x,y);
			}
			else{
				read(x);
				cout<<qson(x)<<endl;
			}
		}
		return;
	};
//	freopen("P4513.in","r",stdin);
//	freopen("P4513_me.out","w",stdout);
	//read(T);
	while(T--) solve();
	return 0;
}
