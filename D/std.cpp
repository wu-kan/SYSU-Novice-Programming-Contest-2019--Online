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
struct StronglyConnectedComponenet : Graph
{
	vector<int> dep, sid, stak; //sid=点所属连通块内一点
	StronglyConnectedComponenet(int n) : Graph(n) {}
	void ask()
	{
		dep.assign(v.size(), v.size());
		sid.assign(v.size(), v.size());
		for (int i = 0; i < v.size(); ++i)
			if (dep[i] == v.size())
				dfs(i, v.size());
	}
	int dfs(int u, int fa)
	{
		int low = dep[u] = fa != v.size() ? dep[fa] + 1 : 0;
		stak.push_back(u);
		for (int i = 0, k, to; i < v[u].o.size(); ++i)
			if (k = v[u].o[i], to = e[k].second, to != fa, 1) //求强连通分量把注释去掉，即允许走回边
			{
				if (dep[to] == v.size())
					low = min(low, dfs(to, u));
				else if (sid[to] == v.size())
					low = min(low, dep[to]);
			}
		if (low == dep[u])
			for (;;)
			{
				int x = stak.back();
				stak.pop_back();
				sid[x] = u;
				if (x == u)
					break;
			}
		return low;
	}
};
struct TwoSat : StronglyConnectedComponenet
{
	vector<int> ok;
	TwoSat(int n) : StronglyConnectedComponenet(n) {}
	void addOR(int p, int q) { add({p ^ 1, q}), add({q ^ 1, p}); }
	void addXOR(int a, int b) { addOR(a, b), addOR(a ^ 1, b ^ 1); }
	void addXNOR(int a, int b) { addOR(a, b ^ 1), addOR(a ^ 1, b); }
	int ask()
	{
		StronglyConnectedComponenet::ask();
		for (int i = 0; i < v.size(); i += 2)
			if (sid[i] == sid[i ^ 1])
				return 0;
		Graph g(v.size());
		vector<int> ind(v.size(), 0), cf(v.size(), 0);
		for (int i = 0; i < v.size(); ++i)
		{
			cf[sid[i]] = sid[i ^ 1];
			for (auto k : v[i].o)
				if (sid[e[k].second] != sid[i])
					g.add({sid[e[k].second], sid[i]}), ++ind[sid[i]];
		}
		deque<int> q;
		for (int i = 0; i < v.size(); ++i)
			if (sid[i] == i && !ind[i])
				q.push_back(i);
		for (ok.assign(v.size(), -1); !q.empty(); q.pop_front())
		{
			if (ok[q.front()] < 0)
				ok[q.front()] = 1, ok[cf[q.front()]] = 0;
			for (auto k : g.v[q.front()].o)
				if (!--ind[g.e[k].second])
					q.push_back(g.e[k].second);
		}
		for (int i = 0; i < v.size(); ++i)
			if (i != sid[i])
				ok[i] = ok[sid[i]];
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
		g.addXOR(x[0] - 'a' << 1 | s[0] == 'w', y[0] - 'a' << 1 | t[0] == 'w');
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