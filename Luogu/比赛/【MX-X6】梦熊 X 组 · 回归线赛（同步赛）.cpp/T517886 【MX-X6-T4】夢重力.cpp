#include<bits/stdc++.h>
#define int long long
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=2e5+10;

int n;
int id[N];
int ans=0;
set<int> s;

int get() {return *s.rbegin()-*s.begin()+1;}
int calc(){
    int x=get();
    if(x==n/2) return n/2*(n/2-1)+(*s.begin()!=1)+(*s.rbegin()!=n);
    int y=*s.begin(),sum=0;
    s.erase(y),x=get();
    if(x==n/2-1) sum+=(*s.begin()!=1)+(*s.rbegin()!=n);
    if(x==n/2) sum++;
    s.insert(y),y=*s.rbegin();
    s.erase(y),x=get();
    if(x==n/2-1) sum+=(*s.begin()!=1)+(*s.rbegin()!=n);
    if(x==n/2) sum++;
    return s.insert(y),sum;
}

signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i) {int x;read(x);id[x]=i;}
        for(int i=1;i<=n/2;++i) s.insert(id[i]);
        ans+=calc();
        for(int i=n/2;i>=1;--i){
            s.erase(id[i]),s.insert(id[i+n/2]);
            ans+=calc();
        }
        cout<<ans<<endl;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}