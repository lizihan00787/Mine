# 暴力多项式全家桶

P.S. 在本节范围内，所有同余号（多项式运算）均在 $\pmod{x^n}$ 意义下进行；所有等号（代数运算）均在模某个质数 $p$ 意义下进行。



**加法**

$H(x)=F(x)+G(x)$

求 $H(x)$。



**Sol**



**乘法**

$H(x)\equiv F(x)G(x)\pmod{x^n}$

求 $H(x)$。



**Sol**







**求逆**

$F(x)G(x)\equiv1\pmod{x^n}$

求 $G(x)$。









**Sol**







**取模**

$F(x)\equiv Q(x)G(x)+R(x)\pmod{x^n}$

求 $Q(x),R(x)$







**Sol**







**求导&积分**

$G(x)=F'(x)$

$H(x)=\int{F(x)\mathrm{d}x}$

求 $G(x),H(x)$









**Sol**









**开根**

$G^2(x)\equiv F(x)\pmod{x^n}$











**Sol**





**ln**

$G(x)\equiv\ln{F(x)}\pmod{x^n}$

保证 $f_0=1$

求 $G(x)$





**Sol**





**exp**

$G(x)\equiv e^{F(x)}\pmod{x^n}$

保证 $f_0=0$

求 $G(x)$









**Sol**











**三角函数**

$G(x)\equiv\sin{F(x)}$

$H(x)\equiv\cos{F(x)}$

求 $G(x),H(x)$













Hint:

$$
\sin{x}=\frac{e^{ix}-e^{-ix}}{2i}
$$

$$
\cos{x}=\frac{e^ix+e^{-ix}}{2}
$$










**Sol**











# FFT

### 前置内容

**多项式插值**

$n+1$ 个横坐标互不相同的点可以唯一确定一个 $n$ 次多项式。







证明：









**复数运算**

复数是形如 $a+bi$ 的数，其中 $i^2=-1$，$a,b\in\mathbb{R}$。

运算规则为：

* $(a+bi)+(c+di)=(a+c)+(b+d)i$

* $(a+bi)(c+di)=(ac-bd)+(ad+bc)i$

* $\frac{a+bi}{c+di}=\frac{(ac+bd)+(bc-ad)i}{c^2+d^2}$

因此如果我们将复数 $a+bi$ 看成向量 $(a,b)$，我们可以观察出其运算的几何意义：

* 加法：向量加法
* 乘法：模长相乘，辐角相加







**单位根**

P.S. 以下为了方便书写，均将 $\omega$ 简写为 $w$，且将 $\omega_n^i$ 表示为 $w_i$。





代数基本定理：任何复系数一元 $n$ 次多项式方程在复数域上至少有一根。

推论：任何复系数一元 $n$ 次多项式方程在复数域上恰好有 $n$ 个根。





其中 $x^n-1=0$ 的 $n$ 个根分别记为 $w_0,w_1\dots w_{n-1}$，统称为 $n$ 次单位根。

根据其几何意义，我们可以得知 $w_i=\cos{\frac{2i\pi}n}+i\sin{\frac{2i\pi}n}$。



如果我们按照这个等式拓宽 $w_i$ 中 $i$ 的范围的话，结合其几何意义，我们可以得到 $w_i$ 一些~~有趣的~~性质：

* $w_{i+n}=w_i$
* $w_iw_j=w_{i+j}$
* $w_{i}^j=w_{ij}$
* $-w_i=w_{-i}$
* $w_{ki}$=$w'_{i}$，其中 $w_i$ 是 $kn$ 次单位根，$w'_i$ 是 $n$ 次单位根。



### FFT



**算法思路**

根据多项式插值中提到的原理我们可以联想到这样一个解决多项式相乘的算法：

将 $F(x)$ 和 $G(x)$ 进行多点求值，得到 $(x_1,F(x_1)),(x_2,F(x_2))\dots(x_n,F(x_n))$ 和 $(x_1,G(x_1)),(x_2,G(x_2))\dots(x_n,G(x_n))$ 这两系列点。



我们可以知道的是：$H(x)=F(x)G(x)$，所以就有 $\forall_{i}H(x_i)=F(x_i)G(x_i)$。



所以我们直接将两系列点对应相乘，得到的一系列点就是 $H(x)$ 上的点。利用这些点进行插值即可得到 $H(x)$ 的表达式。



**问题1**

如何适当的选取 $x_1,x_2\dots x_n$，使得多点求值能够快速进行？





**Sol**

我们可以取 $x_i=w_i$（$w_i$ 是 $n$ 次单位根）

定义操作 $\mathrm{DFT}:\{f_i\}\rightarrow\{F(w_i)\}$，即输入一个 $n-1$ 次多项式的系数列，得到其在 $n$ 次单位根处的点值列。



当我们想求 $\mathrm{DFT}(F)$ 时，也就是要求 $F(w_k)=\sum\limits_{i=0}^{n-1}{f_iw_k^i}$。

如果 $n$ 为偶数，我们按照 $i$ 的奇偶进行分组，就有：

 $\begin{align}F(w_k)&=\sum\limits_{i=0}^{\frac n2-1}{f_{2i}w_k^{2i}}+\sum\limits_{i=0}^{\frac n2-1}{f_{2i+1}w_k^{2i+1}}\\ &=\sum\limits_{i=0}^{\frac n2-1}{f_{2i}w_{2k}^i}+w_k\sum\limits_{i=0}^{\frac n2-1}{f_{2i+1}w_{2k}^{i}}\\ &=\mathrm{DFT}(\{f_0,f_2\dots f_{n-2}\})_k+w_k\mathrm{DFT}(\{f_1,f_3\dots f_{n-1}\})_k\end{align}$

于是可以分别递归计算偶次项和奇次项系数的 $\mathrm{DFT}$，然后再 $O(n)$ 得出原函数的 $\mathrm{DFT}$。

容易发现复杂度满足 $T(n)=2T(\frac n2)+O(n)$，根据主定理可知复杂度为 $O(n\log{n})$。



于是我们在 $O(n\log n)$ 的时间复杂度内求得了 $\mathrm{DFT}(F)$。



**问题2**

仅仅这样当然是不够的，我们还需要在优秀的时间复杂度内插值出多项式 $H(x)$。







**Sol**

我们定义 $\mathrm{IDFT}:\{H(x_i)\}\rightarrow\{h_i\}$，操作与 $\mathrm{DFT}$ 类似。

注意到一个重要的式子 $\sum\limits_{i=0}^{n-1}{w_i^k}=n[n\mid k]$。



证明：



因此我们可以证明这样一个优美的式子：

$nh_k=\sum\limits_{i=0}^{n-1}{H(x_i)w_{-k}^{i}}$





证明：



有了这个式子之后，我们惊奇的发现 $\mathrm{IDFT}$ 的操作几乎和 $\mathrm{DFT}$ 一样，因此同样可以做到 $O(n\log n)$ 的复杂度。



至此，我们成功在 $O(n\log n)$ 的时间复杂度内解决了多项式乘法问题。



**问题3**

如何代码实现？





**Sol**

按照上述流程直接去写的话，就是最经典的写法：（摘自 oi-wiki.org）

```cpp
#include <cmath>
#include <complex>

typedef std::complex<double> Comp;  // STL complex

const Comp I(0, 1);  // i
const int MAX_N = 1 << 20;

Comp tmp[MAX_N];

// rev=1,DFT; rev=-1,IDFT
void DFT(Comp* f, int n, int rev) {
  if (n == 1) return;
  for (int i = 0; i < n; ++i) tmp[i] = f[i];
  for (int i = 0; i < n; ++i) {
    if (i & 1)
      f[n / 2 + i / 2] = tmp[i];
    else
      f[i / 2] = tmp[i];
  }
  Comp *g = f, *h = f + n / 2;
  DFT(g, n / 2, rev), DFT(h, n / 2, rev);
  Comp cur(1, 0), step(cos(2 * M_PI / n), sin(2 * M_PI * rev / n));
  for (int k = 0; k < n / 2;
    tmp[k] = g[k] + cur * h[k];
    tmp[k + n / 2] = g[k] - cur * h[k];
    cur *= step;
  }
  for (int i = 0; i < n; ++i) f[i] = tmp[i];
}
```

当然，我们可以进一步压缩常数。

事实上递归中从上往下的过程相当于按照二进制从高位到低位，把 1 放左边，0 放右边，例如原先在 100101 的数字最后被放到了 101001 处。

因此我们可以非递归地完成这一步操作，然后再非递归地往上合并，可以缩减递归所需的花销。

在注意到交换位置的过程实际上可以通过一定的预处理做到 $O(n)$，可以进一步提升效率。

因此我们可以得到这样一份代码：（同样摘自 oi-wiki.org）

```cpp
void change(Complex y[], int len) {
  for (int i = 0; i < len; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1) {
      rev[i] |= len >> 1;
    }
  }
  for (int i = 0; i < len; ++i) {
    if (i < rev[i]) {
      swap(y[i], y[rev[i]]);
    }
  }
  return;
}

void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {
    Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;
        y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if (on == -1) {
    for (int i = 0; i < len; i++) {
      y[i].x /= len;
    }
  }
}
```

这样写的话相对来说便于理解和记忆且常数较小，是适合实战的写法。





### NTT

P.S.此处关于单位根的上下标仍同 FFT 时的解释一样。



我们已经知道了，复数域内有这样性质良好的数 $w_i$ 可以用于加速 $\mathrm{DFT}$ 和 $\mathrm{IDFT}$，那么模一个质数 $p$ 的有限域下是否存在同样具有这样良好性质的数呢？



答案是有的，设 $g$ 表示 $p$ 的一个原根，则令 $w_i=g^{i\frac{\varphi(p)}n}$ 就具有同复数域中单位根一样的性质。

即：

* $w_{i+n}=w_i$
* $w_iw_j=w_{i+j}$
* $w_{i}^j=w_{ij}$
* $-w_i=w_{-i}$
* $w_{ki}$=$w'_{i}$，其中 $w_i$ 是 $kn$ 次单位根，$w'_i$ 是 $n$ 次单位根。



但是这不代表我们可以直接将他套用进 FFT 中。因为这里必须要求 $n\mid \varphi(p)$，所以这对 $n$ 产生了很大的限制。

幸运的是我们发现质数 $998244353$ 的欧拉函数值 $998244352=119\times2^{23}$，因此当 $n\leq 2^{23}$ 时，都能够很好的进行这个算法，这也是 $998244353$ 成为常用模数的原因。（尽管有些时候题目与多项式无关）





**代码（依然是摘自 oi-wiki.org）**

```cpp
void ntt(int *x, int lim, int opt) {
  int i, j, k, m, gn, g, tmp;
  for (i = 0; i < lim; ++i)
    if (r[i] < i) swap(x[i], x[r[i]]);
  for (m = 2; m <= lim; m <<= 1) {
    k = m >> 1;
    gn = qpow(3, (P - 1) / m);
    for (i = 0; i < lim; i += m) {
      g = 1;
      for (j = 0; j < k; ++j, g = 1ll * g * gn % P) {
        tmp = 1ll * x[i + j + k] * g % P;
        x[i + j + k] = (x[i + j] - tmp + P) % P;
        x[i + j] = (x[i + j] + tmp) % P;
      }
    }
  }
  if (opt == -1) {
    reverse(x + 1, x + lim);
    int inv = qpow(lim, P - 2);
    for (i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % P;
  }
}
```





# 快速多项式全家桶

### 牛顿迭代

牛顿迭代可以用来求方程的一个近似解。

具体原理就是用切线来拟合曲线求零点。

举个例子，对于一个二次函数：$f(x)=x^2-10$，我们首先猜测一个零点 $x_0$，求出 $(x_0,f(x_0))$ 处的切线。

比如我们取 $x_0=3$，由于 $f'(x)=2x$，我们可以很轻松的写出 $(3,-1)$ 处切线方程 $y=6x-19$，得到一个新的近似零点 $x_1=\frac {19}6$。

再带一次：$(\frac{19}6,\frac1{36})$ 处的切线方程 $y=\frac{19}3x-\frac{721}{36}$，得到新的近似零点 $x_2=\frac{721}{228}\approx3.16228$，$3.16228^2=10.0000147984$，已经相当接近 $10$ 了，可见其逼近速度之快。



当我们把 $x$ 换成一个函数，我们发现牛顿迭代又可以用于求解函数。

假如一个函数 $F(x)$ 满足一个关系 $G(F(x))=0$，

那么如果我们先预估一个函数 $F_0(x)$，就能得到 $F_1(x)=F_0(x)-\frac{G(F_0(x)))}{G'(F_0(x))}$ ，并不断继续重复以提高精度。



接下来详细证明证明其正确性。

最开始要已经知道了 $[x^0]F(x)$，记为 $F_0(x)$。

现在假如已知了 $F_k(x)\equiv F(x)\pmod{n}$

我们把 $G(F(x))$ 在 $F_k(x)$ 处泰勒展开，由于 $G(F(x))=0$，所以：

$\sum\limits_{i=0}^{+\infin}{\frac{G^{(i)}(F_k(x))}{i!}(F(x)-F_k(x))^i}=0$

如果我们把上式 $\bmod x^{2n}$，注意到 $(F(x)-F_k(x))^i$ 只在 $i\leq1$ 时有低于 $2n$ 次的项，所以有：

$\sum\limits_{i=0}^1{\frac{G^{(i)}(F_k(x))}{i!}(F(x)-F_k(x))^i}\equiv0\pmod{x^{2n}}$

展开之后也就是 $G(F_k(x))+G'(F_k(x))(F(x)-F_k(x))\equiv0\pmod{x^{2n}}$。

整理一下就有：$F(x)\equiv F_k(x)-\frac{G(F_k(x))}{G'(F_k(x))}\pmod{x^{2n}}$。

我们令 $F_{k+1}(x)\equiv F(x)\pmod{x^{2n}}$，就可以倍增起来了。





**加法**

$H(x)=F(x)+G(x)$

求 $H(x)$。



**Sol**

略



**乘法**

$H(x)\equiv F(x)G(x)\pmod{x^n}$

求 $H(x)$。



**Sol**

略





**求逆**

$F(x)G(x)\equiv1\pmod{x^n}$

求 $G(x)$。









**Sol**



**取模**

$F(x)=Q(x)G(x)+R(x)$

求 $Q(x),R(x)$







**Sol**



**求导&积分**

$G(x)=F'(x)$

$H(x)=\int{F(x)\mathrm{d}x}$

求 $G(x),H(x)$









**Sol**

略







**开根**

$G^2(x)\equiv F(x)\pmod{x^n}$











**Sol**





**ln**

$G(x)\equiv\ln{F(x)}\pmod{x^n}$

保证 $f_0=1$

求 $G(x)$





**Sol**





**exp**

$G(x)\equiv e^{F(x)}\pmod{x^n}$

保证 $f_0=0$

求 $G(x)$









**Sol**



**三角函数**

$G(x)\equiv\sin{F(x)}$

$H(x)\equiv\cos{F(x)}$

求 $G(x),H(x)$











Hint:

$\sin{x}=\frac{e^{ix}-e^{-ix}}{2i}$

$\cos{x}=\frac{e^ix+e^{-ix}}{2}$









**Sol**

略





**唯一一道练习题 ~ P4723 【模板】常系数齐次线性递推**



求一个满足 $k$ 阶齐次线性递推数列 ${a_i}$ 的第 $n$ 项，即：

$$a_n=\sum\limits_{i=1}^{k}f_i \times a_{n-i}$$

$N = 10^{9} , K = 32000 $

保证读入的数字均为 $[-10^9,10^9]$ 内的整数。





**Sol**

qwq