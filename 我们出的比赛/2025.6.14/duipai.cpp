#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define ull unsigned long long
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
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

inline void solve(){
    for(int i=1;i<=10;++i){
        string s = to_string(i);
        // system(("std2.exe < cat"+s+".in > std.out").c_str());
        // if(system(("fc std.out cat"+s+".ans").c_str())){
        //     cout<<"WA on "<<i<<endl;
        //     break;
        // }
        freopen(("cat"+s+".in").c_str(),"r",stdin);
        int T=0,n=0,sum=0;;
        read(T);
        int k=0;
        while(T--){
            read(n);
            ++k;
            if(n>2e6*1) {cout<<"WA on"<<"test on"<<k<<"'s n size"<<endl;break;}
            sum+=n;
            for(int j=1,x;j<=n;++j) read(x);
        }
        if(sum>2e6) {cout<<"WA on"<<i<<"'s total n size"<<endl;break;}
        cout<<sum<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}