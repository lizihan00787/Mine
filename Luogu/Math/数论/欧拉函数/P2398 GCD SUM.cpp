#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
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
int p[100010],isnp[100010],tot=0;
int phi[100010];
int n;
void getphi(){
    phi[1]=1;
    isnp[1]=1;
    for(int i=2;i<=100010;++i){
        if(!isnp[i]) p[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot && i*p[j]<=100010;++j) {
            isnp[i*p[j]]=1;
            if(i%p[j]==0){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
}
signed main(){
    auto solve=[&](){
        read(n);
        getphi();
        int ans=0;
        for(int i=1;i<=n;++i) ans+=phi[i]*(int)(n/i)*(int)(n/i);
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}