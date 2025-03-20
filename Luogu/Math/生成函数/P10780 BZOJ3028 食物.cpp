#include<bits/stdc++.h>
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
const int mod=10007;
template<typename P>
inline void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=res*10+ch-'0';
        res%=mod;
        ch=getchar();
    }
    x=res*f;
}
int T=1;
int n;
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=a*res%mod;;
        a=a*a%mod;b>>=1;
    }
    return res;
}
int inv(int a){
    return qpow(a,mod-2);
}
signed main(){
    auto solve=[&](){
        read(n);
        cout<<(n+2)*(n+1)%mod*n%mod*inv(6)%mod<<endl;
    };
    //io();
    //read(T);
    while(T--) solve();
    return 0;
}