# min_25筛



## 干什么用的？

min_25筛用于求一类积性函数的前缀和，其使用条件为：

> 1. $f(p)$是一个关于p的简单多项式
>
> 2. $f(p^c)$可以快速的计算

## 约定

约定$P_i$为第i个质数，prime表示质数集合，$ver(i)$表示i的最小质因子



本文所有代码的取模计算用函数实现，具体代码如下：

```cpp
typedef long long ll;
const int mod=1e9+7;
int add(int a,int b){a+=b;return a>=mod?a-mod:a;}
int sub(int a,int b){a-=b;return a<0?a+mod:a;}
int mul(int a,int b){return (ll)a*b%mod;}
int qpow(int a,int b){
    int ret=1;
    for(;b;b>>=1,a=mul(a,a))if(b&1)ret=mul(ret,a);
    return ret;
}
/* math */
```

并且预处理出$\sqrt {n}​$的所有素数以及前缀和

```cpp
int prime[N],pre[N],pcnt,v[N];
inline void getprime(int n){
    for(int i=2;i<=n;i++){
        if(!v[i])prime[++pcnt]=i;
        for(int j=1;j<=pcnt&&(long long)prime[j]*i<=n;j++){
            v[i*prime[j]]=1;
            if(!i%prime[j])break;
        }
    }
    for(int i=1;i<=pcnt;i++)pre[i]=add(pre[i-1],prime[i]);//pre为前缀和
}
```



## 怎么筛

### 1. 考虑质数

我们先考虑将函数全部写成质数时的表达式子，然后求出所有为质数的值，即对于每个n/i，求出
$$
g[n]=\sum_{j\le n \and j \in prime} f(j)
$$
我们记$g[n][j]$表示g[n]筛去前 j 个质数的倍数的情况

显然$P_j^2>n$的时候不会筛掉任何数，考虑容斥掉之前的质数的情况，我们有：
$$
g[n][j]=g[n][j-1] (P_j^2>n)
$$

$$
g[n][j]=g[n][j-1]-f(P_j)(g[\frac {n} {P_j}][j-1]-\sum_{i=1}^{j-1}f(P_i)) （P_j^2\le n）
$$

$$
g[n][0]=\sum f(i)(按照i\in prime 算)
$$

以下以筛素数个数以及筛素数和为例

```cpp
for(ll u=1,v;u<=n;u=v+1){
    v=n/(n/u);
    w[++m]=n/u;
    if(w[m]<=sqr)id1[w[m]]=m;
    else id2[n/w[m]]=m; //此处对于大于/小于根号的分别存储id便于存储
    h[m]=(ll)(w[m]-1)%mod;//h表示素数个数
    g[m]=mul((ll)(w[m]+2)%mod,(ll)(w[m]-1)%mod);//g表示素数和
    if (g[m]&1) g[m]+=mod;g[m]/=2;
}
for(int j=1;j<=pcnt;j++){
    for(int i=1;i<=m&&1ll*prime[j]*prime[j]<=w[i];++i){
        int idd=(w[i]/prime[j])<=sqr?id1[w[i]/prime[j]]:id2[n/(w[i]/prime[j])];
        g[i]=sub(g[i],mul(prime[j],sub(g[idd],pre[j-1])));
        h[i]=sub(h[i],sub(h[idd],j-1));
    }
}
```

### 2.考虑合数

同样的我们可以考虑容斥掉合数。

首先我们定义$S(n,j)=\sum _{i=1}^{n} [ver(i)\ge P_j]f(i)​$

则有$ans=S(n,1)+f(1)$

质数部分的答案是 $h(n,j)=g[n][j]-\sum_{i=1}^{j-1}f(P_i)​$

然后我们枚举最小的质因子并且枚举次幂，有
$$
S(n,j)=h(n,j)+\sum_{k=j}^{P_k^2\le n}\sum_{e=1}^{P_k^{e+1}\le n}S(\frac{n}{P_k^e},k+1)\times f(P_k^e)+f(P_k^{e+1})
$$
边界是$n\le 1 \or P_j>n​$

## 例题：[loj6053简单的函数](https://loj.ac/problem/6053)

首先把$f[i]$当成$i-1$求素数和以及素数个数，相减就是素数的和（2要特判一下）然后直接跑合数的就行了

代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int add(int a,int b){a+=b;return a>=mod?a-mod:a;}
int sub(int a,int b){a-=b;return a<0?a+mod:a;}
int mul(int a,int b){return (ll)a*b%mod;}
int qpow(int a,int b){int ret=1;for(;b;b>>=1,a=mul(a,a))if(b&1)ret=mul(ret,a);return ret;}
/* math */
const int N=1e6 +10;
ll n,sqr;
int prime[N],pre[N],pcnt,v[N];
inline void getprime(int n){
    for(int i=2;i<=n;i++){
        if(!v[i])prime[++pcnt]=i;
        for(int j=1;j<=pcnt&&(long long)prime[j]*i<=n;j++){
            v[i*prime[j]]=1;
            if(!i%prime[j])break;
        }
    }
    for(int i=1;i<=pcnt;i++){
        pre[i]=add(pre[i-1],prime[i]);
    }
}
int h[N];
int g[N];
int m;ll w[N];int id1[N],id2[N];
int S(ll x,ll k){
    if(x<=1||prime[k]>x)return 0;
    int idd=(x<=sqr)?id1[x]:id2[n/x];
    int res=sub(sub(g[idd],h[idd]),sub(pre[k-1],k-1));
    if(k==1)res=add(res,2);
    for(int i=k;i<=pcnt&&1ll*prime[i]*prime[i]<=x;i++){
        ll p1=prime[i],p2=(ll)prime[i]*prime[i];
        for(int e=1;p2<=x;++e,p1=p2,p2*=prime[i]){
            res=add(res,add(mul(S(x/p1,i+1),prime[i]^e),prime[i]^(e+1)));
        }
    }
    return res;
}

int main()
{
    scanf("%lld",&n);sqr=sqrt(n);getprime(sqr);
    for(ll u=1,v;u<=n;u=v+1){
        v=n/(n/u);
        w[++m]=n/u;
        if(w[m]<=sqr)id1[w[m]]=m;
        else id2[n/w[m]]=m;
        h[m]=(ll)(w[m]-1)%mod;
        g[m]=mul((ll)(w[m]+2)%mod,(ll)(w[m]-1)%mod);
        if (g[m]&1) g[m]+=mod;g[m]/=2;
    }
    for(int j=1;j<=pcnt;j++){
        for(int i=1;i<=m&&1ll*prime[j]*prime[j]<=w[i];++i){
            int idd=(w[i]/prime[j])<=sqr?id1[w[i]/prime[j]]:id2[n/(w[i]/prime[j])];
            g[i]=sub(g[i],mul(prime[j],sub(g[idd],pre[j-1])));
            h[i]=sub(h[i],sub(h[idd],j-1));
        }
    }
    printf("%d\n",add(S(n,1),1));
}
```

