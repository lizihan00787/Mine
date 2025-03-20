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

char a[12];
unordered_map<char,bool> mp;

inline void solve(){
    scanf("%s",a+1);
    int n=strlen(a+1);
    mp.clear();
    for(int i=1;i<=n;++i) mp[a[i]]=1;
    char op;
    for(char x='a';x<='z';++x) if(!mp[x]) {op=x;break;}
    bool f=0;
    for(int i=1;i<=n;++i){
        cout<<a[i];
        if(a[i]==a[i+1] && !f) cout<<op,f=1;
    }
    if(!f) cout<<op;
    cout<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}