# 暴力多项式全家桶

P.S. 在本节范围内，所有同余号（多项式运算）均在 $\pmod{x^n}$ 意义下进行；所有等号（代数运算）均在模某个质数 $p$ 意义下进行。



**加法**

$H(x)=F(x)+G(x)$

求 $H(x)$。



























**Sol**

$h_{i} = f_{i}+g_{i}$

$O(n)$

























**乘法**

$H(x)\equiv F(x)G(x)\pmod{x^n}$

求 $H(x)$。



















**Sol**

$h_i=\sum\limits_{j=0}^i{f_jg_{i-j}}$

$O(n^2)$



















**求逆**

$F(x)G(x)\equiv1\pmod{x^n}$

求 $G(x)$。



















**Sol**

注意到 $\sum\limits_{i=0}^n{f_i+g_{n-i}}=[n=0]$

我们将 $i=0$ 的项抽出来：$f_0g_n=[n=0]-\sum\limits_{i=1}^n{f_ig_{n-i}}$

于是就有 $g_n=\frac{[n=0]-\sum\limits_{i=1}^n{f_ig_{n-i}}}{f_0}$，可以进行 $O(n^2)$ 递推。

















**取模**

$F(x)\equiv Q(x)G(x)+R(x)\pmod{x^n}$

求 $Q(x),R(x)$



















**Sol**

直接模拟除法过程就可以了。

$O(n^2)$



















**求导&积分**

$G(x)=F'(x)$

$H(x)=\int{F(x)\mathrm{d}x}$

求 $G(x),H(x)$



















**Sol**

$g_i=(i+1)f_{i+1}$

$h_i=\frac{f_{i-1}}{i}$

$O(n)$

















**开根**

$G^2(x)\equiv F(x)\pmod{x^n}$





















**Sol**

$f_i=\sum\limits_{j=0}^i{g_jg_{i-j}}$

类似求逆时的处理方法：$2g_0g_i=f_i-\sum\limits_{j=1}^{i-1}{g_jg_{i-j}}$

移一下项就有：$g_i=\frac{f_i-\sum\limits_{j=1}^{i-1}{g_jg_{i-j}}}{2g_0}$

注意 $g_0^2=f_0$ 是边界情况：

* 若 $f_0\neq0$，则 $G$ 的解数，取决于 $f_0$ 的平方根数量。

* 若 $f_0=0$，令 $F(x)=x^kH(x)$，满足 $h(0)\neq0$，那么若 $k$ 为奇数，则 $G$ 无解；若 $k$ 为偶数，记 $P^2(x)=H(x)$，那么 $G(x)=x^{\frac k2}P(x)$。

















**ln**

$G(x)\equiv\ln{F(x)}\pmod{x^n}$

保证 $f_0=1$

求 $G(x)$



















**Sol**

对原式左右两边求导：$G'(x)\equiv F'(x)F^{-1}(x)^\pmod{x^n}$

先求出 $H(x)\equiv F^{-1}(x)\pmod{x^n}$

那么有 $(i+1)g_{i+1}=\sum\limits_{j=0}^i{(j+1)f_{j+1}h_{i-j}}$，外加 $g_0=0$ 即可。

$O(n^2)$

















**exp**

$G(x)\equiv e^{F(x)}\pmod{x^n}$

保证 $f_0=0$

求 $G(x)$





















**Sol**

狠狠的求导：$G'(x)=F'(x)e^{F(x)}=F'(x)G(x)$

那么就有 $(i+1)g_{i+1}=\sum\limits_{j=0}^i{(j+1)f_{j+1}g_{i-j}}$

外加 $g_0=1$ 即可。

$O(n^2)$



















**三角函数**

$G(x)\equiv\sin{F(x)}$

$H(x)\equiv\cos{F(x)}$

求 $G(x),H(x)$

Hint:

$\sin{x}=\frac{e^{ix}-e^{-ix}}{2i}$

$\cos{x}=\frac{e^{ix}+e^{-ix}}{2}$

















**Sol**

直接把 $F(x)$ 带进公式，利用 $\exp$ 算法即可。

若 $i$ 在模 $p$ 意义下有对应的数，那么可以直接用这个数来运算。

否则可以扩域，复杂度都是 $O(n^2)$。

















# FFT

### 前置内容

**多项式插值**

$n+1$ 个横坐标互不相同的点可以唯一确定一个 $n$ 次多项式。

















证明：

利用待定系数法可以得到一个 $n+1$ 元一次方程组。

观察系数矩阵，可以发现其一定是满秩的。

因为如果令 $S=\{1,2\dots n\}$，那么不存在 $T\subset S$，$0\leq p<q\leq n$，使得 $\sum\limits_{i\in T}{x_i^p}=\sum\limits_{i\in T}{x_i^q}$。

也就意味着消元时不可能消掉一个变量的同时消掉另一个变量，那当然就有一个唯一解。

















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



$nh_k=\sum\limits_{i=0}^{n-1}{H(x_i)w_{-k}^{i}}$

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

$\begin{align}\sum\limits_{i=0}^{n-1}{w_i^k}&=\sum\limits_{i=0}^{n-1}{w_k^i}\end{align}$

注意到这是等比数列求和的形式，因此我们讨论公比：

* 若 $n\mid k$，有公比 $w_k=1$，所以 $\sum\limits_{i=0}^{n-1}{w_k^i}=n$

* 若 $n\nmid k$，有公比 $w_k\neq1$，所以 $\sum\limits_{i=0}^{n-1}{w_k^i}=\frac{w_0-w_k^n}{1-w_k}=0$

因此 $\sum\limits_{i=0}^{n-1}{w_i^k}=n[n|k]$。



因此我们可以证明这样一个优美的式子：

$nh_k=\sum\limits_{i=0}^{n-1}{H(x_i)w_{-k}^{i}}$





















证明：

$\begin{align}nh_k&=\sum\limits_{i=0}^{n-1}w_{-k}^iH(x_i)\\&=\sum\limits_{i=0}^{n-1}{w_{-k}^i\sum\limits_{j=0}^{n-1}w_{i}^jh_j}\\&=\sum\limits_{i=0}^{n-1}\sum_{j=0}^{n-1}{w_{-k}^iw_{i}^jh_j}\\&=\sum\limits_{j=0}^{n-1}h_j\sum\limits_{i=0}^{n-1}{w_i^{j-k}}\\&=\sum\limits_{j=0}^{n-1}nh_j[n|j-k]\\&=nh_k\end{align}$





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

