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

const int N=1e6+20;

int n,m,cnt,a[N],root;

struct Stree{
  #define lson (t[rt].ls)
  #define rson (t[rt].rs)
  struct node{
    int ls,rs,siz;
    ll sum;
  }t[N<<5];
  void pushup(int rt){
    t[rt].sum=t[lson].sum+t[rson].sum;
    t[rt].siz=t[lson].siz+t[rson].siz;
  }
  void update(int &rt,int l,int r,int k,int x){
    if(!rt) rt=++cnt;
    if(l==r) {t[rt].siz+=x,t[rt].sum+=l*x;return;}
    int mid=(l+r)>>1;
    if(k<=mid) update(lson,l,mid,k,x);
    else update(rson,mid+1,r,k,x);
    pushup(rt);
  }
  ll querys(int rt,int l,int r,int L,int R){
    if(!rt || R<l || L>r) return 0ll;
    if(L<=l && R>=r) return t[rt].sum;
    int mid=(l+r)>>1;
    return querys(lson,l,mid,L,R)+querys(rson,mid+1,r,L,R);
  }
  int querysiz(int rt,int l,int r,int L,int R){
    if(!rt || R<l || L>r) return 0;
    if(L<=l && R>=r) return t[rt].siz;
    int mid=(l+r)>>1;
    return querysiz(lson,l,mid,L,R)+querysiz(rson,mid+1,r,L,R);
  }
}Q;

void solve(){
  read(n,m);
  const int L=1e9+5;
  Q.update(root,0,L,0,n);
  ll sum;
  int x;
  for(int i=1;i<=m;++i){
    char op[5];
    int c,s;
    scanf("%s",op);
    read(c,s);
    if(*op=='U'){
      Q.update(root,0,L,a[c],-1);
      Q.update(root,0,L,a[c]=s,1);
    }
    if(*op=='Z'){
      x=Q.querysiz(root,0,L,s,L);
      sum=s?Q.querys(root,0,L,0,s-1):0;
      puts(sum>=(c-x)*1ll*s?"TAK":"NIE");
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


