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
int cnt1=0,cnt2=0;
signed main(){
    auto solve=[&](){
        cin>>n;
        cnt1=0;
        cnt2=0;
        for(int i=1;i<=n;++i){
            cin>>a[i];
            if(a[i]%2) cnt1++;
            else cnt2++;
        }
        sort(a+1,a+n+1);
        if(a[1]%2==0){
            if(cnt1) cout<<"NO"<<endl;
            else cout<<"YES"<<endl;
        }
        else cout<<"YES"<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}