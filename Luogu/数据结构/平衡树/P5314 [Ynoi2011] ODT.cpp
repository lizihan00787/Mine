#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define endl '\n'
using namespace std;
using namespace __gnu_pbds;
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

const int N=1e6+3;

int n,m;
int a[N];
vector<int> g[N];

struct Nod{
  int x,id;
  friend bool operator < (Nod a,Nod b){return a.x!=b.x?a.x<b.x:a.id<b.id;}
};

tree<Nod,null_type,less<Nod>,rb_tree_tag,tree_order_statistics_node_update>tr[N];

struct BIT{
  #define lowbit(x) (x&(-x))
  int t[N];
  void add(int x,int val) {for(;x<=n;x+=lowbit(x)) t[x]+=val;}
  int ask(int x) {int res=0;for(;x;x-=lowbit(x)) res+=t[x];return res;}
  void modi(int l,int r,int d) {add(l,d),add(r+1,-d);}
}T;

int siz[N],son[N],tp[N],fa[N],dep[N],pos[N],tim=0;

void dfs1(int u){
  siz[u]=1;
  dep[u]=dep[fa[u]]+1;
  for(auto to:g[u]){
    if(to==fa[u]) continue;
    fa[to]=u;
    dfs1(to);
    siz[u]+=siz[to];
    if(siz[to]>siz[son[u]]) son[u]=to;
  }
}
void dfs2(int u,int t){
  tp[u]=t;
  pos[u]=++tim;
  T.modi(tim,tim,a[u]);
  if(son[u]) dfs2(son[u],t);
  for(auto to:g[u]){
    if(to==fa[u] || to==son[u]) continue;
    dfs2(to,to);
    tr[u].insert({a[to],to});
  }
}
void update(int x,int y,int z){
  while(tp[x]!=tp[y]){
    if(dep[tp[x]]<dep[tp[y]]) swap(x,y);
    int t=tp[x];
    tr[fa[t]].erase({a[t],t});
    T.modi(pos[t],pos[x],z);
    a[t]=T.ask(pos[t]);
    tr[fa[t]].insert({a[t],t});
    x=fa[tp[x]];
  }
  if(dep[x]<dep[y]) swap(x,y);
  if(dep[y]!=dep[tp[y]] || !fa[y]) {T.modi(pos[y],pos[x],z);return;}
  tr[fa[y]].erase({a[y],y});
  T.modi(pos[y],pos[x],z);
  a[y]=T.ask(pos[y]);
  tr[fa[y]].insert({a[y],y});
}
void Add(int x,int y) {if(y) tr[x].insert({T.ask(pos[y]),y});}
void Del(int x,int y) {if(y) tr[x].erase({T.ask(pos[y]),y});}

signed main(){
  read(n,m);
  for(int i=1;i<=n;++i) read(a[i]);
  for(int i=1;i<n;++i){
    int x,y;
    read(x,y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  dfs1(1);
  dfs2(1,1);
  for(int i=1;i<=m;++i){
    int op,x,y,z;
    read(op,x,y);
    if(op==1) {read(z),update(x,y,z);continue;}
    Add(x,x);Add(x,son[x]);Add(x,fa[x]);
    write(tr[x].find_by_order(y-1)->x);
    putchar('\n');
    Del(x,x);Del(x,son[x]),Del(x,fa[x]);
  }
  return 0;
}
