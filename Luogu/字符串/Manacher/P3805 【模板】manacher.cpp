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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
char a[31000010],s[31000010];
int d[31000010];
int k=0;
void manacher(char *s,int n){
    d[1]=1;
    for(int i=2,l,r=1;i<=n;++i){
        if(i<=r) d[i]=min(d[r-i+l],r-i+1);
        while(s[i-d[i]]==s[i+d[i]]) d[i]++;
        if(i+d[i]-1>r) l=i-d[i]+1,r=i+d[i]-1;
    }
}
signed main(){
    auto solve=[&](){
        scanf("%s",a+1);
        int lena=strlen(a+1);
        s[0]='$';
        s[++k]='#';
        for(int i=1;i<=lena;++i){
            s[++k]=a[i];
            s[++k]='#';
        }
        manacher(s,k);
        int ans=0;
        for(int i=1;i<=k;++i) ans=max(ans,d[i]);
        cout<<ans-1<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}