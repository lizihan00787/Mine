#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
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

const int N=5e5+10;

int n;
int a[N];
double sqr[N],dp[N];

double w(int j,int i){
    return 1.0*a[j]+sqr[i-j];
}

void work(int l,int r,int L,int R){
    if(l>r) return;
    int mid=(l+r)>>1,pos;
    double maxx=0;
    for(int i=L;i<=min(R,mid);++i) if(w(i,mid)>maxx) maxx=w(i,mid),pos=i;
    dp[mid]=max(dp[mid],maxx);
    work(l,mid-1,L,pos);
    work(mid+1,r,pos,R);
}

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i){
        read(a[i]);
        sqr[i]=1.0*sqrt(i);
    }
    work(1,n,1,n);
    for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]),swap(dp[i],dp[n-i+1]);
    work(1,n,1,n);
    for(int i=n;i>=1;--i) cout<<(int)ceil(dp[i])-a[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}