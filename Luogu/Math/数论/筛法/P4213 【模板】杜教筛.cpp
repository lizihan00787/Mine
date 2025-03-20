#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
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
const int N=5000010;
int p[N];
bool isnp[N];
int tot=0,phi[N],mu[N];
int n;
void get(){
    phi[1]=1;
    mu[1]=1;
    for(int i=2;i<=5000005;++i){
        if(!isnp[i]) p[++tot]=i,phi[i]=i-1,mu[i]=-1;
        for(int j=1;j<=tot && i*p[j]<=5000005;++j) {
            isnp[i*p[j]]=1;
            if(i%p[j]==0){
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*(p[j]-1);
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=5000005;++i) mu[i]+=mu[i-1],phi[i]+=phi[i-1];
}
unordered_map<int,int> ansm,ansp;
int get_phi(int x){
    if(x<=N) return phi[x];
    if(ansp[x]) return ansp[x];
    int ans=(1+x)*x/2;
    for(int l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans-=(r-l+1)*get_phi(x/l);
    }
    return ansp[x]=ans;
}
int get_mu(int x){
    if(x<=N) return mu[x];
    if(ansm[x]) return ansm[x];
    int ans=1;
    for(int l=2,r;l<=x;l=r+1){
        r=x/(x/l);
        ans-=(r-l+1)*get_mu(x/l);
    }
    return ansm[x]=ans;
}
signed main(){
    get();
    auto solve=[&](){
        read(n);
        cout<<get_phi(n)<<' '<<get_mu(n)<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    read(T);
    while(T--) solve();
    return 0;
}