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
int a[120];
signed main(){
    auto solve=[&](){
        cin>>n;
        int sumz=0,sumf=0;
        int ans=0;
        int p=1;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i]==1) sumz++;
            else sumf++;
            p*=a[i];
        }
        if(sumf>sumz){
            ans+=(sumf-sumz+1)/2;
            sumf-=(sumf-sumz+1)/2;
            if(sumf%2==1){
                ans++;
            }
            cout<<ans<<endl<<endl;
            return 0;
        }
        else{
            if(sumf%2==1){
                ans++;
            }
            cout<<ans<<endl<<endl;
            return 0;
        }
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}