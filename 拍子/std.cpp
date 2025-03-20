#include<bits/stdc++.h>
#define inl inline
#define reg register
#define pll pair<long long,long long>
#define mk(x,y) make_pair(x,y)
#define fir first
#define sec second

using namespace std;

namespace zzc
{
    typedef long long ll;
    inl ll read()
    {
        ll x=0,f=1;char ch=getchar();
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
        return x*f;
    }

    const ll maxn = 5005;
    const ll inf = 0x3f3f3f3f3f3f3f3f;
    ll n,m,k,cnt,ans;
    ll head[maxn],dis[maxn];
    bool vis[maxn];
    priority_queue<pll> q;

    struct edge
    {
        ll to,nxt,w;
    }e[maxn<<1];

    inl void add(ll u,ll v,ll w)
    {
        e[++cnt].to=v;
        e[cnt].w=w;
        e[cnt].nxt=head[u];
        head[u]=cnt;
    }
    
    inl void dijkstra(ll x)//x 表示我们钦定的第 k 大的边的边权
    {
        memset(dis,0x3f,sizeof(dis));
        memset(vis,false,sizeof(vis));
        dis[1]=0;q.push(mk(0,1));
        while(!q.empty())
        {
            ll u=q.top().sec;q.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(reg ll i=head[u];i;i=e[i].nxt)
            {
                ll v=e[i].to;
                ll w=max(0ll,e[i].w-x);//记得要和 0 取 max
                if(dis[v]>dis[u]+w)
                {
                    dis[v]=dis[u]+w;
                    q.push(mk(-dis[v],v));
                }
            }
        }
         
    }

    void work()
    {
        ll a,b,c;
        n=read();m=read();k=read();
        for(reg ll i=1;i<=m;i++)
        {
            a=read();b=read();c=read();
            add(a,b,c);add(b,a,c);
        }
        dijkstra(0);ans=dis[n];//tip 里提到的情况
        for(ll i=1;i<=(m<<1);i+=2)
        {
            dijkstra(e[i].w);
            ans=min(ans,dis[n]+k*e[i].w);
        }
        printf("%lld\n",ans);
    }


}

int main()
{
	freopen("data.out","r",stdin);
	 freopen("std.out","w",stdout);
    zzc::work();
    return 0;
}
