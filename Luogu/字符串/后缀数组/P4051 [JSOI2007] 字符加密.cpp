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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=2e5+10;

char s[N];
int n,m=300;
int rk[N],sa[N],y[N],c[N];

void get_sa(){
    for(int i=1;i<=n;++i) rk[i]=s[i],c[rk[i]]++;
    for(int i=2;i<=m;++i) c[i]+=c[i-1];
    for(int i=n;i>=1;--i) sa[c[rk[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;++i) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;++i) c[i]=0;
        for(int i=1;i<=n;++i) c[rk[i]]++;
        for(int i=2;i<=m;++i) c[i]+=c[i-1];
        for(int i=n;i>=1;--i) sa[c[rk[y[i]]]--]=y[i],y[i]=0;
        swap(rk,y);rk[sa[1]]=num=1;
        for(int i=2;i<=n;++i){
            if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) rk[sa[i]]=num;
            else rk[sa[i]]=++num;
        }
        if(num==n) return;
        m=num;
    }
}

signed main(){
    auto solve=[&](){
        scanf("%s",s+1);
        n=strlen(s+1);
        int t=n;
        n*=2;
        for(int i=t+1;i<=n;++i) s[i]=s[i-t];
        get_sa();
        for(int i=1;i<=n;++i) if(sa[i]<=t) printf("%c",s[sa[i]+t-1]);
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}