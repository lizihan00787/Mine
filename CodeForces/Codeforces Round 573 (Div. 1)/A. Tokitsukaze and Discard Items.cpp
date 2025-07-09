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

const int N=1e5+20;

int n,m,k;
int p[N];
bool vis[N];

inline void solve(){
    read(n,m,k);
    for(int i=1;i<=m;++i) read(p[i]);
    p[m+1]=0x3f3f3f3f3f3f3f3f;
    int pos=0,pot=k,tot=m,ans=0,las=0;
    while(tot>0){
        pos=upper_bound(p+1,p+m+1,pot)-p-1;
        if(vis[pos] || pos==0) {pot+=ceil(1.0*(p[pos+1]-pot)/k)*k;continue;}
        if(vis[pos] && pos==m) break;
        vis[pos]=1;
        pot+=pos-las;
        tot-=(pos-las);
        ans++;
        las=pos;
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}