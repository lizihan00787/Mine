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

const int N=5e5+20;

int n,cnt;
int l[N],r[N],a[N];
ll t1[N],t2[N],ans[N];
vector<PII> p[N];

void add1(int k,ll x) {for(int i=k;i<=cnt;i+=lowbit(i)) t1[i]=max(t1[i],x);}
int query1(int k) {ll res=0;for(int i=k;i;i-=lowbit(i)) res=max(t1[i],res);return res;}
void add2(int k,ll x) {for(int i=k;i<=cnt;i+=lowbit(i)) t2[i]=min(t2[i],x);}
int query2(int k) {ll res=0x3f3f3f3f3f3f3f3f;for(int i=k;i;i-=lowbit(i)) res=min(t2[i],res);return res;}

void solve(){
	cnt=0;
    read(n);
	for(int i=1;i<=n;++i){
		read(l[i],r[i]);
		a[++cnt]=l[i],a[++cnt]=r[i];
		ans[i]=0;
	}
	sort(a+1,a+cnt+1);
	cnt=unique(a+1,a+cnt+1)-a-1;
	for(int i=1;i<=n;++i){
		l[i]=lower_bound(a+1,a+cnt+1,l[i])-a;
		r[i]=lower_bound(a+1,a+cnt+1,r[i])-a;
		p[r[i]].push_back(mk(l[i],i));
	}
	for(int i=1;i<=cnt;++i){
		sort(p[i].begin(),p[i].end());
		t1[i]=0,t2[i]=0x3f3f3f3f3f3f3f3f;
	}
	PII las;
	for(int i=cnt;i;--i){
		las=mk(0,0);
		for(auto j:p[i]){
			if(las.first==j.first) ans[las.second]=0;
			else{
				int res1=query1(j.first),res2=query2(j.first);
				if(res1>=1 && res2<=cnt) ans[j.second]=a[query2(j.first)]-a[query1(j.first)];
				add1(j.first,j.first),add2(j.first,i);
			}
			las=j;
		}
		p[i].clear();
	}
	for(int i=1;i<=n;++i) cout<<max(0ll,ans[i]-a[r[i]]+a[l[i]])<<endl;
}

signed main(){
    //freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(T);
    while(T--) solve();
    return 0;
}


