#include<bits/stdc++.h>
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
template<typename PP>
inline void write(PP x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) write(x/10);
    putchar('0'+x%10);
}
int T=1;

const int N=8e4+10;

int n,m;
int a[N],id[N];

mt19937 rnd(time(0));

int root=0,cnt=0;
int x=0,y=0,z=0,w=0;
struct FHQ_Tree{
    #define lson (t[rt].l)
    #define rson (t[rt].r)
    struct node{
        int val,siz,l,r,key;
        int fa;
    }t[N];
    int newnode(int val){
        t[++cnt].siz=1;
        t[cnt].key=rnd();
        t[cnt].val=val;
        id[val]=cnt;
        return cnt;
    }
    void update(int rt){
        t[rt].siz=t[lson].siz+t[rson].siz+1;
    }
    void split(int rt,int &l,int &r,int k,int faa=0,int fab=0){
        if(!rt){
            l=r=0;
            return;
        }
        if(t[lson].siz>=k){
            t[rt].fa=fab;
            r=rt;
            split(lson,l,lson,k,faa,rt);
        }
        else{
            t[rt].fa=faa;
            l=rt;
            split(rson,rson,r,k-t[lson].siz-1,rt,fab);
        }
        update(rt);
    }
    int merge(int x,int y){
        if(!x || !y) return x+y;
        if(t[x].key<t[y].key){
            t[x].r=merge(t[x].r,y);
            t[t[x].r].fa=x;
            update(x);
            return x;
        }
        else{
            t[y].l=merge(x,t[y].l);
            t[t[y].l].fa=y;
            update(y);
            return y;
        }
    }
    void insert(int pos,int val){
        split(root,x,y,pos);
        root=merge(x,merge(newnode(val),y));
    }
    bool get(int x) {return t[t[x].fa].r==x;}
    int find(int cnt){
        int tmp=cnt,res=t[t[cnt].l].siz+1;
        while(tmp!=root && cnt){
            if(get(cnt)) res+=t[t[t[cnt].fa].l].siz+1;
            cnt=t[cnt].fa;
        }
        return res;
    }
    void getval(int rnk){
        int rt=root;
        while(rt){
            if(t[lson].siz+1==rnk) break;
            else if(t[lson].siz>=rnk) rt=lson;
            else rnk-=t[lson].siz+1,rt=rson;
        }
        cout<<t[rt].val<<endl;
    }
}Q;

signed main(){
    auto solve=[&](){
        read(n),read(m);
        for(int i=1;i<=n;++i){
            read(a[i]);
            Q.insert(i-1,a[i]);
        }
        while(m--){
            char op[10];
            scanf("%s",op);
            int d;
            read(d);
            if(op[0]=='T'){
                int k=Q.find(id[d]);
                Q.split(root,x,z,k);
                Q.split(x,x,y,k-1);
                root=Q.merge(y,Q.merge(x,z));
            }
            else if(op[0]=='B'){
                int k=Q.find(id[d]);
                Q.split(root,x,z,k,0);
                Q.split(x,x,y,k-1,0);
                root=Q.merge(x,Q.merge(z,y));
            }
            else if(op[0]=='I'){
                int p;
                read(p);
                int k=Q.find(id[d]);
                if(p){
                    if(p>0){
                        Q.split(root,z,w,k+1);
                        Q.split(z,y,z,k);
                        Q.split(y,x,y,k-1);
                        root=Q.merge(x,Q.merge(z,Q.merge(y,w)));
                    }
                    if(p<0){
                        Q.split(root,z,w,k);
                        Q.split(z,y,z,k-1);
                        Q.split(y,x,y,k-2);
                        root=Q.merge(x,Q.merge(z,Q.merge(y,w)));
                    }
                }
            }
            else if(op[0]=='A'){
                int k=Q.find(id[d]);
                cout<<k-1<<endl;
            }
            else{
                Q.getval(d);
            }
        }
    };
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    //read(T);
    while(T--) solve();
    return 0;
}