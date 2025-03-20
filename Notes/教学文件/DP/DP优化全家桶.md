[TOC]



# DP优化全家桶

本质上是DAG上沿着拓扑序递归（没有后效性），从递归的子问题思考。

DP本身的过程是不难的，难的是分析性质和DP的优化。

一般的优化思路：

- 减少DP状态，一般利用DP性质
- 转移的优化，分析dp式子，一般用数据结构
- 内存优化，一般不需要，开不时要滚动数组一下。
- 决策上的单调性、斜率优化，WQS二分等。

## 前缀和优化

状态是由一段前缀的状态转移来的，用前缀和优化。

### P2513 [HAOI2009] 逆序对数列  

对于一个数列 $\{a_i\}$，如果有 $i<j$ 且 $a_i>a_j$，那么我们称 $a_i$ 与 $a_j$ 为一对逆序对数。若对于任意一个由 $1 \sim n$ 自然数组成的数列，可以很容易求出有多少个逆序对数。那么逆序对数为 $k$ 的这样自然数数列到底有多少个？

100%的数据  n<=1000，k<=1000









### Sol

令$f_{i,j}$ 为前 $i$ 小的数排列，有 $j$ 对逆序对的方案数。

$f_{i,j}=\displaystyle\sum_{k=1}^{k\leq i}f_{i-1,j-k}$。

 转移是一段前缀，用前缀和优化。

### P2511 [HAOI2008] 木棍分割  

有n根木棍, 第i根木棍的长度为Li,n根木棍依次连结了一起, 总共有n-1个连接处. 现在允许你最多砍断m个连接处, 砍完后n根木棍被分成了很多段,要求满足总长度最大的一段长度最小, 并且输出有多少种砍的方法使得总长度最大的一段长度最小. 并将结果**mod 10007**。。。

   n<=50000, 0<=m<=min(n-1,1000).

1<=Li<=1000.







### Sol

“最大的最小”显然二分。二分出这个长度后再求方案数。

令 $f_{i,j}$ 表示前 $i$ 根木棍分为 $j$ 组的方案数。

$f_{i,j}=\displaystyle\sum_{k=t}^{i-1}f_{k,j-1}$

其中 $t$ 是最小的满足 $\displaystyle\sum_{k=t+1}^{i}a_k\leq 二分出的长度$

每次找 $t$ 是 $n^3$ 的，可以 $n^2$ 预处理出每个位置对应的 $t$。

相应的求和用前缀和优化。

卡空间，用滚动数组。

### 修剪草坪

在一年前赢得了小镇的最佳草坪比赛后，FJ  变得很懒，再也没有修剪过草坪。现在，新一轮的最佳草坪比赛又开始了，FJ 希望能够再次夺冠。 然而，FJ 的草坪非常脏乱，因此，FJ  只能够让他的奶牛来完成这项工作。FJ 有 N 只排成一排的奶牛，编号为 1 到 N。每只奶牛的效率是不同的，奶牛 i的效率为 Ei 。  靠近的奶牛们很熟悉，如果 FJ 安排超过 K 只连续的奶牛，那么这些奶牛就会罢工去开派对。因此，现在 FJ 需要你的帮助，计算 FJ  可以得到的最大效率，并且该方案中没有连续的超过 K 只奶牛。 







### Sol

令 $f_{i,0/1}$ 表示考虑到前 $i$ 只奶牛，第 $i$ 只选/不选的方案数。

$f_{i,0}=max(f_{j,0},f_{j,1})(j<i)$

$f_{i,1}=max(f_{j,0}-S_{j-1})+S_i$，其中 $S_i$ 为前缀和。

### 习题

 P1776 宝物筛选  （单调队列的做法）

 P4099 [HEOI2013] SAO  

## 单调队列优化

前置技能：单调队列（经典的问题模型：洛谷P1886 滑动窗口）

用于优化形如 $f_i=\min/\max_{j=l_i}^{i-1}\{g_j\}+w_i$，且满足 $l_i\le l_{i+1}$的转移。

人话：对于序列中的每个点，从其左侧一段决策区间内的最值进行转移，且决策区间随着序列下标的增大也不断右移（就像窗口向右滑动）。

设 $j<k$，容易发现如果 $g_j$ 劣于 $g_k$ 的话，那么当决策区间移动到 $k$ 以后，$j$ 永远不会成为最优决策点，再也不会被转移了。

于是，我们只要维护一个队列，满足下标递增，决策性递减。我们需要当前的队首成为最优决策点，那么当队首第一次超出了区间范围（以后也就永远超出了）就把它出队。为了保证单调性，队尾新加入点之前，要先把队列中比它劣的点依次从队尾出队。

### P3594 [POI2015] WIL  

给定一个长度为 $n$ 的序列，你有一次机会选中一段连续的长度不超过 $d$ 的区间，将里面所有数字全部修改为 $0$。请找到最长的一段连续区间，使得该区间内所有数字之和不超过 $p$。

对于 $100\%$ 的数据，$1 \le d \le n \le 2 \times 10^6$，$0 \le p \le 10^{16}$，$1 \leq w_i \leq 10^9$。







### Sol

略

### CF1077F2

给你一个数列$a$，你需要选择$m$个元素，使得连续的$k$个元素都至少有一个被选中。

需要你最大化选出来的所有数的和。

 $ 1 \le k, x \le n \le 5000 $ 







### Sol

令 $f_{i,j}$ 为考虑前 $i$ 个数，已经选了 $j$ 个且第 $i$ 个数被选了的最大和。

转移是一段长度为 $k$ 的区间中的最值。

### P2254 [NOI2005] 瑰丽华尔兹







### Sol

若令 $f_{t,i,j}$ 为在时间 $t$ 时在 $(i,j)$ 处的最长路径，复杂度 $O(TNM)$。

注意到某一时间段内方向是一样的，令 $f_{k,i,j}$ 为第 $k$ 段时间后在 $(i,j)$ 的最长路径。

转移是一段区间。

### P2569 [SCOI2010] 股票交易  









### Sol

令 $f_{i,j}$ 为第 $i$ 天手里有 $j$ 张股票的最大价值。

直接转移复杂度 $n^3$，考虑用单调队列优化“至多卖/买”的限制。

### 习题

P3572 [POI2014] PTA-Little Bird  

## 数据结构优化

在移区间或对应转移的值域是一段区间，且随状态的改变对应区间没有单调性，用数据结构维护一下。

### P4644 [USACO05DEC] Cleaning Shifts S  







### Sol

每次的转移是一段长度不定的区间，用线段树维护。

也有最短路的做法

### P2605 [ZJOI2010] 基站选址  





### Sol

朴素dp：令 $f_{i,j}$ 为第 $i$ 个村庄修建第 $j$ 个基站且不考虑第 $i+1$ ~ $n$ 个村庄所需的最小费用。复杂度 $n^2k$。

转移用前缀和+线段树优化为 $nlognk$。

### P3287 [SCOI2014] 方伯伯的玉米田







### Sol

拔高区间显然 $[l,n]$ 最优。

令 $f_{i,j}$ 为第 $i$ 个数拔高 $j$ 的以 $i$ 结尾的最长序列长度。

 $\large f_{i,j} = \max_{1\le k<i,\ 0\le l\le j,\ a_k+l \le a_i+j}\{f_{k,l}\} + 1$

二维树状数组优化。

还有一种神秘的单log写法：https://www.luogu.com.cn/article/jf6847hh

## 斜率优化

对于一些dp，转移方程形如： $f_i=max(f_j+w_j\times(i-j))$

可将式子转化为 $f_i=max(w_j\times i +f_j-w_j\times j)$

令 $k=w_j,b=f_j-w_j\times j$，两者均为定值。若将 $i$ 视作横坐标 $x$，$f_j$ 视作纵坐标 $y$，则是一条一次函数线。

转移即是对于一堆一次函数的集合，求在某一个特定的 $x$ 上 $y$ 的最值是多少。



若随 $i$ 递增，斜率具有单调性，则可以用栈维护一个凸壳。

不具有单调性的可以用李超线段树等。（也有什么平衡树/cdq的写法但我不会）

### P2900 [USACO08MAR] Land Acquisition G  







### Sol

按高为第一关键字，宽为第二关键字从大到小排序，剩下的就是一个高度递减、宽度递增的矩形序列。考虑怎样制定它们的并购方案会最优。显然如果要并购，一定要挑序列中的一段区间，这样贡献答案的就只有最左边矩形的高乘上最右边矩形的宽，中间的又是没有贡献了。

写DP式子就是一个斜率优化板子。

代码如下（为了保证精度手写了分数）

~~~
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=50001;
int sng(int x){return (x>0)-(x<0);}
struct fraction{
	int x,y;
	fraction(int x = 0,int y = 0):x(sng(x^y)*abs(x)),y(abs(y)){}
	bool operator <=(const fraction &a)const{return x*a.y<=a.x*y;}
};
const fraction NEGINF={INT_MIN,1};
struct Line{
	int k,b;
	fraction x;
	Line(int kk = 0, int bb = 0,fraction xx = NEGINF){
		k=kk;b=bb;x=xx;
	}
	int operator [](int x){return x*k+b;}
	fraction operator &(const Line &a){return {a.b-b,k-a.k};}
};
deque<Line>Q;
struct kkk{
	int x,y;
}q[N],p[N];
bool cmp_k(kkk a,kkk b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
int n,m,dp[N];
int query(int x){
	fraction fx={x,1};
	while(Q.size()>1&&Q[1].x<=fx){
		Q.pop_front();
	}
	Q.front().x=NEGINF;
	return Q.front()[x];
}
void updata(const Line &now){
	fraction x=NEGINF;
	while(!Q.empty()&&(x=Q.back()&now)<=Q.back().x){
		Q.pop_back();
	}
	Q.push_back((Line){now.k,now.b,x});
	return ;
	
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d%d",&q[i].x,&q[i].y);
	sort(q+1,q+1+n,cmp_k);
	for(int i=n;i>=1;i--){
		if(q[i].x==0||q[i].y==0)continue;
		p[++m].x=q[i].x;
		p[m].y=q[i].y;
		int k=i-1;
		while(k>0&&q[k].y<=q[i].y){
			q[k].x=0;q[k].y=0;
			k--;
		}
	}
	sort(p+1,p+1+m,cmp_k);
	for(int i=1;i<=m;i++){
		updata({p[i].y,dp[i-1]});
		dp[i]=query(p[i].x);
	}
	printf("%lld",dp[m]);
	return 0;
}
~~~

### P4360 [CEOI2004] 锯木厂选址









### Sol

略

### P3628 [APIO2010] 特别行动队







### Sol

 显然先预处理前缀和$s(i)=\sum_{k=1}^ix_i$

设$d(i)$为将前$i$个士兵分组的最大修正后战斗力。

$d(i)=max\{\ d(j)+a(s(i)-s(j))^2+b(s(i)-s(j))+c\ \}$

$d(i)=max\{\ d(j)+a\times s(i)^2-2a\times s(i)s(j)+a\times s(j)^2+b\times s(i)-b\times s(j)+c\ \}$

$d(i)=max\{\ d(j)-2a\times s(i)s(j)+a\times s(j)^2-b\times s(j)\ \}+a\times s(i)^2+b\times s(i)+c$

### 习题

 P1721 [NOI2016] 国王饮水记  

 P2305 [NOI2014] 购票  

## 决策单调性

一般分两类。无论是哪一类都需要细心发现决策之间的递变规律。

一种是用于优化形如 $f_{i}=\min/\max w_{i,j}$，且决策点单调递增的。

这样的方程对题目的性质要求较高。

只需要维护指针，按照单调性不断寻找最优答案即可。

另一种是形如$f_i=\min/\max_{j=1}^{i-1} g_j+w_{i,j}$，且记  $f_i$ 的最优决策点为 $p_i$，若满足$p_i<=p_{i+1}$，则该方程满足决策单调性。（这种又叫四边形不等式优化）

我一般用分治做法。

既然转移过程是单调并且离线的，我们考虑分治。假设当前我们求解一段区间  $f_{l,r}$，而所有 $f_{l,r}$ 的最优决策点在 $[L,R]$ 之间。对于 $[l,r]$ 的中点 $mid$，我们可以暴力扫一遍 $L−R$，找到它的最优决策点 $k$。因为决策单调，所以 $f_{l,mid−1}$的决策落在 $[L,k]$ 上，而 $f_{mid+1,r}$ 的决策落在 $[k,R]$ 上，变成了两个规模减半的小问题。与分治复杂度一样是 $nlogn$ 的。



一般考场上不要求证明，打表猜到单调性后直接用就行。

### P3515 [POI2011] Lightning Conductor  

给定一个长度为 $n$ 的序列 $\{a_n\}$，对于每个 $i\in [1,n]$ ，求出一个最小的非负整数 $p$ ，使得 $\forall j\in[1,n]$，都有 $a_j\le a_i+p-\sqrt{|i-j|}$

$1 \le n \le 5\times 10^{5}$，$0 \le a_i \le 10^{9}$ 。







### Sol

图像分析得有单调性。



是不是有点像斜率优化？

### 习题

 P1973 [NOI2011] NOI 嘉年华

 P1912 [NOI2009] 诗人小G  

 cf868f Yet Another Minimization Problem  





还有神秘的wqs二分优化DP。