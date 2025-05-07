#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define ull unsigned long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
template<typename P>
inline void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=2.5e4+10;

int n,k;

int a[N],s[N];
int dp[N];

#define low(x) (x&(-x))
int t[N];
int res=0;
int l=1,r=0;
void upd(int x,int v) {for(;x<=n;x+=low(x)) t[x]+=v;}
int query(int x) {int res=0;for(;x;x-=low(x)) res+=t[x];return res;}
void add(int x,int op) {res+=(op?query(x-1):query(n)-query(x)),upd(x,1);}
void del(int x,int op) {res-=(op?query(x-1):query(n)-query(x)),upd(x,-1);}

double w(int L,int R){
    while(l>L) add(a[--l],0);
    while(r<R) add(a[++r],1);
    while(l<L) del(a[l++],0);
    while(r>R) del(a[r--],1);
    return s[l-1]+res;
}


void work(int l,int r,int L,int R){
    if(l>r) return;
    int mid=(l+r)>>1,pos=0,minn=0x3f3f3f3f3f3f3f3f;
    for(int i=L;i<=min(R,mid-1);++i) if(w(i+1,mid)<minn) minn=w(i+1,mid),pos=i;
    dp[mid]=min(dp[mid],minn);
    work(l,mid-1,L,pos);
    work(mid+1,r,pos,R);
}

inline void solve(){
    read(n,k);
    for(int i=1;i<=n;++i) read(a[i]),dp[i]=w(1,i);
    for(int i=2;i<=k;++i){
        for(int j=1;j<=n;++j) s[j]=dp[j],t[j]=0;
        l=1,r=res=0;
        work(1,n,1,n);
    }
    cout<<dp[n]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}