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
double a[N];

struct Stree{
  #define lson (rt<<1)
  #define rson (rt<<1|1)
  struct node{
    double sum,psum;
    double tag;
  }t[N<<2];
  void pushup(int rt){
    t[rt].sum=t[lson].sum+t[rson].sum;
    t[rt].psum=t[lson].psum+t[rson].psum;
  }
  void build(int rt,int l,int r){
    if(l==r) {t[rt].sum=1.0*a[l],t[rt].psum=1.0*a[l]*a[l];return;}
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(rt);
  }
  void pushtag(int rt,double k,int l,int r){
    t[rt].psum+=(r-l+1)*k*k+2*t[rt].sum*k;
    t[rt].sum+=(r-l+1)*k;
    t[rt].tag+=k;
  }
  void pushdown(int rt,int l,int r){
    if(!t[rt].tag) return;
    int mid=(l+r)>>1;
    pushtag(lson,t[rt].tag,l,mid),pushtag(rson,t[rt].tag,mid+1,r);
    t[rt].tag=0;
  }
  void update(int rt,int l,int r,int L,int R,double x){
    if(L<=l && r<=R) return pushtag(rt,x,l,r);
    int mid=(l+r)>>1;
    pushdown(rt,l,r);
    if(L<=mid) update(lson,l,mid,L,R,x);
    if(R>mid) update(rson,mid+1,r,L,R,x);
    pushup(rt);
  }
  double query(int rt,int l,int r,int L,int R,bool op){
    if(L<=l && r<=R) return op?t[rt].sum:t[rt].psum;
    int mid=(l+r)>>1;
    double res=0;
    pushdown(rt,l,r);
    if(L<=mid) res+=query(lson,l,mid,L,R,op);
    if(R>mid) res+=query(rson,mid+1,r,L,R,op);
    return res;
  }
}Q;

void solve(){
  read(n,m);
  for(int i=1;i<=n;++i) scanf("%lf",&a[i]);
  Q.build(1,1,n);
  for(int i=1;i<=m;++i){
    int op,l,r;
    read(op,l,r);
    if(op==1){
      double x;
      scanf("%lf",&x);
      Q.update(1,1,n,l,r,x);
      continue;
    }
    double sum1=Q.query(1,1,n,l,r,1)/(r-l+1);
    double sum2=Q.query(1,1,n,l,r,0)/(r-l+1);
    if(op==2) printf("%.4lf\n",sum1);
    else printf("%.4lf\n",sum2-sum1*sum1);
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



