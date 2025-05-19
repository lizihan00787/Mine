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
int n;
struct node{
    int k;
    int w1,w2;
}c[200010];
signed main(){
    auto cmp=[&](node a,node b){
        int b1=a.w1*b.w2,b2=a.w2*b.w1;
        if(b1!=b2) return b1>b2;
        return a.k<b.k;
    };
    auto solve=[&](){
        cin>>n;
        int a,b;
        for(int i=1;i<=n;++i){
            cin>>a>>b;
            c[i].k=i;
            c[i].w1=a;
            c[i].w2=b;
        }
        sort(c+1,c+n+1,cmp);
        for(int i=1;i<=n;++i){
            cout<<c[i].k<<' ';
        }
        cout<<endl;
    };
    io();
    //cin>>T;
    while(T--) solve();
    return 0;
}