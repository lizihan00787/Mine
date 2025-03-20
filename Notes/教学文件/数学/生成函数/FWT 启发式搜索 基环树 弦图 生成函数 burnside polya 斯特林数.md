

# 斯特林数

只讲第二类斯特林数。

记 $n\brace m$ 表示把 $n$ 个不同的元素划分为 $m$ 个无序非空集合的方案数。



**递推式**

如果考虑最后一个元素单独成一个集合或者和前面的元素一起构成集合，那么就有： 
$$
{n\brace m}={n-1\brace m-1}+m{n-1\brace m}
$$






**通项公式**

如果考虑二项式反演容斥一下空集个数，那么就有：
$$
{n\brace m}=\frac1{m!}\sum_{i=0}^m{(-1)^{m-i}\binom mii^n}
$$
注意到后面形如卷积，所以可以直接 $O(n\log n)$ 求斯特林数一行。







**下降幂转普通幂**
$$
x^n=\sum_{i=0}^n{{n\brace i}\binom xii!}
$$






证明：

$x^n$ 的组合意义是把 $n$ 个不同的元素放进 $x$ 个不同的可空集合中。

那么先从 $x$ 个集合中选 $i$ 个，然后再把 $n$ 个元素有序划分为 $i$ 个部分，每个部分依次放进每个集合，组合意义与 $x^n$ 相同。



# 生成函数

将数列 $\{a_i\}$ 写成一个函数 $A(x)=\sum{a_ix^i}$ 的形式叫做普通生成函数。

此处的 $x^i$ 没有实际意义，只是一个占位符。

对于生成函数来说，绝大数运算法则都是同平常所说的函数一样的。

例如 $A(x)+B(x) = \sum\limits{(a_i+b_i)x^i}$ 和 $A(x)B(x)=\sum\limits_i\sum\limits_j(a_ib_j)x^{i+j}$。



一些常见的数列都可以写作生成函数的形式，而且往往都有较为简单的形式：

- $\{1,0,0\dots\}\rightarrow1$
- $\{1,1,1\dots\}\rightarrow1+x+x^2+\dots=\frac1{1-x}$
- $\{1,2,3\dots\}\rightarrow1+2x+3x^2+\dots=(1+x+x^2+\dots)'=(\frac1{1-x})'=\frac1{(1-x)^2}$
- $\{1,p,p^2\dots\}\rightarrow1+px+(px)^2+\dots=\frac1{1-px}$
- $\{\binom n0,\binom n1,\binom n2\dots\}\rightarrow(1+x)^n$



#### 例题一

求 $a_n=f(n)$ 的生成函数的封闭形式，其中 $f(x)=\sum\limits_{i=0}^{k-1}{f_ix^i}$。









#### 解法

$$
\begin{aligned}
\sum_{i\geq0}{f(i)x^i}&=\sum_{i\geq0}x^i\sum_{j=0}^{k-1}{f_ji^j}
\\
&=\sum_{i\ge0}{x^i\sum_{j=0}^{k-1}{f_j\sum_{t=0}^j}{{j\brace t}i^{\underline{t}}}}
\\
&=\sum_{t=0}^{k-1}\sum_{j=t}^{k-1}f_j{j\brace t}\sum_{t=0}^j{j\brace t}\sum_{i\ge0}{x^ii^{\underline t}}
\\
&=\sum_{t=0}^{k-1}\sum_{j=t}^{k-1}f_j{j\brace t}x^t(\frac1{1-x})^{(t)}
\\
&=\sum_{t=0}^{k-1}\sum_{j=t}^{k-1}f_j{j\brace t}\frac{x^t(-1)^{\underline t}}{(1-x)^{t+1}}
\\
&=\sum_{t=0}^{k-1}\frac{x^t(-1)^{\underline t}}{(1-x)^{t+1}}\sum_{j=t}^{k-1}f_j{j\brace t}
\end{aligned}
$$

化成这样就挺封闭了。







#### 例题二 P10780食物

在许多不同种类的食物中选出 $n$ 个，每种食物的限制如下：

1. 承德汉堡：偶数个
2. 可乐：0 个或 1 个
3. 鸡腿：0 个，1 个或 2 个
4. 蜜桃多：奇数个
5. 鸡块：4 的倍数个
6. 包子：0 个，1 个，2 个或 3 个
7. 土豆片炒肉：不超过一个。
8. 面包：3 的倍数个

每种食物都是以「个」为单位，只要总数加起来是 $n$ 就算一种方案。对于给出的 ![n](data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7) 你需要计算出方案数，对 $10007$ 取模。

$n\leq10^{500}$





#### 解法

每种物品的生成函数分别为

- $\frac{1}{1-x^2}$

- $1+x$
- $1+x+x^2$
- $\frac x{1-x^2}$
- $\frac 1{1-x^4}$
- $1+x+x^2+x^3$
- $1+x$
- $\frac 1{1-x^3}$

全部乘起来可以得到 $\frac x{(1-x)^4}$，也就是 $\sum\limits_{i\ge0}x^{i+1}\frac{i^{\overline 3}}{3！}=\sum\limits_{i\ge1}{x^i\binom{i+2}3}$。

所以答案就是 $\binom {n+2}3 = \frac{n(n+1)(n+2)}{6}$。







#### 例题三 P4389 付公主的背包

有 $n$ 种物品，每个物品有个体积 $v_i$ 且有无限个，对于所有 $s\in[1,m]$ 求恰好凑出 $s$ 体积的方案数。

$n,m,v_i\leq10^5$









#### 解法

每个物品的生成函数即为 $\frac1{1-x^{v_i}}$，要求的就是 $\prod\limits_{i=1}^n\frac1{1-x^{v_i}}$。

求乘积的一个经典做法就是 $\ln$ 一下然后求和。

所以原式就是：
$$
\begin{aligned}
\exp(\sum\limits_{i=1}^n\ln(\frac{1}{1-x^{v_i}}))&=\exp(\sum\limits_{i=1}^n\int(\frac1{1-x^{v_i}})'(1-x^{v_i})\mathrm{d} x)
\\
&=\exp(\sum\limits_{i=1}^n\int\frac{v_ix^{v_i-1}}{1-x^{v_i}}\mathrm{d}x)
\\
&=\exp(\sum\limits_{i=1}^n\int(\sum\limits_{j\ge1}{v_ix^{jv_i-1}})\mathrm{d}x)
\\
&=\exp(\sum\limits_{i=1}^n\sum\limits_{j\geq0}\frac{x^{jv_i}}j)
\end{aligned}
$$
做到这里就好了，后面那个 $\sum$ 只在 $v_i$ 的倍数处有取值，所以统计每种 $v_i$ 的个数然后再把贡献加上去这一步复杂度是 $O(m\log m)$ 的，最后 $\exp$ 回去又是一个 $O(m\log m)$。









# 集合幂级数卷积

我们定义一个集合幂级数为一个映射，把全集 $U$ 的每一个子集 $S$ 映射到一个值 $t$ 。

类似于生成函数，那么一个对应关系我们可以写作 $tx^S$，整个映射我们就可以写成所有对应关系加起来。

集合幂级数的加法是很好定义的，主要是看乘法。

为了有更好的性质，我们首先要求集合幂级数的乘法对加法有分配律，所以就有：
$$
H(x)=\sum_{P,Q\in U}{f_pg_q(x^{P\otimes Q})}
$$
为了让集合幂级数的乘法满足交换律和结合律， $\otimes$ 也得满足结合律和交换律。

and，or，xor 等运算就是符合条件的 $\otimes$。



#### and 卷积

$$
h_k=\sum_{i\&j=k}f_ig_j
$$

用大写的 $F,G,H$ 来代表三个序列对应的集合幂级数。

考虑分治解决：

把 $F$ 分成 $F_0$ 和 $F_1$，$F_0$ 表示 $F$ 中不含元素 $t$ 的子集，去掉元素 $t$ ，所构成的集合幂级数，$F_1$ 表示剩余集合去掉 $t$ 所构成的集合幂级数。

$G$ 同理。

那么 
$$
\begin{aligned}
F\times G &= (F_0 + x^{\{t\}}F_1)(G_0+x^{\{t\}}G_1)
\\
&=F_0G_0+F_0G_1+F_1G_0+x^{\{t\}}F_1G_1
\end{aligned}
$$
如果直接分治的话，复杂度仍然是 $O(n^2)$ 没有优化。

但是注意到如果令 $P=F_1G_1$，$Q=(F_0+F_1)(G_0+G_1)$，那么 $F\times G=Q-P+x^{\{t\}}P$。

所以只需要递归两边即可，复杂度是 $O(n\log n)$。

对于 or 卷积同理。

对于 xor 卷积，$F\times G=F_0G_0+F_1G_1+x^{\{t\}}(F_0G_1 + F_1G_0)$。

所以令 $P=(F_0+F_1)(G_0+G_1)$，$Q=(F_0-F_1)(G_0-G_1)$，那么 $F\times G=\frac{P+Q}2+x^{\{t\}}\frac{P-Q}2$。

同样做到了 $O(n\log n)$。

为了做到优秀的实现，我们可以不进行递归，直接每一个元素对应的求 $P$、$Q$ 操作一起做完了之后再来求 $H$。



这样看似是取巧的做法，其背后真正的逻辑到底是什么呢？



我们希望 $\mathrm{DFT}(H)_i=\mathrm{DFT}(F)_i\times\mathrm{DFT}(G)_i$

我们理想中的 $\mathrm{DFT}(F)$ 应该为矩乘的形式 $\mathrm{DFT}(F)_i=\sum\limits_{j=0}^{n-1}A_{i,j}f_j$。

因此需要满足：
$$
\begin{aligned}
\sum_{j=0}^{n-1}A_{i,j}h_j=\sum_{j=0}^{n-1}A_{i,j}\sum_{k\otimes l=j}f_kg_l=\sum_{j,k}f_jg_kA_{i,j\otimes k}&=\sum_{j=0}^{n-1}A_{i,j}f_j\times\sum_{j=0}^{n-1}A_{i,j}g_j
\\
&=\sum_{j,k}{f_jg_kA_{i,j}A_{i,k}}
\end{aligned}
$$
也就是需要满足：
$$
A_{i,j\otimes k}=A_{i,j}A_{i,k}
$$
由于位运算具有每一位独立的特性，我们可以按位拆开，只需要 $A_{i_p,j_p\otimes k_p}=A_{i_p,j_p}A_{i_p,k_p}$ 即可。

因此如果 $\otimes$ 是 $or$ 运算，我们可以得到一个符合条件的矩阵 $[\begin{aligned}1\ 0\\1\ 1\end{aligned}]$。

于是我们每一位分别按照这个矩阵去卷，就是 $\mathrm{DFT}$。

这个矩阵的逆是 $[\begin{aligned}1\ 0\\-1\ 1\end{aligned}]$，每一位分别卷这个逆就是 $\mathrm{IDFT}$。





**高维前缀和**

容斥做法没有前途。

考虑每一维分别做一次前缀和就好了。







#### 例题四 P5387 [Cnoi2019] 人形演舞

Cirno 与 Marisa 之间有一个博弈:

首先给定 一个 **可重正整数集合** $V$, 所有的数字都是在 $[1, m]$ 之间。

每次一个人可以选取 $x \in V, y \in [1, x]$, 且 $ x \oplus y \in [0, x)$ , 然后把  $x$ 变为 $x \oplus y$。

$\oplus$ 表示按位异或。

当一个人不能操作时, 则视作失败。

假定 Cirno 和 Marisa 都使用最优策略。

现在 Cirno 想知道自己先手时获胜的方案数对 $998244353$ 取模后是多少。

$|V| \le 10^{18}, m \le 10^6$。









#### 解法

打表可知 $SG(2^k+x)=x+1$。

所以相当于问从 $[1,m]$ 的 $SG$ 值中选 $|V|$ 个使其异或值为 $0$。

记 $A=\sum\limits_{i=1}^m{x^{\{SG(i)\}}}$，那么就是要求 $A^{|V|}$。

每次都 $\mathrm{FWT}$ 一遍显然不对，所以只需要做一遍然后每个数求 $|V|$ 次方，再 $\mathrm{FWT}$ 回去即可。





#### 例题五 #310. 【UNR #2】黎明前的巧克力

给定一个集合，求有多少对不交子集的异或和相等。

$n,a_i\leq10^6$









#### 解法

枚举不交子集的并 $S$，那么这个并首先需要异或和等于 $0$，然后他对答案的贡献为 $2^{|S|}$。

把 $2^{|S|}$ 拆成 $|S|$ 个 $2$ 相乘，把每个 $2$ 分摊到组成 $S$ 的元素上，

那么就是需要求 $\prod\limits_{i=1}^{n}(1+2x^{a_i})$。

直接每个集合幂级数都 $\mathrm{FWT}$ 之后乘起来复杂度显然不对。

注意到 $\mathrm{FWT}(1+2x^k)_i$ 的结果为 $\sum\limits_{j}{(-1)^{|i\&j|}}a_j$，所以只有 $-1$ 和 $3$ 两种取值，所以最终结果一定形如 
$(-1)^{k_i}3^{n-k_i}$。

注意到 $\sum\limits_{i=1}^n\mathrm{FWT}(1+2x^{a_i})=\mathrm{FWT}(\sum\limits_{i=1}^n(1+2x^{a_i}))$，所以我们依据加出来的数据可以解出 $k_i$，然后就能还原出 $\mathrm{FWT}(\prod\limits_{i=1}^n(1+2x^{a_i}))$，再 $\mathrm{IFWT}$ 一下即可。



**子集卷积**

$$
h_k=\sum_{i|j=k\and i\&j=0}{f_ig_j}
$$




**解法**

容易发现其充要条件为 $i|j=k\and |i|+|j|=|k|$。

考虑



**exp、ln**



