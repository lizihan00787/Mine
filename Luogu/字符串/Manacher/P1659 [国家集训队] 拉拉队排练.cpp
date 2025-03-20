#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define int long long
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
const int N=1e6+10,mod=19930726;
char s[N];
int n,m;
int d[N];
int c[N];
void manacher(char *s,int n){
    d[1]=1;
    for(int i=2,l,r=1;i<=n;++i){
        if(i<=r) d[i]=min(d[r-i+l],r-i+1);
        while(s[i+d[i]]==s[i-d[i]]) d[i]++;
        if(i+d[i]-1>r) l=i-d[i]+1,r=i+d[i]-1;
    }
}
int qpow(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}
signed main(){
    auto solve=[&](){
        read(n),read(m);
        cin>>s+1;
        s[0]='$';
        manacher(s,n);
        for(int i=1;i<=n;++i){
            int p=d[i];
            c[1]++,c[p+1]--;
        }
        for(int i=1;i<=n;++i) c[i]+=c[i-1];
        int ans=1;
        int num=0;
        for(int i=1;i<=n;++i) num+=c[i];
        if(num<m){
            puts("-1");
            return;
        }
        for(int i=n;i>=1;--i){
            if(!c[i]) continue;
            int num=c[i];
            int len=i*2-1;
            if(m-num<=0){
                int nj=m;
                ans*=qpow(len,nj);
                ans%=mod;
                break;
            }
            m-=num;
            ans*=qpow(len,num);
            ans%=mod;
        }
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}