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

int l,r;
int num[12];
int f[12][12][12][2][2][2];

int dfs(int now,int pre1,int pre2,bool lim,bool flag,bool app4,bool app8){
    int res=0,up=lim?num[now]:9;
    if(app4 && app8) return 0;
    if(now==0) return flag;
    if(!lim && f[now][pre1][pre2][flag][app4][app8]!=-1) return f[now][pre1][pre2][flag][app4][app8];
    for(int i=0;i<=up;++i){
        bool tmp=(pre1==i && pre2==i);
        res+=dfs(now-1,i,pre1,lim&&i==up,flag || tmp,app4||(i==4),app8||(i==8));
    }
    if(!lim) f[now][pre1][pre2][flag][app4][app8]=res;
    return res;
}
int work(int x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }   
    if(len!=11) return 0;
    memset(f,-1,sizeof(f));
    int res=0;
    for(int i=1;i<=num[len];++i) res+=dfs(len-1,i,0,i==num[len],0,i==4,i==8);
    return res;
}
signed main(){
    auto solve=[&](){
        read(l),read(r);
        cout<<work(r)-work(l-1)<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}