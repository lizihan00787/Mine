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

const int N=1e5+20,mod=1e9+7;

int n,m;
int b[N];

int qpow(int a,int b){
  int res=1;
  while(b){
    if(b&1) res=res*a%mod;
    a=a*a%mod;
    b>>=1;
  }
  return res;
}
int inv(int a) {return qpow(a,mod-2);}

struct Stree{
  #define lson (rt<<1)
  #define rson (rt<<1|1)
  int t[N<<2],s[N<<2];
  void pushup(int rt){
    t[rt]=(t[lson]+t[rson])%mod;
    s[rt]=(s[lson]+s[rson])%mod;
  }
  void build(int rt,int l,int r){
    if(l==r) {t[rt]=b[l]*b[l]%mod,s[rt]=b[l]%mod;return;}
    int mid=(l+r)>>1;
    build(lson,l,mid);build(rson,mid+1,r);
    pushup(rt);
  }
  void update(int rt,int l,int r,int k,int x){
    if(l==r) {t[rt]=x*x%mod,s[rt]=x%mod;return;}
    int mid=(l+r)>>1;
    if(k<=mid) update(lson,l,mid,k,x);
    else update(rson,mid+1,r,k,x);
    pushup(rt);
  }
  int query(int rt,int l,int r,int L,int R,bool op){
    if(L<=l && r<=R) return op?s[rt]:t[rt];
    int mid=(l+r)>>1,res=0;
    if(L<=mid) res+=query(lson,l,mid,L,R,op),res%=mod;
    if(R>mid) res+=query(rson,mid+1,r,L,R,op),res%=mod;
    return res;
  }
}Q;

void solve(){
  read(n,m);
  for(int i=1;i<=n;++i) read(b[i]);
  Q.build(1,1,n);
  for(int i=1;i<=m;++i){
    int op,l,r;
    read(op,l,r);
    if(op==1) Q.update(1,1,n,l,r);
    else{
      int sum1=Q.query(1,1,n,l,r,1)*inv(r-l+1)%mod;
      int sum2=Q.query(1,1,n,l,r,0)*inv(r-l+1)%mod;
      int ans=(sum2-sum1*sum1%mod+mod)%mod;
      cout<<ans<<endl;
    }
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



