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
int a[10];
signed main(){
    auto solve=[&](){
        int last=0;
        for(int i=1;i<=8;++i){
            cin>>a[i];
            if(a[i]<last || (a[i]<100 || a[i]>675) || (a[i]%25!=0)){
                cout<<"No"<<endl;
                return;
            }
            else{
                last=a[i];
            }
        }
        cout<<"Yes"<<endl;
        return;
    };
    io();
    //cin>>T;
    while(T--) solve();
    return 0;
}