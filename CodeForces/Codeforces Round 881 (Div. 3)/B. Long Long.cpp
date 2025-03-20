#include<bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
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
int T=1;
int n;
int a[200010];
int b[200010];
signed main(){
    auto solve=[&](){
        cin>>n;
        int sum=0;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i=1;i<=n;++i){
            cin>>a[i];
            sum+=abs(a[i]);
        }
        for(int i=1;i<=n;++i){
            if(a[i]==0 && (a[i-1]<0 || a[i+1]<0 || b[i-1]==-1 || b[i+1]==-1)) b[i]=-1;
            else if(a[i]<0) b[i]=-1;
            else b[i]=1;
        }
        int m=unique(b+1,b+n+1)-b;
        int ans=0;
        for(int i=1;i<m;++i){
            if(b[i]==-1){
                ans++;
            }
        }
        cout<<sum<<' '<<ans<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}