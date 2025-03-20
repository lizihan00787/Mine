#include<bits/stdc++.h>
// #pragma GCC optimize(2)
// #pragma GCC optimize(3)
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
int n,m;
string a[120];
map<string,int> q;
string s[120];
signed main(){
    auto solve=[&](){
        cin>>n>>m;
        cin.ignore();
        for(int i=1;i<=n;++i){
            cin>>a[i];
        }
        for(int i=1;i<=m;++i){
            cin>>s[i];
        }
        int yu=0;
        int x;
        for(int i=0;i<=m;++i){
            cin>>x;
            if(i==0){
                yu=x;
            }
            else{
                q[s[i]]=x;
            }
        }
        int ans=0;
        for(int i=1;i<=n;++i){
            ans+=(q[a[i]]!=0?q[a[i]]:yu);
        }
        cout<<ans<<endl;
    };
    io();
    //cin>>T;
    while(T--) solve();
    return 0;
}