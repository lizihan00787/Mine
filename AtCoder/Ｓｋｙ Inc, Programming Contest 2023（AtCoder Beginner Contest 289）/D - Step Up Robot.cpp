#include<bits/stdc++.h>
#define LOCAL
#define int long long
#define int128 __int128
#define ll long long
#define sc(a) scanf("%d",&(a))
#define lsc(a) scanf("%lld",&(a))
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define R(i,a,b) for(int i=(a);i>=(b);--i)
#define endl "\n"
using namespace std;
namespace ly
{
    namespace IO
    {
        #ifndef LOCAL
            constexpr auto maxn=1<<20;
            char in[maxn],out[maxn],*p1=in,*p2=in,*p3=out;
            #define getchar() (p1==p2&&(p2=(p1=in)+fread(in,1,maxn,stdin),p1==p2)?EOF:*p1++)
            #define flush() (fwrite(out,1,p3-out,stdout))
            #define putchar(x) (p3==out+maxn&&(flush(),p3=out),*p3++=(x))
            class Flush{public:~Flush(){flush();}}_;
        #endif
        namespace usr
        {
            template<typename type>
            inline type read(type &x)
            {
                x=0;bool flag(0);char ch=getchar();
                while(!isdigit(ch)) flag^=ch=='-',ch=getchar();
                while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
                return flag?x=-x:x;
            }
            template<typename type>
            inline void write(type x)
            {
                x<0?x=-x,putchar('-'):0;
                static short Stack[50],top(0);
                do Stack[++top]=x%10,x/=10;while(x);
                while(top) putchar(Stack[top--]|48);
            }
            inline char read(char &x){do x=getchar();while(isspace(x));return x;}
            inline char write(const char &x){return putchar(x);}
            inline void read(char *x){static char ch;read(ch);do *(x++)=ch;while(!isspace(ch=getchar())&&~ch);}
            template<typename type>inline void write(type *x){while(*x)putchar(*(x++));}
            inline void read(string &x){static char ch;read(ch),x.clear();do x+=ch;while(!isspace(ch=getchar())&&~ch);}
            inline void write(const string &x){for(int i=0,len=x.length();i<len;++i)putchar(x[i]);}
            template<typename type,typename...T>inline void read(type &x,T&...y){read(x),read(y...);}
            template<typename type,typename...T>
            inline void write(const type &x,const T&...y){write(x),putchar(' '),write(y...),sizeof...(y)^1?0:putchar('\n');}
            template<typename type>
            inline void put(const type &x,bool flag=1){write(x),flag?putchar('\n'):putchar(' ');}
        }
        #ifndef LOCAL
            #undef getchar
            #undef flush
            #undef putchar
        #endif
    }using namespace IO::usr;
}using namespace ly::IO::usr;
int n,m;
map<int,bool> pd;
map<int,bool> p;
int a[12],b[12];
bool vis[12];
int zd;
void dfs1(int x)
{
	if(pd[x]==1 || x>n || x<1 || vis[x]==1) return;
	if(x==zd)
	{
		cout<<"Yes";
		exit(0);
	}
	for(int i=1;i<=n;++i)
	{
		if(p[i]==0)
		{
			vis[x+a[i]]=1;
			p[i]=1;
			dfs1(x+a[i]);
			p[i]=0;
			vis[x+a[i]]=0;
		}
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(int i=1;i<=n;++i)
	{
		read(a[i]);
	}
	read(m);
	int x;
	for(int i=1;i<=m;++i)
	{
		read(x);
		pd[x]=1;
	}
	read(zd);
	for(int i=1;i<=n;++i)
	{
		p.clear();
		p[i]=1;	
		memset(vis,0,sizeof(vis));
		vis[a[i]]=1;
		dfs1(a[i]);
	}
	cout<<"No";
	return 0;
}

