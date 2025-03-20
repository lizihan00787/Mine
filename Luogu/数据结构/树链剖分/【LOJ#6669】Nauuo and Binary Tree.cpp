#include<bits/stdc++.h>
#define endl '\n'
#define ll long long
#define mk(a,b) make_pair(a,b)
#define PII pair<int,int>
using namespace std;
template<typename P>
void read(P &x){
    P res=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
	     if(ch=='-') f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    x=res*f;
}
template<typename PP,typename ...Arc>
void read(PP &x,Arc &...y) {read(x),read(y...);}
int T=1;

const int N=3020;

int n;

int dep[N],siz[N],tp[N],f[N],son[N],id[N];
int jump[N][N];
int ch[N][2];
unordered_map<int,int> mp;

void dfs1(int u,int fa){
	siz[u]=1;
	son[u]=0;
	for(int i=0;i<2;++i){
		int to=ch[u][i];
		if(!to) continue;
		dfs1(to,u);
		siz[u]+=siz[to];
		if(siz[to]>siz[son[u]]) son[u]=to;
	}
}
void dfs2(int u,int top){
	tp[u]=top;
	if(dep[u]>dep[mp[top]]) mp[top]=u;
	if(son[u]) dfs2(son[u],top);
	int to=ch[u][0]^ch[u][1]^son[u];
	if(to) dfs2(to,to);
}
void upd(int u){
	for(int i=1;i<=dep[f[u]];++i) jump[u][i]=jump[f[u]][i];
	jump[u][dep[u]]=u;
}


void work(int u){
	int atk=1,tmp=0;
	while(true){
		atk=mp[tp[atk]];
		cout<<'?'<<' '<<atk<<' '<<u<<endl;
        fflush(stdout);
		read(tmp);
		if(tmp==1){
			f[u]=atk;
			ch[atk][0]=u;
			break;
		}
		int d=(dep[u]+dep[atk]-tmp)>>1,fff=jump[atk][d+1];
		atk=jump[atk][d];
		atk=ch[atk][0]^ch[atk][1]^fff;
		if(!atk){
			f[u]=f[fff];
			ch[f[fff]][1]=u;
			break;
		}
	}
}

bool cmp(int a,int b) {return dep[a]<dep[b];}

void solve(){
	read(n);
	dep[1]=1;
	jump[1][1]=1;
	for(int i=2;i<=n;++i){
		printf("? 1 %d\n",i);
        fflush(stdout);
		read(dep[i]);
		++dep[id[i]=i];
	}
	sort(id+2,id+n+1,cmp);
	for(int i=2;i<=n;++i){
		mp.clear();
		dfs1(1,0),dfs2(1,1);
		work(id[i]),upd(id[i]);
	}
	printf("!");
	for(int i=2;i<=n;++i) printf(" %d",f[i]);
	puts("");
    fflush(stdout);
	cout<<endl;

}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


