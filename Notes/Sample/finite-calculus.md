---
layout: cover
---

# 正文2（有限微积分基础

> 有限微积分很多和经典微积分相似，所以大部分情况都是在类比（从连续到离散化？从实数到整数？（雾

---

<v-clicks>

类比极限，$D f(x) = \frac {d f(x)}{dx} = \lim\limits_{h \to 0} \frac {f(x + h) - f(x)}{h}$，在有限微积分中的极限是 $1$，那么可以定义差分算子：$\Delta f(x) = f(x + 1) - f(x)$

差分算子满足：$\Delta^k f(x) = \Delta^{k - 1} f(x + 1) - \Delta^{k - 1} f(x)$

如果我们定义平移算子 $E$，其中 $Ef(x) = f(x + 1)$，那么差分算子 $\Delta$ 也就是 $E - 1$。

众所周知，在经典微积分中存在着 $D(x^m) = m x^{m - 1}$，而此处有$\Delta (x^{\underline{m}}) = m x^{\underline{m - 1}}$。

其中 $x^{\underline{m}}$ 是下降幂，$x(x - 1)(x - 2)\ldots(x - m + 1)$ 一共 $n$ 个因子。

当 $m < 0$ 时，便是 $\frac {1}{(x + 1)(x + 2)\ldots (x + m)}$。

类似的可以定义上升幂。

</v-clicks>

---

**注**：

在有限微积分中：

$$
\sum\nolimits_a^b f(x) \delta x = \sum_{k = a}^{b - 1} f(k)
$$

还有：

$$
\sum \Delta f(x) \delta x = f(b) - f(a) = \left. f(x) \right|_a^b
$$

---

则利用该法则，可以得到：

$$
\sum_{i =  0}^{n - 1} i = \sum\nolimits_0^n x \delta x = \sum\nolimits_0^n \Delta \left(\frac {x^{\underline 2}}{2} \right) \delta x = \frac 1 2 \big((n + 1) \times n - 0 \times (-1) \big) = \frac {n(n + 1)}{2}
$$

$$
\sum_{i = 0}^{n - 1} a^i = \sum\nolimits_0^n a^x \delta x = \sum\nolimits_0^n \Delta \left( \frac {a^x} {a - 1} \right) \delta x = \frac {a^n - 1} {a - 1} (a \ne 0)
$$

例题：

- [求和](https://www.luogu.com.cn/problem/P1625)

$$\sum_{i=1}^n \frac{1}{\prod_{j=i}^{i+m-1}j}=S$$

$n + m \le 500$

---

$$
\displaystyle\sum_{i=1}^n\left(\prod_{j=i}^{i+m-1}j\right)^{-1}=\sum_{i=0}^{n-1}\left(\prod_{j=i+1}^{i+m}j\right)^{-1}=\sum_{i=0}^{n-1}\dfrac{1}{(i+m)^{\underline{m}}} \\\
 ={\sum}_0^nx^{\underline{-m}}\delta x=\dfrac{n^{\underline{-m+1}}-0^{\underline{-m+1}}}{-m+1}=\dfrac{(n+m-1)^{\underline{n}}-n!}{(m-1)(n+m-1)!}
$$

该法则还可以解决：

$$
\sum_x \binom x m, \sum x^k, \cdots
$$

对于 $\sum x^k$ 可以利用斯特林数展开为下降幂，然后就是 $O(k)$ 计算了。

---

- **差分法则**

$$
\begin{aligned}
\Delta (u(x) + v(x)) &= \Delta u(x) + \Delta v(x) \\
\Delta (u(x) v(x)) &= u(x) \Delta v(x) + E v(x) \Delta u(x)
\end{aligned}
$$

<v-click>

- **分部求和法则**

注意到乘法法则：

$$
\Delta (uv) = u \Delta v + Ev \Delta u = v \Delta u + Eu \Delta v
$$

我们重新排布一下两边，并且对于各自求一个和，那么我们就可以得到部分求和法则：

$$
\sum\nolimits_{a}^b u \Delta v = \left. u v \right|_a^b - \sum\nolimits_a^b Ev \Delta u
$$

</v-click>
<v-click>

一个经典的应用是：

$$
\sum\nolimits_{0}^n x^{\underline k} a^x \delta x \quad (a \ne 1)
$$

</v-click>

---

<v-clicks>

注意到 $x^{\underline k}$ 易于差分，而 $a^x$ 是 $\frac {a^x} {a - 1}$ 的差分，于是套用上式：

$$
\begin{aligned}
\sum\nolimits_{0}^n x^{\underline k} a^x \delta x &= \left. x^{\underline k} \frac {a^x} {a - 1} \right|_0^n - \sum\nolimits_{0}^n \frac {a^{x + 1}} {a - 1} k x^{\underline {k - 1}} \\
&= n^{\underline k } \frac {a^{n}} {a - 1} - \frac {ka} {a - 1} \sum\nolimits_{0}^n x^{\underline {k - 1}} a^x \\
&= \dfrac{a^x}{a-1}\sum_{i=0}^k{\left(\dfrac{-a}{a-1}\right)}^ik^{\underline{i}}x^{\underline{k-i}}
\end{aligned}
$$

于是就可以愉快的 $O(k)$ 地递推了或者直接计算了。

分部求和就喜欢干这种一个易于差分，另一个是一个简单差分，并且两个函数有一定关联的式子。

</v-clicks>

---

例：[数列求和](https://www.luogu.com.cn/problem/P4948)

给定 $n\le10^{18}$，$a\le10^9$，$k\le2000$，求：

$$\sum_{i=1}^n i^k a^i \pmod {10^9 + 7}$$

<v-click>

将 $x^k$ 转化为 $\sum {k \brace i} x^{\underline i}$，即可转化为前面的问题。

瓶颈在与求出第二类斯特林数，可以 $O(k^2)$ 递推，也可以用 NTT 变成 $O(k \log k)$ 之类的东西。

但是 [P5907 数列求和加强版](https://www.luogu.com.cn/problem/P5907) 呢？$k \le 10^7$，显然不可做了！

这个留作思考（~~其实是我懒得打公式了~~

</v-click>

---

> 除了利用第二类斯特林数转化为经典应用的例子，还有另外一种做法：扰动法。

<v-clicks>

对于一个数列求和：$S_n = \sum_{i = 0}^n f(i)$，一定存在：

$$
f(n) + \sum_{i = 0}^{n - 1} f(i) = f(0) + \sum_{i = 1}^{n} f(i)
$$

那么如果 $S_n - f(0)$ 与 $S_{n - 1}$ 间可以用某个等式简单的变换，那么便可以通过移项的方式求出，例如：

$$
a^{n+1}+\sum\limits_{i=0}^{n}a^i=a^0+a\sum\limits_{i=0}^{n}a^i \implies a^{n+1}+S_n=1+aS_n \implies S_n=\dfrac{1-a^{n+1}}{1-a}
$$

</v-clicks>

---

<v-clicks>

于是这里对原式进行扰动：

$$
\sum_{i=1}^{n-1}i^k a^i +n^k a^n=\sum_{i=1}^{n-1}(i+1)^k a^{i+1}+a
$$

但是由于 $S_n - f(0)$ 与 $S_{n - 1}$ 间关联不大，所以不太能变，考虑直接二项式展开：

$$
\sum_{i=1}^{n-1}i^k a^i +n^k a^n=\sum_{i=1}^{n-1}\sum_{j=0}^k\binom{k}{j}i^j a^{i+1}+a
$$

再稍微变下求和顺序，我们的目的是构造递推式，所以顺便把 $k$ 的项单独提出来：

$$
\sum_{i=1}^{n-1}i^k a^i +n^k a^n=\sum_{j=0}^{k - 1}\binom{k}{j}\sum_{i=1}^{n-1}i^j a^{i + 1} + \sum_{i = 1}^{n - 1} i^k a^{i + 1} + a
$$

</v-clicks>

---

<v-clicks>

稍微合并一下：

$$
a\sum_{j=0}^{k-1}\binom{k}{j}\sum_{i=1}^{n-1}i^j a^i + (a-1)\sum_{i=1}^{n-1}i^k a^i=n^ka^n-a
$$

令 $S_k = \sum_{i=1}^{n-1}i^k a^i$ 那么有：

$$
a\sum_{j=0}^{k-1} S_j + (a - 1) S_k = n^k a^n - a
$$

也就是说：

$$
S_k =\dfrac{-a\sum_{j=0}^{k-1}\binom{k}{j} S_j +n^ka^n-a}{a-1}
$$

$S_0$ 容易求，那么 $O(k^2)$ 递推后，答案为 $S_k + n^k a^n$

$a = 1$ 时也可以类似做，留作练习。

</v-clicks>

---

然后该题的解法还有一堆堆，例如插值，例如 EI 的 Binomial Sums 科技……

这个留作思考（梅开二度

---

回到 $\Delta = E - 1$，那么有

$$
\Delta^n = (E - 1)^n = \sum_k \binom{n}{k}E^k (-1)^{n - k}
$$

类似的利用 $E = \Delta + 1$，那么有

$$
E^n = (\Delta + 1)^n = \sum_k \binom{n}{k} \Delta^k
$$

此时我们发现这东西其实就是二项式反演的形式，如果我们将 $E$ 看为至多，$\Delta$ 看为恰好。

那么由此观察出二项式反演是原序列和差分序列之间的一种反演关系。

<!-- （） -->

---

现在知道了：

$$
E^n = (\Delta + 1)^n = \sum_k \binom{n}{k} \Delta^k
$$

意味着只要我们知道了 $\Delta^k$，我们就可以求出整个函数的值。这其实就是牛顿级数，与麦克劳林级数十分相似。

$$
f(x) = E^x f(0) = \sum_k \binom nk \Delta^k f(0) =  \sum_k c_k \binom x k
$$

然而对于一个多项式来说，其次数为 $n$，那么存在 $\Delta^{n + 1} = 0$，这可以通过二项式定理和归纳来证明。

> 此后我们简记为 $\Delta^k f(0) = c_k$。

> 这是否很像多项式平移的玩意？所以可以用它来做吗？理论可行！但是限制很大！

---

<v-clicks>

接下来回顾一个小小的公式：

$$
\binom{n}{k} = \binom{n - 1}{k} + \binom{n - 1}{k - 1}
$$

也就是说，我们令 $f(x) = \binom{x}{k}$，那么存在 $\Delta f(x) = \binom{x + 1}{k} - \binom{x}{k} = \binom{x}{k - 1}$，也就是说说 $\Delta^z f(x) = \binom{x}{k - z}$。

如果我们将一个函数表示成牛顿级数，由于存在 $\Delta(f + g) = \Delta f + \Delta g$ 的性质：

$$
\Delta^z f(x) = \Delta^z (\sum c_k \binom{x}{k}) = \sum c_k \binom{x}{k - z}
$$

令多项式 $f(x)$ 的阶为 $d$，如果观察 $\Delta^z f(0)$ 可知：

$$
\Delta^z f(0) = \begin{cases}
    c_z & z \le d \\
    0 & z \ge d
\end{cases}
$$

于是我们知道差分即可快速还原出这个多项式！

</v-clicks>

---

现在我们知道了牛顿级数，是否意味着我们可以拓展二项式定理了？

<v-clicks>

对于整数下，我们有：

$$
(x + y)^n = \sum_{k = 0}^n \binom{n}{k} x^k y^{n - k}
$$

由于存在 $k \gt n, k \lt 0 \to \binom{n}{k} = 0$，所以上式我们删除对 $k$ 的限制：

$$
(x + y)^\alpha = \sum_{k} \binom{\alpha}{k} x^k y^{\alpha - k}
$$

其中 $\alpha \in {\mathbb Z}$，上式是一个无穷牛顿级数，其就是扩展到实数的牛顿二项式定理。

但是注意实际上广义牛顿二项式定理并非总是成立, 因为等式右边不一定收敛……

</v-clicks>

---

<v-clicks>

或许我们可以通过另一种新的方式来理解。看到，对于一个无穷的牛顿级数来说：$\Delta^z f(0) = c_z$，也就是说：

$$
f(x) = \sum_k \Delta^k f(0) \binom{x}{k}
$$

由于 $E = 1 + \Delta, E^x = \sum_k \binom{x}{k} \Delta^k$，所以有：

$$
E^x g(a) = g(a + x)
$$

意味着：

$$
g(a + x) = \sum_k \binom{x}{k} \Delta^k g(a) = \sum_k \frac {\Delta^k g(a)} {k!} x^{\underline{k}}
$$

这与无限微积分中的**泰勒级数**何其相似！

$$
g(a + x) = \sum_k \frac {g^{(k)}(a)}{k!} x^{k}
$$

</v-clicks>

---

回到 $g(x) = (1 + z)^x$，可以知道 $\Delta^k g(x) = x^k (1 + z)^x$

$$
g(x) = \sum_n  \binom{x}{k} \Delta^k g(0) = (1 + z)^0 \sum_k \binom{x}{k} z^k = \sum_k \binom{x}{k} z^k
$$

也就是说，只要 $|z| < 1$，意味着右式是收敛的，那么它总是成立的！

这就是广义二项式定理另一种理解方式。