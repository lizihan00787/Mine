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
int a[70];
signed main(){
    auto solve=[&](){
        cin>>n;
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        int ans=0;
        for(int i=1;i<=n/2;++i){
            int x=a[i];
            int y=a[n-i+1];
            ans+=abs(x-y);
        }
        cout<<ans<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}