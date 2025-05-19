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

const int N=2e6+20,M=4e5+20;

int n;
struct node{
    int ch[26];
    int fa,len;
}SAM[N];
int tot=1,pos[N];

int insert(int c,int las){
    if(SAM[las].ch[c] && SAM[SAM[las].ch[c]].len==SAM[las].len+1) return SAM[las].ch[c];
    int p=las,np=++tot,flag=0,nq,q;
    SAM[np].len=SAM[p].len+1;
    for(;p && !SAM[p].ch[c];p=SAM[p].fa) SAM[p].ch[c]=np;
    if(!p) SAM[np].fa=1;
    else{
        q=SAM[p].ch[c];
        if(SAM[q].len==SAM[p].len+1) SAM[np].fa=q;
        else{
            if(p==las) flag=1,np=0,tot--;
            nq=++tot;
            SAM[nq]=SAM[q];
            SAM[nq].len=SAM[p].len+1;
            SAM[np].fa=SAM[q].fa=nq;
            for(;p && SAM[p].ch[c]==q;p=SAM[p].fa) SAM[p].ch[c]=nq;
        }
    }
    return flag?nq:np;
}

char s[N];

inline void solve(){
    read(n);
    for(int i=1;i<=n;++i){
        scanf("%s",s+1);
        int len=strlen(s+1);pos[0]=1;
        for(int j=1;j<=len;++j) pos[j]=insert(s[j]-'a',pos[j-1]);
    }
    ll ans=0;
    for(int i=2;i<=tot;++i) ans+=SAM[i].len-SAM[SAM[i].fa].len;
    cout<<ans<<endl<<tot<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}