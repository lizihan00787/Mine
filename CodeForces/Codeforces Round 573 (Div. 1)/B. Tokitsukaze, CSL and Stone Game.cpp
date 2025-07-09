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

const int N=1e5+20;

int n;
int a[N];

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]);
    sort(a+1,a+n+1);
    if(!a[1] && a[1]==a[2]) return (void)puts("cslnb");
    for(int i=2;i<n;++i) if(a[i]==a[i+1] && a[i]==a[i-1]) return (void)puts("cslnb");
    for(int i=2;i<n;++i) if(a[i]==a[i+1] && a[i]==a[i-1]+1) return (void)puts("cslnb");
    bool flag=0;
    for(int i=2;i<=n;++i){
        if(a[i]==a[i-1] && !flag) flag=1;
        else if(a[i]==a[i-1] && flag) return (void)puts("cslnb"); 
    }
    int sum=0;
    for(int i=1;i<=n;++i) sum+=abs(a[i]-i+1);
    if(sum&1) puts("sjfnb");
    else puts("cslnb");
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}