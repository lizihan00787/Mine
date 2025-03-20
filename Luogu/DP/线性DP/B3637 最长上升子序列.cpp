#include<bits/stdc++.h>
#define int long long
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
int n;
int a[5020];
int dp[5020];
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) read(a[i]);
        dp[1]=a[1];
        int ans=1;
        for(int i=2;i<=n;++i){
            int l=1,r=ans,mid;
            while(l<=r){
                mid=(l+r)>>1;
                if(a[i]<=dp[mid]) r=mid-1;
                else l=mid+1;
            }
            dp[l]=a[i];
            if(l>ans) ++ans;
        }
        cout<<ans<<endl;
    };
    //io();
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}