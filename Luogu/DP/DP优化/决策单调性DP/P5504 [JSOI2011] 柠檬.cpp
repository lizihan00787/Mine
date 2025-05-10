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

const int N=1e5+10;

#define sz(x) (stk[x].size())
#define sp(x) (stk[x].size()-1)
#define sq(x) (stk[x].size()-2)

int a[N],n,buc[N],s[N];
vector<int> stk[N];
int dp[N];

int calc(int p,int t) {return dp[p-1]+t*t*a[p];}

int chk(int x,int y){
    int res=n+1;
    int l=1,r=n,mid;
    while(l<=r){
        mid=(l+r)>>1;
        if(calc(x,mid-s[x]+1)>=calc(y,mid-s[y]+1)) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}


inline void solve(){
    read(n);
    for(int i=1;i<=n;++i) read(a[i]),s[i]=++buc[a[i]];
    for(int i=1;i<=n;++i){
        int t=a[i];
        while(sz(t)>=2 && chk(stk[t][sq(t)],stk[t][sp(t)])<=chk(stk[t][sp(t)],i)) stk[t].pop_back();
        stk[t].push_back(i);
        while(sz(t)>=2 && chk(stk[t][sq(t)],stk[t][sp(t)])<=s[i]) stk[t].pop_back();
		dp[i]=calc(stk[t][sp(t)],s[i]-s[stk[t][sp(t)]]+1);
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