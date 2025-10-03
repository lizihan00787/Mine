#include<bits/stdc++.h>
using namespace std;
#define re register
#define il inline
#define int long long
il int read()
{
    re int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
struct Edge
{
	int u,v,w;
}edge[200005];
int fa[5005],n,m,ans,eu,ev,cnt;
il bool cmp(Edge a,Edge b)
{
    return a.w<b.w;
}
il int find(int x)
{
    while(x!=fa[x]) x=fa[x]=fa[fa[x]];
    return x;
}
int k;
il void kruskal()
{
    sort(edge,edge+m,cmp);
    for(re int i=0;i<m;i++){
        eu=find(edge[i].u), ev=find(edge[i].v);
        if(eu==ev){
            continue;
        }
        ans+=(edge[i].w%k);
        ans%=k;
        fa[ev]=eu;
        if(++cnt==n-1){
            break;
        }
    }
}
signed main(){
    n=read(),m=read(),k=read();
    for(re int i=1;i<=n;i++){
        fa[i]=i;
    }
    for(re int i=0;i<m;i++)
    {
        edge[i].u=read(),edge[i].v=read(),edge[i].w=read();
    }
    kruskal();
    printf("%d",ans);
    return 0;
}
