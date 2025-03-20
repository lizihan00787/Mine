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


