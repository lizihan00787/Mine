#include <bits/stdc++.h>
using namespace std;
#define double long double
#define pdd pair<double, double>
double get_dis(pdd x, pdd y) {
    return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}
double check(pdd l1, pdd r1, pdd l2, pdd r2) {
    return (r1.first - l1.first) * (r2.second - l2.second) - (r1.second - l1.second) * (r2.first - l2.first);
}
int n;
pdd a[100010];
bool cmp(pdd x, pdd y) { return check(a[1], x, a[1], y) > 0; }
int tot;
pdd st[100010];
double get_dis(pdd x, pdd y, pdd z) {
    double a = get_dis(x, y), b = get_dis(x, z), c = get_dis(y, z);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c)) * 2 / a;
}
int main() {
    freopen("P1452_10.in", "r", stdin);
    // freopen("std.out","w",stdout);
    cin >> n;
    double in = 1e9;
    int wz;
    mt19937 rnd(time(0));
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first >> a[i].second;
        a[i].first += rnd() * 1.0 / 1e15, a[i].second += rnd() * 1.0 / 1e15;
        if (in > a[i].second) in = a[i].second, wz = i;
    }
    swap(a[1], a[wz]);
    sort(a + 2, a + n + 1, cmp);
    st[tot = 1] = a[1];
    for (int i = 2; i <= n; ++i) {
        while (tot >= 2 && check(st[tot - 1], st[tot], st[tot], a[i]) < 0) --tot;
        st[++tot] = a[i];
    }
    for (int i = 1; i <= tot; ++i) st[i + tot] = st[i];
    int now = 2;
    double ans = 0;
    for (int i = 1; i <= tot; ++i) {
        while (get_dis(st[i], st[i + 1], st[now]) < get_dis(st[i], st[i + 1], st[now + 1])) ++now;
        ans = max(ans, max(get_dis(st[i], st[now]), get_dis(st[i + 1], st[now])));
    }
    printf("%.0Lf", ans * ans);
    return 0;
}
