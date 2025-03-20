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

const int N=2020;

int n;

inline void solve(){
    read(n);
    vector<ll> a(n);
    for(auto &x:a) read(x);
    ll ans=1e18;

    auto upd=[&](vector<ll> a){
        sort(a.begin(),a.end());
        for(int i=1;i<a.size();++i) if(a[i-1]==a[i]) return;
        ll res=0;
        for(int i=0;i<a.size();i+=2) res=max(res,a[i+1]-a[i]);
        ans=min(ans,res);
    };
    
    if(n%2==0){
        upd(a);
        cout<<ans<<endl;
        return;
    }
    for(int i=0;i<n;++i){
        for(int x: {-1,1}){
            a.push_back(a[i]+x);
            upd(a);
            a.pop_back();
        }
    }
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}