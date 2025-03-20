#include<bits/stdc++.h>
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

int l,r;
int num[11];
int f[11][11];
int dfs(int now,bool op0,bool lim,int pre){
    int res=0,up=lim?num[now]:9;
    if(now==0) return 1;
    if(!op0 && !lim && f[now][pre]!=-1) return f[now][pre];
    for(int i=0;i<=up;++i){
        if(i==0 && op0) res+=dfs(now-1,op0,lim && i==up,pre);
        else if(abs(i-pre)>=2) res+=dfs(now-1,false,lim && i==up,i);
    }
    if(!op0 && !lim) f[now][pre]=res;
    return res;

}
int work(int x){
    int len=0;
    while(x){
        num[++len]=x%10;
        x/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(len,true,true,10000);
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