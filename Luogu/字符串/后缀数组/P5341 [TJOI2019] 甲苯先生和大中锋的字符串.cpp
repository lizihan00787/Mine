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

const int N=1e5+10;

int n,m=122,kk;

char s[N];
int rk[N],sa[N],y[N],c[125],h[N];

void get_sa(){
    for(int i=1;i<=n;++i) c[rk[i]=s[i]]++;
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
        swap(rk,y),rk[sa[1]]=num=1;
        for(int i=2;i<=n;++i){
            if(y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]) rk[sa[i]]=num;
            else rk[sa[i]]=++num;
        }
        if(num==n) return;
        m=num;
    }
}

void geth(){
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    for(int i=1,k=0;i<=n;++i){
        if(rk[i]==1) continue;
        if(k) k--;
        int j=sa[rk[i]-1];
        while(i+k<=n && j+k<=n && s[i+k]==s[j+k]) k++;
        h[rk[i]]=k;
    }
}

signed main(){
    auto solve=[&](){
        scanf("%s",s+1);
        read(kk);
        kk--;
        m=122;
        n=strlen(s+1);
        get_sa();
        geth();
        int ans=0;
        for(int i=1;i<=n;++i){
            cout<<h[i]<<' ';
        }
        cout<<endl;
        cout<<ans<<endl;
        for(int i=1;i<=n;++i) sa[i]=0,rk[i]=0,h[i]=0,y[i]=0;
        for(int i=1;i<=m;++i) c[i]=0;
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}