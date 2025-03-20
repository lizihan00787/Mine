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
int n,k,Q;
int a[200010];
int sum[200010],t=0;
map<int,int> q;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,k);
	for(int i=1;i<=n;++i) read(a[i]);
	read(Q);
	int l,r;
	for(int i=2;i<=n;++i)
	{
		sum[i-1]=abs(a[i]-a[i-1]);
	}
	while(Q--)
	{
		read(l,r);
		t=0;
		memset(sum,0,sizeof(sum));
		q.clear();
		for(int i=l+1;i<=r;++i)
		{
			sum[++t]=abs(a[i]-a[i-1]);
			q[sum[t]]+=1;
		}
		int num=0;
		for(auto it:q)
		{
			if(it.second==2)
			{
				num++;
			}
		}
		if(q[sum[1]]==2 && q[sum[t]]==2 && (r-l-2*num)%2==1)
		{
			cout<<"Yes"<<endl;
		}
		else cout<<"No"<<endl;
	}
	return 0;
}

