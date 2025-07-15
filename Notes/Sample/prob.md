---
layout: cover
---

# 数学（正文 1：概率论

---
layout: quote  
---

叠甲：这部分可能与 OI 直接关联不大，讲讲干货，拓展一下知识面

~~主要是我想学学~~

---
layout: cover
---

## 概率论公理

---

- 样本空间 $\Omega$：一个试验所有可能的结果构成的集合。
- 事件 $E$：样本空间的任一子集，或者说由试验的某些可能结果构成的一个集合（可以只有一个元素，也可以有多个元素），如果试验的结果包含在 $E$ 中，则称事件发生了。
- $E \cup F$：事件的并
- $E \cap F$ 与 $EF$ 表述等价，表示事件的交。
- $E^c$ 表示事件的补，即 $\Omega - E$

> 事件的交并分别满足交换律和结合律，在交和并的转化间满足德摩根律：
> $$
> \left(\bigcup E_i \right)^c = \bigcap E_i^c
> $$

---

定义一个事件的发生概率可以利用事件发生的相对频率：

$$
P(E) = \lim_{n \to \infty} \frac {n(E)} n
$$

但是这需要基于 $\frac {n(E)} n$ 趋于一个常数的假设，或者说一个公理。

也可以利用古典概型定义概率：

$$
P(E) = \frac {n(E)}{|\Omega|}
$$

也就是认为样本空间（一个可重集）中的每一个结果发生的概率相等，则事件发生的概率即该事件在样本空间中的数量除以样本空间的大小。

---

概率的三条公理：

$$
0 \le P(E) \le 1
$$

$$
P(\Omega) = 1
$$

对任一系列互不相容的事件 $\{E_i\}$（$i \ne j \implies E_i E_j = \emptyset$）

$$
P \left( \bigcup E_i \right) = \sum P(E_i)
$$

---

由这三个公理，我么可以得到若干命题：

$$
\begin{aligned}
1 = P(S) &= P(E \cup E^c) = P(E) + P(E^c) \\
E \subset F &\implies P(E) \le P(F) \\
P(E \cup F) &= P(E) + P(F) - P(EF) \implies \\
P(E_1 \cup E_2 \cup \ldots \cup E_n) &= \sum_{r = 1}^n (-1)^{r + 1} \sum_{i_1 < i_2 < \cdots < i_r} P(E_{i_1} E_{i_2} \ldots E_{i_r})
\end{aligned}
$$

其中第三个命题便是最原始的容斥原理。 

值得注意的是，容斥恒等式中，如果取第一项，那么得到事件并的一个概率上界，取钱两项，是一个下界，一次类推，会得到不断缩小的上下界，知道完全精确为止。 

于是有了：

$$
P \left( \bigcup E_i \right) \le \sum P(E_i)
$$

该不等式称为布尔不等式。

---

- 连续集函数

事件序列 $\{E_n, n \ge 1\}$ 如果满足：

$$
E_1 \subset E_2 \subset \cdots \subset E_n \subset \cdots
$$

则称为递增序列，反之，则还有递减序列。

对于递增序列，定义一个新的事件：

$$
\lim_{n \to \infty} E_n = \bigcup_{i = 1}^\infty E_i
$$

类似的，对于递减序列：

$$
\lim_{n \to \infty} E_n = \bigcap_{i = 1}^\infty E_i
$$

---

对于递增或递减序列：

$$
\lim_{n \to \infty} P(E_n) = P(\lim_{n \to \infty} E_n)
$$

证明比较容易，利用三个公理和该序列的性质即可。

---

- 概率与悖论：

假设有一个无限大的坛子和无限个编了号的球，现在是 0 点 0 分 0 秒，进行如下操作：

在差 1 秒到 0 点 0 分 0 秒时，将 $1 \sim 10$ 号球放进去，并把 $10$ 号球拿出来。

在差 1/2 秒到 0 点 0 分 0 秒时，将 $11 \sim 20$ 号球放进去，并把 $20$ 号球拿出来。

在差 1/4 秒到 0 点 0 分 0 秒时，将 $21 \sim 30$ 号球放进去，并把 $30$ 号球拿出来。

……

那么最终坛子中剩余多少个球？

<v-click>

显然是无限个。

</v-click>

---

假设有一个无限大的坛子和无限个编了号的球，现在是 0 点 0 分 0 秒，进行如下操作：

在差 1 秒到 0 点 0 分 0 秒时，将 $1 \sim 10$ 号球放进去，并把 $1$ 号球拿出来。

在差 1/2 秒到 0 点 0 分 0 秒时，将 $11 \sim 20$ 号球放进去，并把 $2$ 号球拿出来。

在差 1/4 秒到 0 点 0 分 0 秒时，将 $21 \sim 30$ 号球放进去，并把 $3$ 号球拿出来。

……

那么最终坛子中剩余多少个球？

<v-click>

为什么就变成了 $0$ 个呢？

因为 $i$ 号球总会在差 $\frac 1 {2^i}$ 秒时被取出来。

</v-click>

---

现在变成随机取出一个球，那么结果是 $0$ 还是无限？

<v-clicks>

坛子还是为空，接下来我们从概率论的角度去理解：

先考虑 $1$ 号球，令 $P(E_n)$ 表示 $n$ 轮后其仍在坛子中的概率，那么：


$$
P(E_n) = \frac {9 \times 18 \times 27 \times \cdots \times 9n}{10 \times 19 \times 28 \times \cdots \times (9n + 1)}
$$

$E_n$ 显然是一个递减事件序列，则由：

$$
\bigcup_{i = 1}^\infty E_i = \lim_{n \to \infty} P(E_n) = P(\lim_{n \to \infty} E_n) = 0
$$

(极限的证明略)

则 $1$ 球被留下的概率为 $0$。

同理可推得其他球留下的概率也为 $0$。

于是坛子为空的概率为 $1$，得证。

</v-clicks>

---

游程问题，咕……

---

## 概率论问题

---

- **贝叶斯公式**：

$$
P(E) = P(EF) + P(EF^c) = P(E | F) P(F) + P(E | F^c) P(F^c)
$$

也可以扩展到一系列互不相容的 $F_i$ 且满足 $E \subset \bigcup F_i$，那么 $P(E) = \sum P(E | F_i) P(F_i)$

例：

一项血液化验有95%的把握诊断某种疾病，但是这项化验用于健康人也会有1%的伪阳性结果。如果该疾病的患者事实上仅占总人口的0.5%，若某人化验结果为阳性，则此人确实患该疾病的概率是多少？

<v-clicks>

利用贝叶斯公式，我们可以求得：

$$
P = \frac {0.95 \times 0.005} {0.95 \times 0.005 + 0.01 \times 0.995} \approx 0.323
$$

哇哦，这看上去正确率好低呀，所以医生的话到底能不能信呢？

</v-clicks>


---

- **点数问题**

假设在独立重复试验中，每次成功的概率为 $p$ ,失败的概率为 $1 - p$, 在 $m$ 次失败之前，已有 $n$ 次成功的概率是多大？

<v-clicks>

尽管我们可以直接DP,但是费马给出了这样子的论断:

要使得 $n$ 次成功出现在 $m$ 次失败之前，那么在前 $m + n - 1$ 次试验中，至少有 $n$ 次成功。即使在 $m + n - 1$ 次试验之前，试验已经结束了。

> 费马说：我有一个绝妙的证明，但这里空白处太少，我写不下

因此 $P_{n, m} = \sum_{k = n}^{m + n - 1} \binom {m + n - 1} k p^k (1 - p)^{m + n - 1 - k}$

所以当两个人在游戏时，确定一个人赢得一场比赛的概率，假设比赛在胜负结束后依然继续，会更为容易。

</v-clicks>

---

- **赌徒破产问题**：

两个赌徒就连续抛掷一枚硬币的结果进行打赌。如果正面向上，B将给A一元。如果反面向上，A将给B一元，一直如此下去，直到某一方钱输光。假设连续抛掷硬币是独立的，且每次的结果正面朝上的概率为 p，假定开始时 A 有 i 元， B 有 N 减 i 元。那么最后 A 能赢得所有钱的概率是多少？

<v-clicks>

令 $q = 1 - p$，$P_i$ 表示开始时 A 有 i 元，B 有 N - i 元，而 A 赢得所有钱的概率，开始递推：

$$
P_i = \begin{cases}
\frac {1 - (\frac q p)^i} {1 - \frac q p} P_1, \frac q p \ne 1 \\
i P_1, \frac q p = 1
\end{cases}
$$

再利用 $P_N = 1$ 的事实，则：

$$
P_i = \begin{cases}
\frac {1 - (\frac q p)} {1 - (\frac q p)^N}, \frac q p \ne 1 \\
\frac i N, \frac q p = 1
\end{cases}
$$

</v-clicks>

---

该问题还有一种特殊的情形，称为赌博持续时间问题。

利用期望的线性形进行递推：

$$
E_i = p (E_{i - 1} + 1) + q (E_{i + 1} + 1)
$$

稀疏矩阵消元即可。

---

练习题：

- 已知有一个球放在 N 个盒子中的一个内，已知球在第 $i$ 个盒子的概率是 $p_i$ 。如果球在第 $i$ 个盒子里搜寻该盒子会以 $a_i$ 的概率发现它。求解搜索第 $i$ 个盒子没有发现球的条件下，球在第 $j$ 个盒子的条件概率。

<v-click>

$$
\begin{cases}
\frac {p_j} {1 - a_i p_j}, j \ne i \\
\frac {(1 - a_i) p_i} {1 - a_i p_i}, j = i
\end{cases}
$$

</v-click>

---

- $n$ 个选手单循环赛，每对选手只比赛一次，比赛结果是相互独立的，任何一场比赛的结果都分出输赢（等概率）。对于一个给定的整数 $k$，是否可能存在一种比赛的结果，对于任意 $k$ 个选手的集合都有一位选手打败了该集合内的选手？证明：当 $\binom nk \left[1 - (\frac 12)^k \right]^{n - k} \lt 1$ 时这种结果总是存在的。

<v-clicks>

给 $k$ 个选手的所有 $\binom nk$ 个组合标号，令 $B_i$ 表示在第 $i$ 个组合里，没有人打败所有 $k$ 个选手的概率：

$$
B_i = \left[1 - (\frac 12)^k \right]^{n - k}
$$

所以

$$
P\left(\bigcup B_i\right) \le \sum P(B_i) = \binom nk \left[1 - (\frac 12)^k \right]^{n - k} \lt 1
$$

所以存在。

</v-clicks>

---

## 随机变量

---

设想有 $r$ 种不同的优惠券，某人每次收集一张，且每种优惠券都以相同的可能性被收集到，并假设各自收集是相互独立的。假设某人想收集全一套 $r$ 种优惠券，那么他所收集到的优惠券的总张数是一个随机变量，记为 $T$。

我们如何计算 $P(T = n)$?

<v-clicks>

与其直接计算，我们不如先考虑 $T$ 大于 $n$ 的概率。

为此，先固定 $n$ 并且分别定义事件 $A_1, A_2, \ldots, A_r$。其中 $A_i$ 表示前 $n$ 张优惠券里没有第 $i$ 种优惠券。于是：

$$
P(T > n) = P\left(\bigcup A_i\right)
$$

注意到：

$$
\begin{aligned}
P(A_i) = \left(\frac {r - 1} r \right)^n \\
P(A_{i_1}A_{i_2} \cdots A_{i_k}) = P\left(\frac {r - k} r \right)^n
\end{aligned}
$$

于是，我们自然就可以得到 $P(T = n)$

</v-clicks>

---

如果考虑随机变量是前 $n$ 张优惠券里，优惠券的不同种类数 $D_n$，可以有：

$$
P(D_n = k) = \binom rk \left(\frac k r \right)^n \left[1 - \sum_{i = 1}^{k - 1} \binom ki \left( \frac {k - i} k \right)^n (-1)^{i + 1} \right]
$$

利用布尔不等式以及 $e^{-x} \ge 1 - x$ 的放缩，可以推导 $P(T > n)$ 的上界：

$$
P(T > n) = P\left(\bigcup A_i \right) \le \sum P(A_i) = r(1 - \frac 1 r)^n \le re^{- \frac nr}
$$

这里自然可以引入随机变量 $X$ 的累计分布函数 $F(x) = P(X \le x)$

---

对于离散变量：

$$
E(X) = \sum k P(X = k)
$$

对于连续变量，设 $f(x) = \frac {dF(x)}{dx}$ 表示概率密度函数：

$$
E(X) = \int_{-\infty}^{+\infty} x dF(x) = \int_{-\infty}^{+\infty} x f(x) dx
$$

- **二项随机变量**

问，对于一个参数为 $(n, p)$ 的二项随机变量 $X$（满足 $P(X = k) = \binom nk p^k (1 - p)^{n - k}$，求：

$$
E[X^k]
$$

---

直接暴力展开：

$$
\begin{aligned}
E[X^k] &= \sum_{i = 1}^n i^k \binom ni p^i (1 - p)^{n - i} \\
&= np \sum_{i = 1}^n i^{k - 1} \binom {n - 1} {i - 1} p^{i - 1} (1 - p)^{n - i} \\
&= np \sum_{i = 0}^{n - 1} (i - 1)^{k - 1} \binom {n - 1} i p^i (1 - p)^{n - 1 - i} \\
&= np E[(Y + 1)^{k  - 1}]
\end{aligned}
$$

其中 $Y$ 是一个参数为 $(n - 1, p)$ 的二项随机变量。

于是令 $k = 1$，得到 $E[X] = np$，令 $k = 2$ 有：

$$
E[X^2] = np E[Y + 1] = np[(n - 1)p + 1]
$$

则方差 $Var(X) = E[X^2] - (E[X])^2 = np(1 - p)$

---

那么二项随机变量的概率分布函数怎么求？

$$
P(X \le i) = \sum_{k = 0}^i \binom nk p^k (1 - p)^{n - k}
$$

那么可以有递推式：

$$
P(X = k + 1) = \frac p {1 - p} \frac {n - k} {k + 1} P(X = k)
$$

自行证明即可。

---

- **泊松随机变量**

$$
p(i) = P(X = i) = e^{-\lambda} \frac {\lambda^i} {i!} (X = 0, 1, 2, \ldots)
$$

该分布列满足 $\sum_{i = 0}^\infty p(i) = e^{-\lambda} \sum_{i = 0}^\infty \frac {\lambda^i} {i!} = e^{-\lambda} e^\lambda = 1$

当 $n$ 足够大而 $p$ 充分小，使得 $np$ 保持适当大小时，可以用于拟合二项随机变量。

其期望：

$$
E[X] = \sum_{i = 0}^\infty \frac {i e^{-\lambda} \lambda^i} {i!} = \lambda e^{-\lambda} \sum_{i = 0}^{\infty} \frac {\lambda^i} {i !} = \lambda
$$

而方差：

$$
Var(X) = \lambda
$$

留作自行证明。

---

假设有 $n$ 个人，每个人在一年365天内任意天过生日的概率都相同。现在的问题是计算 $n$ 个人生日各不相同的概率，特别的这里求解该概率小于 $\frac 12$ 的 $n$ 大致范围。

<v-clicks>

我们可以利用柏松分布近似来给出上述概率的近似值设想。

我们进行一系列试验，对于不同的两个人，如果他们的生日相同，就称试验为成功。

如果我们令 $E_{i, j}$ 表示对 $i$ 和 $j$ 的试验成功，那么考虑到虽然这个事件 $E_{i, j}$ 间并不独立，但其相依性却很弱，所以可以利用泊松分布近似。

（可以证明对于不同的 $i, j, k, l$ $E_{i, j}$ 与 $E_{k, l}$ 时相互独立的。

那么假设的次数近似的服从参数为 $\lambda = \binom n 2 \times \frac 1 {365}$ 的泊松分布。

于是 $P(没有两个人生日相同) = P(没有试验成功) \approx \exp \left( \frac {-n (n - 1)} {730} \right)$

依据问题，可得 $n = 23$。

</v-clicks>

---

有趣的是，柏松分布可以近似很多问题，但在此处我们不再展开。

---

- **几何随机变量**

$$
P(X = n) = p (1 - p)^{n - 1}, n = 1, 2, 3, \ldots
$$

$$
E(X) = \frac 1 p
$$

$$
Var(X) = \frac {1 - p} {p^2}
$$

---

- **超几何随机变量**

是一个坛子里共有 m 个白球，n 个黑球，从中随机的选出 k 个球，令 $X$ 表示取出来的白球数：

$$
P(X = i) = \frac {\binom m i \binom n {k - i}} {\binom {n + m} k}
$$

$$
E[X^k] = \binom {mk} {n + m}= E \left[(Y + 1)^{k - 1} \right]
$$

其中 $Y$ 为参数时 $(m - 1, n + m - 1, k - 1)$ 的超几何随机变量，那么：

$$
E[X] = k \frac m {m + n}
$$

令 $p = \frac m {m + n}$

$$
Var(X) = np(1 - p) \left(1 - \frac {k - 1} {m + n - 1} \right)
$$

---

还有各种神秘的随机变量和分布,这里便不做过多展开

---

## 期望的性质

- **平面上的随机游走**

设在平面坐标系的原点上，放一质点，在平面上按单位长度向任意方向随机游走，求走了 $n$ 步以后，质点相对原点的距离的平方的期望值。

<v-clicks>

$$
D^2 = (\sum X_i)^2 + (\sum Y_i)^2 = \sum(X_i^2+Y_i^2) + \sum_{i \ne j} (X_i X_j + Y_i Y_j) = n + \sum_{i \ne j} (X_i X_j + Y_i Y_j)
$$

我们利用 $\theta i$ 之间相互独立的假设：

$$
2\pi E[\cos \theta_i] = \int_0^{2\pi} \cos u du = \sin 2\pi - \sin 0 = 0
$$

可得：

$$
E[D^2] = n
$$

</v-clicks>

---

一共有 52 棵树排在一个圆周上，有 15 只金花鼠生活在这些树上。证明存在相连的七棵树，其上生活着至少有三只金花鼠。

<v-clicks>

随机的选一棵树，并记 X 为这棵树的邻域中金花鼠的数目，那么显然：

$$
E[X] = 15 \times \frac 7 {52} = \frac {105} {52} \gt 2
$$

注意到：

$$
P(a \le X \le b) = 1 \implies a \le E[X] \le b
$$

则一定存在。

> 抽屉原理也可以用类似方法去证明

</v-clicks>

---

还记得 $\min - \max$ 容斥吗？我们现在给出一个概率的证明：

首先假设所有的 $x_i$ 在 $[0, 1]$ 内，令 $U$ 为 $(0, 1)$ 的随机变量记事件 $A_i = \{U \lt x_i\}$

$$
P\left(\bigcup A_i \right) = P(U \le \max_i x_i) = \max_i x_i
$$

且 $P(A_iu) = P(U \lt x_i) = x_i$

类似的：

$$
P(A_{i_1} \cdots A_{i_r}) = P(U \lt \min_{j = 1, \ldots, r} x_{i_j}) = \min_{j = 1, \ldots, r} x_{i_j}
$$

由事件和的容斥原理，即可得：

$$
\max_i x_i = \sum_{r = 1}^n (-1)^{r + 1} \min_{i_1 \lt \cdots \lt i_r} x_i
$$

注意到，一个数集总可以通过线性变化映射到我们给定的这个条件内，而同时取期望后，根据期望的线性性，则该扩展自然成立。

---

补充：如果从$[0, 1]$ 区间随机、独立地抽取 $n$ 个数，那么第 $k$ 小的数的期望？

首先考虑第 $1$ 小的。对于每一个数，定义其概率分布函数：

$$
F(x) = P(X < x) = x
$$

那么对于 $n$ 个数，其概率密度函数：

$$
\begin{aligned}
F_n(x) &= P(\min \{x_i\} \lt x) \\
&= 1 - P(\min \{x_i\} \ge x) \\
&= 1 - \prod P(x_i \ge x) \\
&= 1 - (1 - \prod F(x))^n \\
&= 1 - (1 - x)^n
\end{aligned}
$$

---

那么其期望：

$$
\begin{aligned}
E(X) &= \int_0^1 x dF_n(x) \\
&= \int_0^1 x n (1 - x)^{n - 1} \\
&= \left. -x (1 - x)^n \right\vert_0^1 - \int_0^1 - (1 - x)^n \\
&= \left. -\frac 1 {n + 1} (1 - x)^{n + 1} \right\vert_0^1 \\
&= \frac 1 {n + 1}
\end{aligned} 
$$