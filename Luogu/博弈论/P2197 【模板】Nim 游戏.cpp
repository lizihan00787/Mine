#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define PII pair<int,int>
#define mk(a,b) make_pair(a,b)
using namespace std;
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
        ch=getchar();
    }
    x=res*f;
}
int T=1;
int n;
int ans=0;
signed main(){
    auto solve=[&](){
        read(n);
        ans=0;
        for(int i=1;i<=n;++i){
            int x;
            read(x);
            ans^=x;
        }
        if(ans) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}