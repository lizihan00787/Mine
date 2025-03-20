#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int mod=1e4+7;
int n,m;
int le[50020];
bool check(int x){
    int tot=0,len=0;
    for(int i=1;i<=n;++i){
        if(len+le[i]>x) tot++,len=le[i];
        else len+=le[i];
        if(tot>m) return 0;
    }
    return tot<=m;
}
int dp[50010];
int sum[50010];
int p[50010];
int rem[50010];
signed main(){
    auto solve=[&](){
        read(n),read(m);
        int mx=0;
        for(int i=1;i<=n;++i) read(le[i]),p[i]=p[i-1]+le[i],mx=max(mx,le[i]);
        int l=mx,r=p[n],ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) r=mid-1,ans=mid;
            else l=mid+1;
        }
        for(int i=1;i<=n;++i){
            for(int k=0;k<i;++k){
                if(p[i]-p[k]<=ans) {rem[i]=k;break;}
            }
        }
        int res=(p[n]<=ans);
        for(int i=1;i<=n;++i){
            if(p[i]<=ans) dp[i]=1;
            sum[i]=(sum[i-1]+dp[i])%mod;
        }
        for(int i=2;i<=m+1;++i){
            for(int j=1;j<=n;++j){
                dp[j]=sum[j-1];
                if(rem[j]>=1) dp[j]=((dp[j]-sum[rem[j]-1])%mod+mod)%mod;
            }
            for(int j=1;j<=n;++j) sum[j]=(sum[j-1]+dp[j])%mod;
            res+=dp[n];
            res%=mod;
        }
        cout<<ans<<' '<<res<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}