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

#define lowbit(x) (x&(-x))

const int N=3e5+20;

int n,m;
struct node{
	int l,r,id;
	bool operator < (const node &a) const{
		return r<a.r;
	}
}p[N],q[N];
int ans[N];

int t[N];
void add(int k,int x) {for(int i=k;i<N;i+=lowbit(i)) t[i]+=x;}
int query(int k) {int res=0;for(int i=k;i;i-=lowbit(i)) res+=t[i];return res;}


void solve(){
	int res=0;
	memset(t,0,sizeof(t));
    read(n,m);
	for(int i=0;i<n;++i){
		int l,r;
		read(l,r);
		p[i]=node{l,r,0};
	}
	for(int i=0;i<m;++i){
		int num;
		int las=-1;
		read(num);
		while(num--){
			int x;
			read(x);
			q[res++]=node{las,x,i};
			las=x;
		}
		q[res++]=node{las,N-1,i};
	}
	sort(q,q+res);
	sort(p,p+n);
	memset(ans,0,sizeof(ans));
	for(int j=0,i=0;i<res;++i){
        while(j<n && p[j].r<q[i].r) add(p[j].l,1),j++;
		ans[q[i].id]+=query(q[i].r-1)-query(q[i].l);
	}
	for(int i=0;i<m;++i) cout<<n-ans[i]<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//read(T);
    while(T--) solve();
    return 0;
}


