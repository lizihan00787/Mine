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

const int N=1e5+20;

int n,k;
char s[N];
int L[N],R[N];

void init(){
    L[1]=1,R[n]=n;
    for(int i=2;i<=n;++i) L[i]=s[i]==s[i-1]?L[i-1]:i;
    for(int i=n-1;i>=1;--i) R[i]=s[i]==s[i+1]?R[i+1]:i; 
}
bool chk1(){
    if(n==k || L[n-k]==1 || R[k+1]==n) return 1;
    for(int i=2;i<=n-k;++i) if(s[i-1]==s[i+k] && L[i-1]==1 && R[i+k]==n) return 1;
    return 0;
}
bool chk2(){
    if(k*2<n) return 0;
    for(int i=2;i<=n-k;++i) if(L[i-1]!=1 || R[i+k]!=n) return 0;
    return 1;
}

inline void solve(){
    read(n,k);
    scanf("%s",s+1);
    init();
    if(chk1()) return (void)puts("tokitsukaze");
    if(chk2()) return (void)puts("quailty");
    puts("once again");
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}