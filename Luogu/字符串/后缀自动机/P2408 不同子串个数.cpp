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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=2e5+20;

struct node{
    int ch[27],fa,len;
}SAM[N];
int las=1,tot=1;

void insert(int c){
    int p=las,np=las=++tot;
    SAM[np].len=SAM[p].len+1;
    for(;p && !SAM[p].ch[c];p=SAM[p].fa) SAM[p].ch[c]=np;
    if(!p) SAM[np].fa=1;
    else{
        int q=SAM[p].ch[c];
        if(SAM[q].len==SAM[p].len+1) SAM[np].fa=q;
        else{
            int nq=++tot;
            SAM[nq]=SAM[q];
            SAM[nq].len=SAM[p].len+1;
            SAM[q].fa=SAM[np].fa=nq;
            for(;p && SAM[p].ch[c]==q;p=SAM[p].fa) SAM[p].ch[c]=nq;
        }
    }
}

int n;
char s[N];

inline void solve(){
    read(n);
    scanf("%s",s+1);
    for(int i=1;i<=n;++i) insert(s[i]-'a');
    ll ans=0;
    for(int i=1;i<=tot;++i) ans+=SAM[i].len-SAM[SAM[i].fa].len;
    cout<<ans<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}