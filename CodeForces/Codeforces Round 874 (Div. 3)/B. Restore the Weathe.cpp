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
int n,k;
int b[100010];
struct node{
    int x,k;
}a[100010];
map<int,int> q;
signed main(){
    auto cmp=[&](node a,node b){
        return a.x<b.x;
    };
    auto solve=[&](){
        cin>>n>>k;
        for(int i=1;i<=n;++i){
            cin>>a[i].x;
            a[i].k=i;
        }
        for(int i=1;i<=n;++i) cin>>b[i];
        sort(a+1,a+n+1,cmp);
        sort(b+1,b+n+1);
        for(int i=1;i<=n;++i){
            q[a[i].k]=b[i];
        }
        for(int i=1;i<=n;++i){
            cout<<q[i]<<" ";
        }
        cout<<endl;
    };
    io();
    cin>>T;
    while(T--) solve();
    return 0;
}