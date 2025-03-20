#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
#define fi first
#define se second
using namespace std;
template<typename P>
void read(P &x){
  P res=0,f=1;
  char ch=getchar();
  while(!isdigit(ch)){
  	if(ch=='-') f=-1;
    ch=getchar();
  }
  while(isdigit(ch)){
    res=(res<<3)+(res<<1)+(ch^48);
    ch=getchar();
  }
  x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
template<class P>
void write(P x) {if(x>9) write(x/10);putchar(x%10+48);}

int T=1;

const int N=1e5+20;

int n,m;
int col[N],w[N];
vector<int> g[N];

int cnt=0;
int root[N];
struct node{
  int l,r,maxx,sum;
}t[20000110];

int siz[N],son[N],tp[N],dep[N],fa[N],dfx[N],tot;

void dfs1(int u,int f){
  siz[u]=1;
  fa[u]=f;
  dep[u]=dep[f]+1;
  for(auto to:g[u]){
    if(to==f) continue;
    dfs1(to,u);
    siz[u]+=siz[to];
    if(siz[to]>siz[son[u]]) son[u]=to;
  }
}
void dfs2(int u,int t){
  tp[u]=t;
  dfx[u]=++tot;
  if(son[u]) dfs2(son[u],t);
  for(auto to:g[u]){
    if(to==fa[u] || to==son[u]) continue;
    dfs2(to,to);
  } 
}

#define lson (t[rt].l)
#define rson (t[rt].r)
void pushup(int rt) {
  t[rt].sum=t[lson].sum+t[rson].sum;
  t[rt].maxx=max(t[lson].maxx,t[rson].maxx);
}
void update(int &rt,int l,int r,int k,int x){
  if(!rt) rt=++cnt;
  t[rt].maxx=max(t[rt].maxx,x);
  t[rt].sum+=x;
  if(l==r) return;
  int mid=(l+r)>>1;
  if(k<=mid) update(lson,l,mid,k,x);
  else update(rson,mid+1,r,k,x);
}
void remove(int &rt,int l,int r,int k){
  if(l==r) {t[rt].maxx=t[rt].sum=0;return;}
  int mid=(l+r)>>1;
  if(k<=mid) remove(lson,l,mid,k);
  else remove(rson,mid+1,r,k);
  t[rt].maxx=max(t[lson].maxx,t[rson].maxx);
  t[rt].sum=t[lson].sum+t[rson].sum;
}
int query(int rt,int l,int r,int L,int R,bool ty){
  if(L<=l && R>=r) {return (!ty)?t[rt].sum:t[rt].maxx;}
  int mid=(l+r)>>1,res=0;
  if(L<=mid) res=(!ty)?res+query(lson,l,mid,L,R,ty):max(res,query(lson,l,mid,L,R,ty));
  if(R>mid) res=(!ty)?res+query(rson,mid+1,r,L,R,ty):max(res,query(rson,mid+1,r,L,R,ty));
  return res;
}

int sig(int u,int v,int bl,bool ty){
  int ans=0;
  while(tp[u]!=tp[v]){
    if(dep[tp[u]]<dep[tp[v]]) swap(u,v);
    ans=(!ty)?(ans+query(root[bl],1,n,dfx[tp[u]],dfx[u],ty)):max(ans,query(root[bl],1,n,dfx[tp[u]],dfx[u],ty));
    u=fa[tp[u]];
  }
  if(dep[u]<dep[v]) swap(u,v);
  ans=(!ty)?(ans+query(root[bl],1,n,dfx[v],dfx[u],ty)):max(ans,query(root[bl],1,n,dfx[v],dfx[u],ty));
  return ans;
}

void solve(){
  cnt=0;
  read(n,m);
  for(int i=1;i<=n;++i) read(w[i],col[i]);
  for(int i=1;i<n;++i){
    int u,v;
    read(u,v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(1,0);
  dfs2(1,1);
  for(int i=1;i<=n;++i) update(root[col[i]],1,n,dfx[i],w[i]);
  for(int i=1;i<=m;++i){
    char s[5];
    scanf("%s",s);
    int x,y;
    read(x,y);
    if(s[1]=='C'){
      remove(root[col[x]],1,n,dfx[x]);
      update(root[y],1,n,dfx[x],w[x]);
      col[x]=y;
    }
    else if(s[1]=='W'){
      remove(root[col[x]],1,n,dfx[x]);
      update(root[col[x]],1,n,dfx[x],y);
      w[x]=y;
    }
    else if(s[1]=='S') cout<<sig(x,y,col[x],0)<<endl;
    else if(s[1]=='M') cout<<sig(x,y,col[x],1)<<endl;
  }
  return;
}

signed main(){
  //freopen(".in","r",stdin);
  //freopen(".out","w",stdout);
  //read(T);
  while(T--) solve();
  return 0;
}

