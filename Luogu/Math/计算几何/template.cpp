#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const double Pi = acos(-1.0);
const int N = 3e5 + 10;

namespace CG {
    struct pt {
        double x, y;
        pt(double _x = 0, double _y = 0) {
            x = _x;
            y = _y;
        }
        inline void read() { scanf("%lf%lf", &x, &y); }
    } O;
    typedef pt vec;
    inline vec operator+(const vec &a, const vec &b) { return vec(a.x + b.x, a.y + b.y); }
    inline vec operator-(const vec &a, const vec &b) { return vec(a.x - b.x, a.y - b.y); }
    inline vec operator*(const vec &a, double b) { return vec(a.x * b, a.y * b); }
    inline vec operator/(const vec &a, double b) { return vec(a.x / b, a.y / b); }
    inline double operator*(const vec &a, const vec &b) { return a.x * b.x + a.y * b.y; } // 点积
    inline double operator^(const vec &a, const vec &b) { return a.x * b.y - a.y * b.x; } // 叉积

    inline double Len(const vec &a) { return sqrt(a.x * a.x + a.y * a.y); } // 模长
    inline double angle(const vec &a) { return atan2(a.y, a.x); }
    inline bool cmpx(const pt &a, const pt &b) { return (a.x != b.x) ? a.x < b.x : a.y < b.y; }
    inline int dcmp(double x) { return (x < -eps) ? -1 : (x > eps ? 1 : 0); }
    inline double Abs(double x) { return x * dcmp(x); }
    
    inline double dis_PP(pt a, pt b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }   
    inline vec rotate(vec a, double theta) { // 将点或向量a绕原点(向量是顶点)逆时针旋转theta的弧度
        double x = a.x * cos(theta) - a.y * sin(theta);
        double y = a.x * sin(theta) + a.y * cos(theta);
        return pt(x, y);
    }
    inline vec rotate_90(vec a) { return pt(a.y, -a.x); }
    inline pt rotate_P(pt a, pt b, double theta) { return rotate(a - b, theta) + b; } // 将点a绕点b逆时针旋转theta

    // 命名技巧：点P(point)，线段S(segment)，射线R(ray)，直线L(line)
    struct line {
        pt s, t;
        line(pt _s = pt(0, 0), pt _t = pt(0, 0)) {
            s = _s;
            t = _t;
        }
    };
    inline double maxx(const line &L) { return max(L.s.x, L.t.x); }
    inline double maxy(const line &L) { return max(L.s.y, L.t.y); }
    inline double minx(const line &L) { return min(L.s.x, L.t.x); }
    inline double miny(const line &L) { return min(L.s.y, L.t.y); }
    inline double ang(const line &L) { return angle(L.t - L.s); }

    inline bool operator<(const line &a, const line &b) {
        double a1 = angle(a.t - a.s), a2 = angle(b.t - b.s);
        if (dcmp(a2 - a1) != 0) return dcmp(a2 - a1) > 0;
        return dcmp((b.t - a.s) ^ (a.t - a.s)) > 0;
    }
    inline bool operator==(pt a, pt b) { return (!dcmp(a.x - b.x)) && (!dcmp(a.y - b.y)); }           // 点a与点b间的距离
    inline bool judge_PL(pt a, line b) { return !dcmp((a - b.s) ^ (b.t - b.s)); }                                         // 判断点是否在直线上
    inline bool judge_PS(pt a, line b) { return (!dcmp((a - b.s) ^ (b.t - b.s))) && (dcmp((a - b.s) * (a - b.t)) <= 0); } // 判断点是否在线段上

    inline bool operator < (const pt &a, const pt &b) { double p = angle(a - O), q = angle(b - O); return p != q ? p < q : dis_PP(a, O) < dis_PP(b, O); }

    inline pt Footprint(pt a, line b) { // 点A关于直线ST的垂足
        pt x = a - b.s, y = a - b.t, z = b.t - b.s;
        double s1 = x * z, s2 = -1.0 * (y * z); // 分别求出AS，AT关于ST的投影
        return b.s + z * (s1 / (s1 + s2));
    }
    inline pt mirror(pt a, line b) { return a + (Footprint(a, b) - a) * 2.0; }                 // 点a关于直线b的对称点
    inline double dis_PL(pt a, line b) { return Abs((a - b.s) ^ (a - b.t)) / Len(b.t - b.s); } // 点与直线的距离:面积除以底边长
    inline double dis_PS(pt a, line b) {                                                       // 点与线段的距离
        pt x = a - b.s, y = a - b.t, z = b.t - b.s;
        if (dcmp(x * z) < 0) return Len(x); // 距离左端点最近
        if (dcmp(y * z) > 0) return Len(y); // 距离右端点最近
        return dis_PL(a, b);
    }
    inline pt point_PS(pt a, line b) { // 点a在线段b上距离最近的点
        pt x = a - b.s, y = a - b.t, z = b.t - b.s;
        if (dcmp(x * z) < 0) return b.s; // 距离左端点最近
        if (dcmp(y * z) > 0) return b.t; // 距离右端点最近
        return Footprint(a, b);
    }

    inline pt cross_LL(line a, line b) { // 直线的交点
        pt x = a.t - a.s, y = b.t - b.s, z = a.s - b.s;
        return a.s + x * ((y ^ z) / (x ^ y));
    }
    inline bool judge_cross_SL(line a, line b) { // 判断线段a与直线b是否相交
        if (!dcmp((a.t - a.s) ^ (b.t - b.s))) return false;
        return judge_PS(cross_LL(a, b), a); // 看交点是否在线段上即可
    }
    inline bool judge_cross_SS(line a, line b) { // 判断两线段是否相交
        if (maxx(a) < minx(b) || maxy(a) < miny(b)) return false;
        if (maxx(b) < minx(a) || maxy(b) < miny(a)) return false;
        double s1 = (a.t - a.s) ^ (b.s - a.s), s2 = (a.t - a.s) ^ (b.t - a.s);
        double s3 = (b.t - b.s) ^ (a.s - b.s), s4 = (b.t - b.s) ^ (a.t - b.s);
        return dcmp(s1) * dcmp(s2) <= 0 && dcmp(s3) * dcmp(s4) <= 0; // a的端点在b的两侧且b的端点在a的两侧
    }
}
using namespace CG;

namespace Polygon { // 多边形
    struct polygon {
        vector<pt> pts;
        inline pt &operator[](int x) { return pts[x]; }
        inline void read(int n) {
            pt cur;
            for (int i = 0; i < n; ++i) cur.read(), pts.push_back(cur);
        }
        inline void clear() { pts.clear(); }
        inline int nxt(int x) { return x < pts.size() - 1 ? x + 1 : 0; }
        inline int include(pt p) { // 点在多边形上：0:在多边形外,1:在多边形内，2：在多边形的边上
            int cnt = 0;
            for (int i = 0; i < pts.size(); ++i) {
                pt s = pts[i], t = pts[nxt(i)];
                line L = line(s, t);
                if (judge_PS(p, L)) return 2;
                if (dcmp(p.y - miny(L)) >= 0 && dcmp(maxy(L) - p.y) > 0) {
                    double nx = s.x + ((p.y - s.y) / (t.y - s.y) * (t.x - s.x));
                    if (dcmp(nx - p.x) > 0) cnt++;
                }
            }
            return cnt & 1;
        }

        inline double area() { // 面积
            double ans = 0;
            for (int i = 1; i < pts.size() - 1; ++i) ans += (pts[i] - pts[0]) ^ (pts[nxt(i)] - pts[0]);
            return Abs(ans) / 2;
        }
        inline double peri() { // 周长
            double ans = 0;
            for (int i = 0; i < pts.size(); ++i) ans += dis_PP(pts[i], pts[nxt(i)]);
            return ans;
        }
        inline bool Left(pt x, pt l, pt r) { return dcmp((l - x) ^ (r - x)) <= 0; } // xl是否在xr左侧
        inline void rever() { reverse(pts.begin(), pts.end()); }                    // 转顺时针为逆时针
        inline int include_bs(pt p) {                                               // 二分法判断点是否在多边形内
            int n = pts.size();
            if (!Left(pts[0], p, pts[1])) return 0;
            if (!Left(pts[0], pts[n - 1], p)) return 0;
            if (judge_PS(p, line(pts[0], pts[1]))) return 2;
            if (judge_PS(p, line(pts[0], pts[n - 1]))) return 2;
            int l = 1, r = n - 2, ans = 1;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (!Left(pts[0], pts[mid], p))
                    l = mid + 1, ans = mid;
                else
                    r = mid - 1;
            }
            if (!Left(pts[ans], p, pts[nxt(ans)])) return 0;
            if (judge_PS(p, line(pts[ans], pts[nxt(ans)]))) return 2;
            return 1;
        }
        inline void insert(pt p) { pts.push_back(p); }
    };
    inline bool disjoint(polygon A, polygon B) { // 多边形AB是否相离
        for (int i = 0; i < A.pts.size(); ++i) {
            line x = line(A[i], A[A.nxt(i)]);
            for (int j = 0; j < B.pts.size(); ++j) {
                line y = line(B[j], B[B.nxt(j)]);
                if (judge_cross_SS(x, y)) return false;
            }
        }
        if (A.include_bs(B[0])) return false;
        if (B.include_bs(A[0])) return false;
        return true;
    }
}
using namespace Polygon;

namespace Hull {                     // 凸包、旋转卡壳、半平面交、闵可夫斯基和
    inline void Andrew(polygon &p) { // Andrew算法求凸包
        vector<pt> q(p.pts.size() << 1);
        sort(p.pts.begin(), p.pts.end(), cmpx);
        int top = -1, n = p.pts.size();
        q[++top] = p[0];
        for (int i = 1; i < n; ++i) {
            while (top && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) top--;
            q[++top] = p[i];
        }
        int now = top;
        for (int i = n - 2; i >= 0; --i) {
            while (top > now && dcmp((q[top - 1] - q[top]) ^ (p[i] - q[top])) >= 0) --top;
            q[++top] = p[i];
        }
        if (n > 1) --top;
        p.clear();
        for (int i = 0; i <= top; ++i) p.insert(q[i]);
    }
    inline vector<pt> Graham(vector<pt> vec) { // atan2函数排序存在精度问题！！！！
        int n = ((int)vec.size());
        for (int i = 1; i < n; ++i) if (vec[i].y < vec[0].y || (vec[i].y == vec[0].y && vec[i].x < vec[0].x)) swap(vec[0], vec[i]);
        O = vec[0];
        sort(vec.begin() + 1, vec.end());
        vector<pt> s(n + 1);
        int ed = 0;
        for (int i = 0; i < n; ++i) {
            while (ed >= 2 && dcmp((s[ed] - s[ed - 1]) ^ (vec[i] - s[ed - 1])) <= 0) --ed;
            s[++ed] = vec[i];
        }
        vector<pt> res;
        for (int i = 1; i <= ed; ++i) res.emplace_back(s[i]);
        return res;
    }
    inline double S(const pt &x, const pt &y, const pt &z) { return Abs((y - x) ^ (z - x)); }
    inline double diam(polygon &p) { // 旋转卡壳求凸包直径
        int n = p.pts.size();
        double ans = 0;
        for (int i = 0, j = 1; i < n; ++i) {
            for (;; j = p.nxt(j))
                if (dcmp(S(p[j], p[i], p[p.nxt(i)]) - S(p[p.nxt(j)], p[i], p[p.nxt(i)])) >= 0) break;
            ans = max(ans, dis_PP(p[j], p[i]));
            ans = max(ans, dis_PP(p[j], p[p.nxt(i)]));
        }
        return ans;
    }
    inline polygon SI(vector<line> q) { // 半平面交算法 S&I
        int n = q.size();
        sort(q.begin(), q.end());
        vector<line> li(n + 1), L(n + 1);
        vector<pt> p(n + 1);
        int len = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && !dcmp(ang(q[i]) - ang(q[i - 1]))) continue;
            L[++len] = q[i];
        }
        int l = 1, r = 0;
        for (int i = 1; i <= len; ++i) {
            while (l < r && dcmp((L[i].t - p[r]) ^ (L[i].s - p[r])) > 0) --r;
            while (l < r && dcmp((L[i].t - p[l + 1]) ^ (L[i].s - p[l + 1])) > 0) ++l;
            li[++r] = L[i];
            if (r > l) p[r] = cross_LL(li[r], li[r - 1]);
        }
        while (l < r && dcmp((li[l].t - p[r]) ^ (li[l].s - p[r])) > 0) --r;
        while (l < r && dcmp((li[r].t - p[l + 1]) ^ (li[r].s - p[l + 1])) > 0) ++l;

        p[r + 1] = cross_LL(li[r], li[l]), ++r;
        polygon P;
        for (int j = l + 1; j <= r; ++j) P.insert(p[j]);
        return P;
    }
    inline polygon merge(polygon A, polygon B) { // 闵可夫斯基和
        int n = A.pts.size(), m = B.pts.size(), tot1 = 0, tot2 = 0;
        vector<pt> p(n + 1), q(m + 1);
        for (int i = 1; i < n; ++i) p[++tot1] = A[i] - A[i - 1]; p[++tot1] = A[0] - A[n - 1];
        for (int i = 1; i < m; ++i) q[++tot2] = B[i] - B[i - 1]; q[++tot2] = B[0] - B[m - 1];
        int i = 1, j = 1, tot = 0;
        pt last = pt(0, 0);
        polygon C;
        C.pts.resize(n + m + 1);
        C[0] = last = A[0] + B[0];
        while (i <= n && j <= m) {
            if (dcmp(p[i] ^ q[j]) >= 0) C[++tot] = last + p[i++], last = C[tot];
            else C[++tot] = last + q[j++], last = C[tot];
        }
        while (i <= n) C[++tot] = last + p[i++], last = C[tot];
        while (j <= m) C[++tot] = last + q[j++], last = C[tot];
        Andrew(C);
        return C;
    }
}
using Hull::Andrew;
using Hull::diam;
using Hull::merge;

namespace Circle { // 圆：三点确定一圆、最小圆覆盖
    struct circle {
        pt o;
        double r;
        circle(pt _o = pt(0, 0), double _r = 0) {
            o = _o;
            r = _r;
        }
        circle(pt A, pt B, pt C) { // 三点确定一圆
            pt D = (A + B) / 2, E = (B + C) / 2;
            o = cross_LL(line(D, D + rotate_90(B - A)), line(E, E + rotate_90(C - B)));
            r = dis_PP(o, A);
        }
        inline bool include(pt p) { return dcmp(r - dis_PP(p, o)) >= 0; } // 点在圆内
        inline void print(int x) {
            printf("%.*lf\n", x, r);
            printf("%.*lf %.*lf", x, o.x, x, o.y);
        }
    };
    inline circle mincov(const vector<pt> &p) { // 最小圆覆盖
        int n = p.size();
        circle c = circle(0, 0);
        for (int i = 0; i < n; ++i) {
            if (!c.include(p[i])) {
                c = circle(p[i], 0);
                for (int j = 0; j < i; ++j) {
                    if (!c.include(p[j])) {
                        c = circle((p[i] + p[j]) / 2.0, dis_PP(p[i], p[j]) / 2.0);
                        for (int k = 0; k < j; ++k)
                            if (!c.include(p[k])) c = circle(p[i], p[j], p[k]);
                    }
                }
            }
        }
        return c;
    }
}
using namespace Circle;
