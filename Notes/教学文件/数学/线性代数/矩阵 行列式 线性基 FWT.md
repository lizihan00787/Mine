    # 线代入门

#### 向量

向量是什么？

从偏计算机的角度看，是一列数；从偏物理的角度看，是一个有方向有长度的箭头。

然而从数学的角度看，还有一个视角，是一个可以相加，可以数乘的代数结构。





我们主要还是从有长度的箭头的角度来看。

虽然起点在哪里都无所谓，但是我们更倾向于把起点放到坐标原点，并且还可以用终点所在的点来表示这个向量。



向量相当重要且基础的两个运算就是 相加 和 数乘。



两个向量求和可以理解为把其中一个向量移到另一个向量末尾，此时前一个向量的起点指向后一个向量的终点所形成的向量，也可以理解为两个向量对应坐标之和构成的向量。

一个向量数乘可以理解为把模长乘一个倍数，也可以理解为对应坐标每个数都乘一个倍数。





#### 线性组合 基 空间

一个向量 $v$ 的坐标表示中的 $(a,b)$，实际上可以理解为 $v=a\hat{i}+b\hat{j}$，其中 $\hat{i}$ 和 $\hat{j}$ 分别是 $x$ 轴和 $y$ 轴方向上的单位向量，这个形式称为 $v$ 可以表示为 $\hat{i}$ 和 $\hat{j}$ 的线性组合。



事实上，平面上所有向量都可以由 $\hat{i}$ 和 $\hat{j}$ 表出，所以我们可以称他俩叫做这个平面的一组基。

注意到，只要两个向量不共线，那么他们就可以作为这个平面的一组基。



一组向量经过线性组合能得到的向量对应的点构成的空间就叫这组向量张成的空间。

比如我们可以称一个平面的基张成的空间为这个平面，称共线的向量张成的空间为这条直线。



#### 线性变换

线性变换实际上是把一个向量映射为另一个向量的函数。

这个函数是有要求的：

* 原本终点同一条直线上的向量变换后终点仍在同一条直线上
* 原来的零向量变换后还是零向量

满足这个要求的函数就叫做线性变换。



注意到如果 $v=a\hat{i}+b\hat{j}$，且 $\hat{i}',\hat{j}',v'$ 为 $\hat{i},\hat{j},v$ 变换后的结果，那么 $v'=a\hat{i}'+b\hat{j}'$。

因此，只需要 $\hat i',\hat j'$ 就可以描述一个线性变换了。



我们把 $\hat i',\hat j'$ 写在一起，就构成了一个 $2\times2$ 的矩阵，这个矩阵就描述了一个线性变换。

容易得知所有线性变换都可以写成这样的矩阵。

例如将坐标系逆时针旋转 $90^{\circ}$ 的线性变换所对应的矩阵就是 $\begin{bmatrix}0 & -1\\1\ &0\end{bmatrix}$。

将一个变换作用于一个向量就是我们熟知的矩阵乘法，其原理就如上文所述。



容易发现两个线性变换的复合仍然是线性变换。

寻找两个线性变换的复合相当于把后者作用与前者的每一列构成的矩阵，这个过程也正是我们熟悉的矩阵乘法。



从这个角度看，矩阵乘法的结合律是显然的。



#### 行列式

我们注意到不同的线性变换实际上对空间是有扩张或收缩的。

注意到平面上所有正方形在经过线性变换后面积变化的比例是相同的，如果我们用小正方形近似任意一个图形区域，那么可以得知所有图形在变换前后面积变化比例都是相同的。

我们记 $|\det(A)|$ 表示面积变化的比例。

$\det(A)$ 的正负取决于平面是否发生了翻转，这是很自然的定义。



$\det(M_1M_2)=\det(M1)\det(M_2)$ 也是相当显然的。



行列式的一个表达式为 $\det(M)=\sum\limits_{\pi}(-1)^{r(\pi)}\prod\limits_{i=1}^nM_{i,\pi_i}$，暂未找到好理解的证明。

由上式可知实际上 $\det(M)=\det(rM)$，其中 $rM$ 表示 $M$ 的转置。



注意到把一列加到另一列上，相当于一个向量 $a$ 沿着另一个向量 $b$ 的方向进行了移动，由于平行关系，所以 $\det(M)$ 不变。外加转置矩阵不会影响 $\det$，所以将其高消至只剩对角线即可。



注意到如果 $\det(M)=0$，实际上意味着这个变换使得某些维度坍缩了。



#### 逆、秩

当我们想找一个变换 $M^{-1}$ 使得 $M^{-1}M$ 是一个什么也不做的变换时，我们就称 $M^{-1}$ 是 $M$ 的逆。

注意到如果某个维度发生了坍缩，也就是 $\det=0$ 那么实际上是没有逆的。

**矩阵的逆求法**



变换 $M$ 的所有列向量所张成的空间成为 列空间，列空间的维度数成为矩阵 $M$ 的秩。





#### 点积

定义两个维度数相同的向量 $a,b$，定义其点积为对应每位积之和。

有一个几何解释就是 $a\cdot b=|a||b|\cos<a,b>$。





#### 叉积

叉积只从二维上讲，有 $a\times b=|a||b|\sin<a,b>$，表示 $a,b$ 构成的平行四边形的面积。

计算方法可以使用行列式。



事实上，叉积是针对三维向量的，其结果向量与 $a,b$ 张成的平面垂直，符合右手定则，且模长等于 $|a||b|\sin<a,b>$。



#### 基变换

假如我们使用的就是标标准准的 $\hat i,\hat j$，但是别人给出了一个向量 $(a,b)$ 以 $\hat u,\hat v$ 作为基向量的表示，怎么转化到我们的系里呢？



注意到如果 $\hat u,\hat v$ 在我们的系中表示为 $(p,q),(s,t)$，那么实际上 $(a,b)$ 在我们的系中就是 $a\hat u + b\hat v$ 也就是 $(ap+as,qs+qt)$，更进一步实际上就是 $(a,b)$ 左乘了一个矩阵 $\begin{bmatrix}p & s \\ q & t\end{bmatrix}$。

而将我们的系中的向量转化到别人的系里，就是左乘这个矩阵的逆。



当我们想要得到别人以 $(p,q),(s,t)$ 作为基的系里的向量 $a$ 逆时针旋转 $90^{\circ}$ 的结果时，相当于求 $\begin{bmatrix}p&s\\q&t\end{bmatrix}^{-1}\begin{bmatrix}0&-1\\1&0\end{bmatrix}\begin{bmatrix}p&s\\q&t\end{bmatrix}a$。



#### 特征向量 特征值

在一个线性变换中，如果一个向量没有离开他所张成的空间，或者说他仅仅之发生了模长的变化，那么称这个向量为这个变换的特征向量，且其对应特征值为其模长的变化倍数。



比如一个变换为 $M$，其特征向量为 $v$，其特征值为 $a$，那么有 $Mv=av$。

我们进行处理有：
$$
\begin{aligned}
Mv&=av
\\
Mv&=aIv
\\
Mv-aIv&=0
\\
(M-aI)v&=0
\end{aligned}
$$
注意到变换 $M-aI$ 使向量 $v$ 坍缩到了原点，那么显然有 $\det(M-aI)=0$。

因此通过解方程 $\det(M-xI)=0$，解出来的 $x$ 就是所有特征值。





把特征值带回上式，得到一个关于 $v$ 的方程，显然也是个线性方程组。

这个方程组的所有解就是这个特征值对应的特征向量。



##### 例题

给定一个 $n\times n$ 的矩阵 $M$，求该矩阵的 $k$ 次方。

保证数据随机。



##### 解法

由于数据随机，于是我们可以求出这个矩阵的特征向量 $v_1,v_2,v_3\dots v_n$，要应用 $k$ 次变换 $M$ 可以改成先转到以特征向量作为基，然后应用 $k$ 次以特征向量作为基的变换，在变换回原来的坐标系，也就是：
$$
A^{-1}M'^kA
$$
其中有：
$$
M'=\begin{bmatrix}\lambda_1&0&\cdots&0\\0&\lambda_2&\cdots&0\\\vdots&&\ddots\\0&\dots&0&\lambda_n\end{bmatrix}
$$

注意到 $M^k$ 是非常好求的。