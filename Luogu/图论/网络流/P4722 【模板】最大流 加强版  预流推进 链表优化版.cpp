#include<bits/stdc++.h>
#define int long long
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
        res=res*10+ch-'0';
        ch=getchar();
    }
    x=res*f;
}
const int N=2e3+10,Max=2e5+10,inf=1e18;
int n,m,s,t,h[N],ex[N],gap[N];
struct edge{
    int v,w,nxt;
};
vector<edge> e[N];
list<int> g[N];
int lev=0;
void add(int u,int v,int w){
    e[u].push_back({v,w,e[v].size()}); 
    e[v].push_back({u,0,e[u].size()-1});
}
void init(){
    int u=s;
    for(auto it=e[u].begin();it!=e[u].end();it++){
        int v=it->v,w=it->w;
        if(!w || h[v]==inf) continue;
        if(v!=s && v!=t && !ex[v]) g[h[v]].push_back(v),lev=max(lev,h[v]);
        it->w-=w,e[v][it->nxt].w+=w,ex[u]-=w,ex[v]+=w;
    }
}
bool push(int u){
    for(auto it=e[u].begin();it!=e[u].end();it++){
        int v=it->v,w=it->w;
        if(!w || h[u]!=h[v]+1) continue;
        if(v!=s && v!=t && !ex[v]) g[h[v]].push_back(v),lev=max(lev,h[v]);
        w=min(w,ex[u]);
        ex[u]-=w,ex[v]+=w,it->w-=w,e[v][it->nxt].w+=w;
        if(!ex[u]) return 0;
    }
    return 1;
}
void relabel(int u){
    h[u]=inf;
    for(auto it=e[u].begin();it!=e[u].end();it++){
        int v=it->v,w=it->w;
        if(w) h[u]=min(h[v],h[u]);
    }
    if(++h[u]<n){
        g[h[u]].push_back(u);
        lev=max(lev,h[u]);
        gap[h[u]]++;
    }
}
bool bfs(){
    for(int i=1;i<=n;++i) h[i]=inf;
    list<int> q;
    q.push_back(t);
    h[t]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
        for(auto it=e[u].begin();it!=e[u].end();it++){
            int v=it->v,w=it->w;
            if(!w && h[v]>h[u]+1) h[v]=h[u]+1,q.push_back(v);
        }
    }
    return h[s]==inf;
}
int maxh(){
    while(g[lev].empty() && ~lev) lev--;
    return lev==-1?0:g[lev].back(); 
}
int HLPP(){
    if(bfs()) return 0;
    for(int i=1;i<=n;++i) if(h[i]!=inf) ++gap[h[i]];
    h[s]=n;
    init();
    int u;
    u=maxh();
	while(u){
		g[lev].pop_back();
		if(push(u)){
			if(!--gap[h[u]]){
                for(int i=1;i<=n;++i){
                    if(i!=s && h[i]>h[u] && h[i]<=n) h[i]=n+1;
                }
			}
			relabel(u);
		}
        u=maxh();
	}
	return ex[t];
}
signed main(){
    int u,v,w;
    read(n),read(m),read(s),read(t);
    for(int i=1;i<=m;++i){
        read(u),read(v),read(w);
        add(u,v,w);
    }
    cout<<HLPP()<<endl;
    return 0;
}
