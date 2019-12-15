#include <bits/stdc++.h>
using namespace std;
struct Graph
{
	struct Vertex
	{
		vector<int> o;
	};
	typedef pair<int, int> Edge;
	vector<Vertex> v;
	vector<Edge> e;
	Graph(int n) : v(n) {}
	void add(const Edge &ed)
	{
		v[ed.first].o.push_back(e.size());
		e.push_back(ed);
	}
};
struct TwoSat : Graph
{
	vector<int> ok;
	TwoSat(int n) : Graph(n) {}
	void addOR(int p, int q) { add({p ^ 1, q}), add({q ^ 1, p}); }
	int dfs(int u, vector<int> &stak)
	{
		if (ok[u ^ 1])
			return 0;
		if (ok[u])
			return 1;
		ok[u] = 1;
		stak.push_back(u);
		for (int k : v[u].o)
			if (!dfs(e[k].second, stak))
				return 0;
		return 1;
	}
	int ask()
	{
		ok.assign(v.size(), 0);
		for (int i = 0; i < v.size(); i += 2)
			if (!ok[i] && !ok[i ^ 1])
			{
				vector<int> stak;
				if (!dfs(i, stak))
				{
					for (int j = 0; j < stak.size(); ++j)
						ok[stak[j]] = 0;
					if (!dfs(i ^ 1, stak))
						return 0;
				}
			}
		return 1;
	}
};
int main()
{
	int n;
	scanf("%d", &n);
	TwoSat g(n << 1);
	for (int i = 0; i < n; ++i)
	{
		char x[9], s[9], y[9], t[9];
		scanf("%s%s%s%s", x, s, y, t);
		int P = x[0] - 'a' << 1 | s[0] == 'w',
			Q = y[0] - 'a' << 1 | t[0] == 'w';
		g.addOR(P, Q);
		g.addOR(P ^ 1, Q ^ 1);
	}
	if (!g.ask())
		return printf("Nie"), 0;
	for (int i = n = 0; i < g.ok.size(); i += 2)
		if (!g.ok[i])
			printf("%c ", 'a' + (i >> 1)), ++n;
	if (!n)
		printf("All");
}
/*
g++ WerewolfKill.1.cpp -o WerewolfKill
time ./WerewolfKill < input.0.in > output.0.out
time ./WerewolfKill < input.1.in > output.1.out
time ./WerewolfKill < input.2.in > output.2.out
time ./WerewolfKill < input.3.in > output.3.out
time ./WerewolfKill < input.4.in > output.4.out
time ./WerewolfKill < input.5.in > output.5.out
time ./WerewolfKill < input.6.in > output.6.out
time ./WerewolfKill < input.7.in > output.7.out
time ./WerewolfKill < input.8.in > output.8.out
time ./WerewolfKill < input.9.in > output.9.out
*/
/*
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n = 26;
	srand(time(0));
	for (int fi = 3; fi < 10; ++fi)
	{
		ofstream fout("input." + string(1, '0' + fi) + ".in");
		fout << n << '\n';
		int ans = abs(int(rand()) << 15 | rand()) % (1 << 26);
		for (int i = 0; i < n; ++i)
		{
			int x = rand() % n, y = rand() % n, s = (ans >> x) & 1, t = (ans >> y) & 1;
			t = !t;
			if (rand() % 2)
				swap(x, y), swap(s, t);
			fout << char('a' + x) << (s ? " werewolf " : " villager ")
				 << char('a' + y) << (t ? " werewolf\n" : " villager\n");
		}
	}
}
*/