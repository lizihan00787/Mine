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

int n,m,q;
char s[N],t[N];

struct node{
    int len,fa;
    int ch[26];
}SAM[N<<1];
int las=1,tot=1;

int st[N][20],lg[N];

void insert(int c){
    int p=las,np=las=++tot;
    SAM[np].len=SAM[p].len+1;
    for(;p && !SAM[p].ch[c];p=SAM[p].fa) SAM[p].ch[c]=np;
    if(!p) SAM[np].fa=1;
    else{
        int q=SAM[p].ch[c];
        if(SAM[p].len+1==SAM[q].len) SAM[np].fa=q;
        else{
            int nq=++tot;
            SAM[nq]=SAM[q];
            SAM[nq].len=SAM[p].len+1;
            SAM[q].fa=SAM[np].fa=nq;
            for(;p && SAM[p].ch[c]==q;p=SAM[p].fa) SAM[p].ch[c]=nq;
        }
    }
}

void init(){
    int p=1,len=0;
    for(int i=1;i<=n;++i){
        while(p!=1 && !SAM[p].ch[s[i]-'a']) len=SAM[SAM[p].fa].len,p=SAM[p].fa;
        if(SAM[p].ch[s[i]-'a']) len++,p=SAM[p].ch[s[i]-'a'];
        st[i][0]=len;
    }
    for(int j=1;j<=lg[n];++j)
        for(int i=1;i+(1<<j)-1<=n;++i)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}

int get(int l,int r){
    int p=lg[r-l+1];
    return max(st[l][p],st[r-(1<<p)+1][p]);
}

inline void solve(){
    scanf("%s",s+1),scanf("%s",t+1);
    n=strlen(s+1),m=strlen(t+1);
    for(int i=2;i<=n;++i) lg[i]=lg[i/2]+1;
    for(int i=1;i<=m;++i) insert(t[i]-'a');
    init();read(q);
    while(q--){
        int l,r;
        read(l,r);
        int L=0,R=r-l+1,res=0;
        while(L<=R){
            int mid=(L+R)>>1;
            if(get(l+mid-1,r)>=mid) res=mid,L=mid+1;
            else R=mid-1;
        }
        cout<<res<<endl;
    }
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}