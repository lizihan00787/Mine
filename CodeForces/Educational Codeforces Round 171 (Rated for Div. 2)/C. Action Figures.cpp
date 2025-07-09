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

const int N=4e5+20;

int n;
char s[N];
priority_queue<ll> q;

inline void solve(){
    read(n);
    scanf("%s",s+1);
    ll ans=0,cnt=0;
    for(int i=1;i<=n;++i){
        ans+=i;
        if(s[i]=='0') ++cnt;
        else{
            if(cnt){
                ans-=i;
                q.push(-i);
                --cnt;
            }
            else if(!q.empty()){
                ans-=i;
                ans+=-q.top();
                ++cnt;
                q.pop();
                q.push(-i);
            }
            else{
                ++cnt;
            }
        }
    }
    cout<<ans<<endl;
    while(!q.empty()) q.pop();
}

signed main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    read(T);
    while(T--) solve();
    return 0;
}