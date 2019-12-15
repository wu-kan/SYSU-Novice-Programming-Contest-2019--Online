#include <bits/stdc++.h>
using namespace std;
const int N = 17792;
struct EulerSieve
{
	vector<int> p, m, phi;
	EulerSieve(int N) : m(N, 0), phi(N, 0)
	{
		phi[1] = 1;
		for (long long i = 2, k; i < N; ++i)
		{
			if (!m[i])
				p.push_back(m[i] = i), phi[i] = i - 1;
			for (int j = 0; j < p.size() && (k = i * p[j]) < N; ++j)
			{
				phi[k] = phi[i] * p[j];
				if ((m[k] = p[j]) == m[i])
					break;
				phi[k] -= phi[i];
			}
		}
	}
} e(N);
int t, n, m, a[N];
struct SegmentTree
{
	int l, r, val;
	vector<SegmentTree> ch;
	SegmentTree(int l, int r) : l(l), r(r), val(a[l])
	{
		if (l >= r)
			return;
		int m = l + (r - l >> 1);
		ch = {{l, m}, {m + 1, r}};
		val = max(ch[0].val, ch[1].val);
	}
	void div(int l, int r, int w)
	{
		if (val < 1 || w == 1)
			return;
		if (this->l >= this->r)
		{
			val /= w;
			return;
		}
		if (r <= ch[0].r)
			ch[0].div(l, r, w);
		else if (l >= ch[1].l)
			ch[1].div(l, r, w);
		else
			ch[0].div(l, ch[0].r, w), ch[1].div(ch[1].l, r, w);
		val = max(ch[0].val, ch[1].val);
	}
	void sqr(int l, int r)
	{
		if (val < 2)
			return;
		if (this->l >= this->r)
		{
			val = sqrt(val);
			return;
		}
		if (r <= ch[0].r)
			ch[0].sqr(l, r);
		else if (l >= ch[1].l)
			ch[1].sqr(l, r);
		else
			ch[0].sqr(l, ch[0].r), ch[1].sqr(ch[1].l, r);
		val = max(ch[0].val, ch[1].val);
	}
	void phi(int l, int r)
	{
		if (val < 2)
			return;
		if (this->l >= this->r)
		{
			val = e.phi[val];
			return;
		}
		if (r <= ch[0].r)
			ch[0].phi(l, r);
		else if (l >= ch[1].l)
			ch[1].phi(l, r);
		else
			ch[0].phi(l, ch[0].r), ch[1].phi(ch[1].l, r);
		val = max(ch[0].val, ch[1].val);
	}
	int ask(int l, int r)
	{
		if (l <= this->l && this->r <= r)
			return val;
		if (r <= ch[0].r)
			return ch[0].ask(l, r);
		if (l >= ch[1].l)
			return ch[1].ask(l, r);
		return max(ch[0].ask(l, ch[0].r), ch[1].ask(ch[1].l, r));
	}
};
int main()
{
	for (scanf("%d", &t); t--;)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		SegmentTree t(0, n - 1);
		for (int i = 0, l, r, w; i < m; ++i)
		{
			char s[9];
			scanf("%s%d%d", s, &l, &r);
			if (!strcmp(s, "div"))
				scanf("%d", &w), t.div(l, r, w);
			else if (!strcmp(s, "sqr"))
				t.sqr(l, r);
			else if (!strcmp(s, "phi"))
				t.phi(l, r);
			else
				printf("%d\n", t.ask(l, r));
		}
	}
}
/*
g++ std.cpp -o std
time ./std < data/secret/1.in > data/secret/1.ans
time ./std < data/secret/2.in > data/secret/2.ans
time ./std < data/secret/3.in > data/secret/3.ans
time ./std < data/secret/4.in > data/secret/4.ans
time ./std < data/secret/5.in > data/secret/5.ans
time ./std < data/secret/6.in > data/secret/6.ans
time ./std < data/secret/7.in > data/secret/7.ans
time ./std < data/secret/8.in > data/secret/8.ans
time ./std < data/secret/9.in > data/secret/9.ans
time ./std < data/secret/10.in > data/secret/10.ans
time ./std < data/sample/1.in > data/sample/1.ans
*/
/*
#include <bits/stdc++.h>
using namespace std;
int t = 10, n = 17792, m = 17792;
int main()
{
    srand(time(0));
    for (int i = 2; i < 3; ++i)
    {
        ofstream fout("data/secret/10.in");
        fout << t;
        for (int ti = 0; ti < t; ++ti)
        {
            fout << '\n'
                 << n << ' ' << m << '\n';
            for (int i = 0; i < n; ++i)
                fout << rand() % 17792 << ' ';
            for (int i = 0; i < m; ++i)
            {
                int l = rand() % n, r = rand() % n, w = rand() % 17792 + 1, p = rand() % 4;
                l = rand() % 9, r = rand() % 9 ? n - 1 - rand() % 9 : l;
				if (ti < 4)
				{
					if (!ti)
						w = 1;
					p = rand() % 2;
					if (ti > 1)
						p = p ? p : ti;
				}
                if (l > r)
                    swap(l, r);
                string s[4] = {"div", "ask", "sqr", "phi"};
                fout << "\n"
                     << s[p] << " " << l << " " << r;
                if (!p)
                    fout << " " << w;
            }
        }
    }
}
*/