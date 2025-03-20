#include<bits/stdc++.h>
#define endl '\n'
#define int long long
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

const int N=2e5+20;

int n,m,a[N];
double sink,cosk;

struct Stree{
  #define lson (rt<<1)
  #define rson (rt<<1|1)
  struct node{
    double sine,cosi;
    int tag;
  }t[N<<2];
  void pushup(int rt){
    t[rt].sine=t[lson].sine+t[rson].sine;
    t[rt].cosi=t[lson].cosi+t[rson].cosi;
  }
  void pushtag(int rt,double sinx,double cosx){
    double sina=t[rt].sine,cosa=t[rt].cosi;
    t[rt].sine=sina*cosx+cosa*sinx;
    t[rt].cosi=cosa*cosx-sina*sinx;
  }
  void pushdown(int rt){
    if(!t[rt].tag) return;
    double sinx=sin(t[rt].tag),cosx=cos(t[rt].tag);
    pushtag(lson,sinx,cosx),pushtag(rson,sinx,cosx);
    t[lson].tag+=t[rt].tag;
    t[rson].tag+=t[rt].tag;
    t[rt].tag=0;
  }
  void build(int rt,int l,int r){
    if(l==r) {t[rt].sine=sin(a[l]);t[rt].cosi=cos(a[l]);return;}
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(rt);
  }
  void update(int rt,int l,int r,int L,int R,int x){
    if(L<=l && r<=R) {pushtag(rt,sink,cosk);t[rt].tag+=x;return;}
    pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) update(lson,l,mid,L,R,x);
    if(R>mid) update(rson,mid+1,r,L,R,x);
    pushup(rt);
  }
  double query(int rt,int l,int r,int L,int R){
    if(L<=l && r<=R) return t[rt].sine;
    pushdown(rt);
    int mid=(l+r)>>1;
    double res=0;
    if(L<=mid) res+=query(lson,l,mid,L,R);
    if(R>mid) res+=query(rson,mid+1,r,L,R);
    return res;
  }
}Q;

void solve(){
  read(n);
  for(int i=1;i<=n;++i) read(a[i]);
  Q.build(1,1,n);
  read(m);
  for(int i=1;i<=m;++i){
    int op,l,r;
    read(op,l,r);
    if(op==1){
      int k;
      read(k);
      sink=sin(k);
      cosk=cos(k);
      Q.update(1,1,n,l,r,k);
    }
    else printf("%.1lf\n",Q.query(1,1,n,l,r));
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



