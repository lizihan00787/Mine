#include<bits/stdc++.h>
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
const int N=3e5+10;
char a[N],s[N];
int k=0;
int d[N];
int ll[N],rr[N];
void manacher(char *s,int n){
    d[1]=1;
    for(int i=2,l,r=1;i<=n;++i){
        if(i<=r) d[i]=min(d[r-i+l],r-i+1);
        while(s[i+d[i]]==s[i-d[i]]) d[i]++;
        if(i+d[i]-1>r) l=i-d[i]+1,r=i+d[i]-1;
        ll[i-d[i]+1]=max(ll[i-d[i]+1],d[i]-1);
        rr[i+d[i]-1]=max(rr[i+d[i]-1],d[i]-1);
    }
}
signed main(){
    auto solve=[&](){
        scanf("%s",a+1);
        int n=strlen(a+1);
        s[0]='$';s[++k]='#';
        for(int i=1;i<=n;++i) s[++k]=a[i],s[++k]='#';
        manacher(s,k);n=k;
        for(int i=1;i<=n;i+=2) ll[i]=max(ll[i-2]-2,ll[i]);
        for(int i=n;i>=1;i-=2) rr[i]=max(rr[i+1]-2,rr[i]);
        int ans=0;
        for(int i=1;i<=n;i+=2) if(ll[i] && rr[i]) ans=max(ans,ll[i]+rr[i]);
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}