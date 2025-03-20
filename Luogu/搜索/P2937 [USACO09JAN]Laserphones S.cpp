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
int m,n,qx,qy,zx,zy;
char mapp[120][120];
bool vis[120][120];
const int xx[4]={1,0,-1,0};
const int yy[4]={0,1,0,-1};
int ans=0x3f3f3f3f;
int sum=0;
/*deque<pair<int,int> > q;
int pd()
{
//	for(auto it:q)
//	{
//		cout<<it.first<<' '<<it.second<<endl;
//	}
	sum=0;
	int kx=q.front().first,ky=q.front().second;
	q.pop_front();
	int fx,fx2;
	if(q.front().first==kx+1) fx=2;
	else if(q.front().first==kx-1) fx=4;
	else if(q.front().second==ky+1) fx=1;
	else fx=3;
	kx=q.front().first;
	ky=q.front().second;
	q.pop_front();
	while(!q.empty())
	{
		if(q.front().first==kx+1) fx2=2;
		else if(q.front().first==kx-1) fx2=4;
		else if(q.front().second==ky+1) fx2=1;
		else fx2=3;
		if(fx!=fx2) sum++;
		kx=q.front().first,ky=q.front().second;
		fx=fx2;
		q.pop_front();
	}
	return sum;
//	cout<<endl<<sum<<endl;
//	exit(0);
}*/
int dis[120][120][5];
void dfs(int x,int y,int p,int to)
{
	if(p>=dis[x][y][to]) return;
	dis[x][y][to]=p;
 	if(p>=ans) return;
	if(x==zx && y==zy)
	{
		ans=p;
		return;
	}
	for(int i=0;i<=3;++i)
	{
		int nx=x+xx[i];
		int ny=y+yy[i];
		if(nx>=1 && nx<=n && ny>=1 && ny<=m && mapp[nx][ny]!='*' && !vis[nx][ny])
		{
			vis[nx][ny]=1;
			int zx=0;
			if(i!=to) zx=1;
			if(to==-1) zx=0;
			dfs(nx,ny,p+zx,i);
			vis[nx][ny]=0;
		}
	}
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(m,n);
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			read(mapp[i][j]);
		}
	}
	bool qd=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			if(mapp[i][j]=='C' && qd==0)
			{
				qx=i,qy=j,qd=1;
			}
			else if(mapp[i][j]=='C' && qd!=0) 
			{
				zx=i,zy=j;
				break; 
			}
		}
	}
	memset(dis,0x3f3f3f3f,sizeof(dis));
	dfs(qx,qy,0,-1);
	cout<<ans;
	return 0;
}
