//minamoto
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=2e5+5,M=N*16,K=5e5+5;
struct node{
	int from,to,cost;
	node(){}
	node(int from,int to,int cost):from(from),to(to),cost(cost){}
	inline bool operator <(const node &b)const
	{return cost<b.cost;}
}E[K];
int head[N],Next[N],ver[N],sum[M],L[M],R[M],bin[25],cnt,tot;
int fa[N],f[N][20],ls[N],rs[N],rt[N],val[N],num;
int h[N],limit,b[N],n,q,m,ans=0,dfn;
inline void mission(int u){
	for(int i=1;bin[i]<=n;++i)
	f[u][i]=f[f[u][i-1]][i-1];
}
inline void add(int u,int v){
	ver[++tot]=v,Next[tot]=head[u],head[u]=tot;
}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void update(int last,int &now,int l,int r,int x){
	sum[now=++cnt]=sum[last]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) R[now]=R[last],update(L[last],L[now],l,mid,x);
	else L[now]=L[last],update(R[last],R[now],mid+1,r,x);
}
int query(int a,int x,int k){
	int l=1,r=limit;
	for(int j=18;~j;--j)
	if(f[a][j]&&val[f[a][j]]<=x) a=f[a][j];
	int v=rt[rs[a]],u=rt[ls[a]-1];
	if(sum[v]-sum[u]<k) return -1;
	while(l<r){
		int tmp=sum[R[v]]-sum[R[u]],mid=(l+r)>>1;
		if(tmp>=k) v=R[v],u=R[u],l=mid+1;
		else v=L[v],u=L[u],r=mid,k-=tmp;
	}
	return b[r];
}
void dfs(int u){
	mission(u),ls[u]=++num;
	if(u<=n) update(rt[num-1],rt[num],1,limit,h[u]);
	else rt[num]=rt[num-1];
	for(int i=head[u];i;i=Next[i]) dfs(ver[i]);
	rs[u]=num;
}
int main(){
//	freopen("testdata.in","r",stdin);
	n=read(),m=read(),q=read();
	bin[0]=1;for(int i=1;i<=22;++i) bin[i]=bin[i-1]<<1;
	for(int i=1;i<=2*n;++i) fa[i]=i;
	for(int i=1;i<=n;++i) b[i]=h[i]=read();
	for(int i=1,u,v,e;i<=m;++i)
	u=read(),v=read(),e=read(),E[i]=node(u,v,e);
	sort(b+1,b+1+n),limit=unique(b+1,b+1+n)-b-1;
	for(int i=1;i<=n;++i) h[i]=lower_bound(b+1,b+1+limit,h[i])-b;
	sort(E+1,E+1+m);dfn=n;
	for(int i=1;i<=m;++i){
		int u=find(E[i].from),v=find(E[i].to);
		if(u!=v){
			val[++dfn]=E[i].cost,fa[u]=fa[v]=dfn;
			add(dfn,u),add(dfn,v),f[u][0]=f[v][0]=dfn;
			if(dfn-n==n-1) break;
		}
	}
	for(int i=1;i<=dfn;++i) if(!ls[i]) dfs(find(i));
	while(q--){
		int v=read(),x=read(),k=read();
		print(query(v,x,k));
	}
	Ot();
	return 0;
}
