#include<bits/stdc++.h>
#define endl '\n'
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
template<typename Ty,typename ...Args>
inline void read(Ty &x,Args &...args) {read(x);read(args...);}
int T=1;

const int N=13,limit=1e4;

int mod,A,B;
char s[N];
bool is[N];
int num[N],f[N][100010];

int dfs(int pos,int sum,bool lim,bool op0){
    int res=0;
    if(f[pos][sum]!=-1 && !op0 && !lim) return f[pos][sum];
    if(pos==0) return (sum==0);
    int up=lim?num[pos]:9;
    for(int i=0;i<=up;++i){
        if(is[i] || (i==0 && op0)) res+=dfs(pos-1,(sum*10+i)%mod,lim && i==up,op0 && i==0);
    }
    if(!lim && !op0) f[pos][sum]=res;
    return res;
}
int calc(int x){
    int tot=0;
    while(x){
        num[++tot]=x%10;
        x/=10;
    }
    memset(f,-1,sizeof(f));
    return dfs(tot,0,1,1);
}

bool chk(int x){
    while(x){
        if(!is[x%10]) return 0;
        x/=10;
    }
    return 1;
}

inline void solve(){
    read(mod,A,B);
    scanf("%s",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;++i) is[s[i]-'0']=1;
    if(mod<=1e5) cout<<calc(B)-calc(A-1)<<endl;
    else{
        int res=0;
        for(int i=mod;i<=B;i+=mod) if(chk(i) && i>=A) res++;
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