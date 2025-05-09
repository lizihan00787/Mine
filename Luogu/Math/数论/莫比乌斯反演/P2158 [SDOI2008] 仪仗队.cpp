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
int p[40020],isnp[40020],tot=0;
int mu[40020];
int n;
void getmu(){
    mu[1]=1;
    for(int i=2;i<=40000;++i){
        if(!isnp[i]) p[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot && i*p[j]<=40000;++j) {
            isnp[i*p[j]]=1;
            if(i%p[j]==0){
                mu[i*p[j]]=0;
                break;
            }
            mu[i*p[j]]=-mu[i];
        }
    }
}
signed main(){
    auto solve=[&](){
        read(n);
        getmu();
        if(n==1){
            puts("0");
            return;
        }
        int ans=0;
        for(int i=1;i<=n;++i) ans+=mu[i]*(int)((n-1)/i)*(int)((n-1)/i);
        ans+=2;
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}