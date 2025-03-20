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
char a[70];
map<string,bool> q;
signed main(){
    auto solve=[&](){
        q.clear();
        cin>>n;
        cin>>a+1;
        for(int i=2;i<=n;++i){
            string sub,ssub;
            sub.push_back(a[i-1]);
            sub.push_back(a[i]);
            q[sub]=1;
        }
        cout<<(int)(q.size())<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}