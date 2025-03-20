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
string a,b;
signed main(){
    auto solve=[&](){
        cin>>a>>b;
        int ans=0;
        if(a.size()<b.size()) a.insert(0,b.size()-a.size(),'0');
        for(int i=0;i<a.size();++i){
            if(a[i]!=b[i]){
                ans+=abs(a[i]-b[i]);
                ans+=(a.size()-i-1)*9;
                break;
            }
            else continue;
        }
        cout<<ans<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}