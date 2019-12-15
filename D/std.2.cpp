#include <bits/stdc++.h>
using namespace std;
const int N = 63;
vector<int> g[N];
int dfs(int k, int state)
{
	if (k < 0)
		return state;
	int ok = 1;
	for (auto it : g[k << 1])
		if (bool(state & (1 << (it >> 1))) != (it & 1))
		{
			ok = 0;
			break;
		}
	if (ok)
	{
		int ans = dfs(k - 1, state);
		if (ans >= 0)
			return ans;
	}
	state |= 1 << k;
	ok = 1;
	for (auto it : g[k << 1 | 1])
		if (bool(state & (1 << (it >> 1))) != (it & 1))
		{
			ok = 0;
			break;
		}
	if (ok)
	{
		int ans = dfs(k - 1, state);
		if (ans >= 0)
			return ans;
	}
	return -1;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		char x[9], s[9], y[9], t[9];
		scanf("%s%s%s%s", x, s, y, t);
		int P = (x[0] - 'a' << 1) | (s[0] == 'w'),
			Q = (y[0] - 'a' << 1) | (t[0] == 'w');
		if (P > Q)
			swap(P, Q);
		g[P].push_back(Q ^ 1);
		g[P ^ 1].push_back(Q);
	}
	int ans = dfs(n - 1, 0);
	if (ans < 0)
		return printf("Nie"), 0;
	if (!ans)
		return printf("All"), 0;
	for (int i = 0; i < n; ++i)
		if (ans & (1 << i))
			printf("%c ", 'a' + i);
}
/*
g++ WerewolfKill.2.cpp -o WerewolfKill
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