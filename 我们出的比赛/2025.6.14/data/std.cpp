#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	1000000
#define MD	1000000007
#define V2	500000004

int vv[N + 1], ff[N + 1], gg[N + 1];

void init() {
	int i;

	ff[0] = gg[0] = 1;
	for (i = 1; i <= N; i++) {
		vv[i] = i == 1 ? 1 : (long long) vv[i - MD % i] * (MD / i + 1) % MD;
		ff[i] = (long long) ff[i - 1] * i % MD;
		gg[i] = (long long) gg[i - 1] * vv[i] % MD;
	}
}

int *ex[N], *ey[N], *ew[N], *et[N], eo[N];

void append(int a, int x, int y, int t) {
	int o = eo[a]++;

	if (o >= 2 && (o & o - 1) == 0) {
		ex[a] = (int *) realloc(ex[a], o * 2 * sizeof *ex[a]);
		ey[a] = (int *) realloc(ey[a], o * 2 * sizeof *ey[a]);
		et[a] = (int *) realloc(et[a], o * 2 * sizeof *et[a]);
		ew[a] = (int *) realloc(ew[a], o * 2 * sizeof *ew[a]);
	}
	ex[a][o] = x, ey[a][o] = y, et[a][o] = t, ew[a][o] = 0;
}

int choose(int n, int k) {
	return k < 0 || k > n ? 0 : (long long) ff[n] * gg[k] % MD * gg[n - k] % MD;
}

int count_(int x1, int y1, int x2, int y2, int d) {
	x1 = -x1, x2 = -x2;
	if (x1 > x2 || y1 > y2 || y2 - x2 < 0 || y2 - x2 >= d)
		return 0;
	return ((long long) choose(x2 - x1 + y2 - y1, x2 - x1) - choose(x2 - x1 + y2 - y1, y2 - x1 + 1) - choose(x2 - x1 + y2 - y1, y2 - x1 - d) + MD * 2) % MD;
}

int sum(int *aa, int l, int r) {
	return l > r ? 0 : (aa[r] - (l == 0 ? 0 : aa[l - 1]) + MD) % MD;
}

int solve(int *aa, int n) {
	static int ii[N], pp[N];
	int i, a, b, ans, o, o_;

	memset(ii, -1, n * sizeof *ii);
	for (i = 0; i < n; i++)
		if (aa[i] != -1)
			ii[aa[i]] = i;
	for (i = 0; i < n; i += 2)
		pp[i] = i / 2;
	for (i = 1; i < n; i += 2)
		pp[i] = n - 1 - i / 2;
	for (a = 0; a < n; a++) {
		ex[a] = (int *) malloc(2 * sizeof *ex[a]);
		ey[a] = (int *) malloc(2 * sizeof *ey[a]);
		et[a] = (int *) malloc(2 * sizeof *et[a]);
		ew[a] = (int *) malloc(2 * sizeof *ew[a]);
		eo[a] = 0;
	}
	for (a = 0; a < n; a++)
		if (a == 0) {
			for (i = 0; i < n; i += 2)
				if (ii[a] == -1 || ii[a] == i)
					append(a, pp[i], pp[i], 0);
		} else if (a == n - 1) {
			for (i = 1; i < n; i += 2)
				if (ii[a] == -1 || ii[a] == i)
					append(a, pp[i] - n, pp[i] - 1, 0);
		} else if ((i = ii[a]) != -1) {
			if (pp[i] * 2 + a >= 0 && pp[i] * 2 + a < n)
				append(a, pp[i], pp[i] + a, 0);
			if (pp[i] * 2 + a - n * 2 >= 0 && pp[i] * 2 + a - n * 2 < n)
				append(a, pp[i] - n, pp[i] + a - n, 0);
			if (pp[i] * 2 - a >= 0 && pp[i] * 2 - a < n)
				append(a, pp[i] - a, pp[i], 1);
			if (pp[i] * 2 - a + n * 2 >= 0 && pp[i] * 2 - a + n * 2 < n)
				append(a, pp[i] - a + n, pp[i] + n, 1);
		}
	a = 0;
	for (o = eo[a]; o--; )
		ew[a][o] = 1;
	for (a = 0, b = 1; b < n; b++)
		if (ii[b] != -1 || b == n - 1) {
			for (o = eo[a]; o--; ) {
				int x = ex[a][o], y = ey[a][o], w = ew[a][o];

				if (w == 0)
					continue;
				for (o_ = eo[b]; o_--; ) {
					int x_ = ex[b][o_], y_ = ey[b][o_], t_ = et[b][o_];

					if (t_ == 0)
						ew[b][o_] = (ew[b][o_] + (long long) w * count_(x, y, x_ + 1, y_, n)) % MD;
					else
						ew[b][o_] = (ew[b][o_] + (long long) w * count_(x, y, x_, y_ - 1, n)) % MD;
				}
			}
			a = b;
		}
	a = n - 1;
	ans = 0;
	for (o = eo[a]; o--; )
		ans = (ans + ew[a][o]) % MD;
	for (a = 0; a < n; a++)
		free(ex[a]), free(ey[a]), free(et[a]), free(ew[a]);
	return ans;
}

int main() {
	// freopen("cat8.in","r",stdin);
	// freopen("cat8.ans","w",stdout);
	int t;
	init();
	scanf("%d", &t);
	while (t--) {
		static int aa[N], cc[N];
		int n, h, i, ans, zero;

		scanf("%d", &n);
		zero = 1;
		for (i = 0; i < n; i++) {
			scanf("%d", &aa[i]), aa[i]--;
			if (aa[i] != -2)
				zero = 0;
		}
		if (!zero) {
			ans = 0;
			for (h = 0; h < 2; h++) {
				ans = (ans + solve(aa, n)) % MD;
				for (i = 0; i < n; i++)
					if (aa[i] != -2)
						aa[i] = n - 1 - aa[i];
			}
		} else {
			ans = 0;
			for (i = 0; i <= n - 2; i++)
				cc[i] = choose(n - 2, i);
			for (i = 1; i <= n - 2; i++)
				cc[i] = (cc[i] + cc[i - 1]) % MD;
			for (i = 0; i * 2 < n; i++)
				ans = ((long long) ans + sum(cc, i, n / 2 - 1 + i) - sum(cc, (n + 1) / 2 + i, n - 2) - sum(cc, 0, i - 2)) % MD;
			ans = ans * 2 % MD;
			if (ans < 0)
				ans += MD;
		}
		printf("%d\n", ans);
	}
	return 0;
}

