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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
int T=1;
int n;
const int N=2010;
struct edge{
    int to,nxt,w;
}e[N*N<<1];
int head[N*N],cnt,dis[N*N],vis[N*N];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].nxt=head[u];
    e[cnt].w=w;
    head[u]=cnt;
}
signed main(){
    auto solve=[&](){
        read(n);
        for(int i=1;i<=n;++i){
            for(int j=i,w;j<=n;++j){
                read(w);
                add(i-1,j,w);
                add(j,i-1,w);
            }
        }
        priority_queue<PII> q;
        memset(dis,0x3f,sizeof(dis));
        dis[1]=0;
        q.push(mk(0,1));
        int ans=0;
        while(!q.empty()){
            int x=q.top().second;q.pop();
            if(vis[x]) continue;
            vis[x]=1;
            ans+=dis[x];
            for(int i=head[x];i;i=e[i].nxt){
                int to=e[i].to;
                if(dis[to]>e[i].w){
                    dis[to]=e[i].w;
                    q.push(mk(-dis[to],to));
                }
            }
        }
        cout<<ans<<endl;
    };
    //freopen(.in,'r',stdin);
    //freopen(.out,'w',stdout);
    //read(T);
    while(T--) solve();
    return 0;
}