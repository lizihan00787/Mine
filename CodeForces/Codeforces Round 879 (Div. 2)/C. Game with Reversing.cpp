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
string a,b;
signed main(){
    auto solve=[&](){
        cin>>n;
        cin>>a>>b;
        if(a==b){
            cout<<0<<endl;
            return;
        }
        string ar=string(a.rbegin(),a.rend());
        if(ar==b){
            cout<<2<<endl;
            return;
        }
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}