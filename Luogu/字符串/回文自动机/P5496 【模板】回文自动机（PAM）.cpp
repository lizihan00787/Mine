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
const int N=5e5+10;
int n,tot=1;
struct node{
    int len,fa,a[27],dep;
    node(){
        fa=0;
        len=0;
        memset(a,0,sizeof(a));
        dep=0;
    }
}t[N];
char s[N];
int getfail(int u,int i){
    while(i-t[u].len-1<=0 || s[i-t[u].len-1]!=s[i]) u=t[u].fa;
    return u;
}
signed main(){
    auto solve=[&](){
        scanf("%s",s+1);
        n=strlen(s+1);
        t[0].fa=1,t[1].len=-1;
        int now=0,las=0;
        for(int i=1;i<=n;++i){
            s[i]=(s[i]-'a'+las)%26+'a';
            int pos=getfail(now,i),c=s[i]-'a';
            if(!t[pos].a[c]){
                t[++tot].fa=t[getfail(t[pos].fa,i)].a[c];
                t[pos].a[c]=tot;
                t[tot].len=t[pos].len+2,t[tot].dep=t[t[tot].fa].dep+1;
            }
            now=t[pos].a[c];
            cout<<(las=t[now].dep)<<' ';
        }
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}