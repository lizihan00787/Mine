#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define re register
#define PII pair<int,int>
#define fi first
#define se second
#define MOD 998244353
#define io() ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL)
#define mk(a,b) make_pair(a,b)
#define pqd priority_queue<int,vector<int>,less<int> >
#define pqx priority_queue<int,vector<int>,greater<int> >
#define lson (rt>>1)
#define rson (rt>>1|1)
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
const int maxn = 5e5 + 5;
int n;
int num[maxn]; 
int tree0[maxn << 2],tree1[maxn << 2]; 
int left0[maxn << 2],left1[maxn << 2]; 
int right0[maxn << 2],right1[maxn << 2];
int lazy[maxn << 2];
void pushup(int rt,int l,int r) {
	int mid=(l+rt)/2;
	int ln=mid-l+1; 
	int rn=r-mid;
	left0[rt]=left0[lson];
	left1[rt]=left1[lson];
	if (left0[rt]==ln) left0[rt]+=left0[rson];
	if (left1[rt]==ln) left1[rt]+=left1[rson];
	right0[rt]=right0[rson];
	right1[rt]=right1[rson];
	if(right0[rt]==rn) right0[rt]+=right0[lson];
	if(right1[rt]==rn) right1[rt]+=right1[lson];
	tree0[rt]=max(max(tree0[lson],tree0[rson]),right0[lson]+left0[rson]);
	tree1[rt]=max(max(tree1[lson],tree1[rson]),right1[lson]+left1[rson]);
	return;
}
void build(int rt,int l,int r) {
	lazy[rt]=0;
	left0[rt]=right0[rt]=tree0[rt]=0;
	left1[rt]=right1[rt]=tree1[rt]=0;
	if(l==r){
		if(num[l]==1){
			left1[rt]=right1[rt]=tree1[rt]=1;
			left0[rt]=right0[rt]=tree0[rt]=0;
		}
		else{
			left1[rt]=right1[rt]=tree1[rt]=0;
			left0[rt]=right0[rt]=tree0[rt]=1;
		}
		return;
	}
	int mid=(l+r)/2;
	build(lson,l,mid);
	build(rson,mid+1,r);
	pushup(rt,l,r);
}
void Swap(int rt){
	swap(tree0[rt],tree1[rt]);
	swap(left0[rt],left1[rt]);
	swap(right0[rt],right1[rt]);
}
void pushdown(int rt){
	if(lazy[rt]){
		lazy[lson]^=1;
		lazy[rson]^=1;
		lazy[rt]=0;
		Swap(lson);
		Swap(rson);
	}
}
void update(int rt, int l, int r, int uleft, int uright) {
	if(l>=uleft && r<=uright){
		lazy[rt]^=1;
		Swap(rt);
		return;
	}
	int mid=(l+r)/2;
	pushdown(rt);
	if(mid>=uleft) update(lson,l,mid,uleft,uright);
	if(mid<uright) update(rson,mid+1,r,uleft,uright);
	pushup(rt,l,r);
}
int query(int rt,int l,int r,int qleft,int qright){
	if(l>=qleft && r<=qright) return tree1[rt];
	int mid=(l+r)/2;
	pushdown(rt);
	if(qright<=mid) return query(lson,l,mid,qleft,qright);
	if(qleft>mid) return query(rson,mid+1,r,qleft,qright);
	int ll=query(lson,l,mid,qleft,qright);
	int rr=query(rson,mid+1,r,qleft,qright);
	int lr=min(right1[lson],mid-qleft+1)+min(left1[rson],qright-mid);
	return max(max(ll,rr),lr);
}

signed main() {
  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    char c;
    cin >> c;
    num[i] = c - '0';
  }
  build(1, 1, n);
  while (m--) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 2) {
      int res = query(1, 1, n, l, r);
      printf("%d\n", res);
    } else {
      update(1, 1, n, l, r);
    }
  }
}
