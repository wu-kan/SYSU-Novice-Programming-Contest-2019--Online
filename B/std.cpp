#include <bits/stdc++.h>
using namespace std;
const int BIT = 31;
int n, k, a, b[BIT];
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0, j; i < n; ++i)
		for (scanf("%d", &a), j = 0; a; ++j, a >>= 1)
			if (a & 1)
				++b[j];
	for (int j = a = 0; j < BIT; ++j)
		a |= b[j] % k << j;
	printf("%d", a);
}
/*
g++ std.cpp -o std
./std < data/secret/1.in > data/secret/1.ans
./std < data/secret/2.in > data/secret/2.ans
./std < data/secret/3.in > data/secret/3.ans
./std < data/secret/4.in > data/secret/4.ans
./std < data/secret/5.in > data/secret/5.ans
./std < data/secret/6.in > data/secret/6.ans
./std < data/secret/7.in > data/secret/7.ans
./std < data/secret/8.in > data/secret/8.ans
./std < data/secret/9.in > data/secret/9.ans
./std < data/secret/10.in > data/secret/10.ans
*/
/*
#include <bits/stdc++.h>
using namespace std;
const int m = 1919810, k = 7, n = (114514 - 1) / k * k + 1;
int main()
{
	srand(time(0));
	ofstream fout("input.7.in");
	unordered_set<int> se;
	while (se.size() <= n / k)
		se.insert(abs(int(rand()) << 15 | rand()) % m);
	fout << n << ' ' << k << '\n';
	vector<int> a{*se.begin()};
	se.erase(a[0]);
	for (auto it : se)
		for (int i = 0; i < k; ++i)
			a.push_back(it);
	random_shuffle(a.begin(), a.end());
	for (auto it : a)
		fout << it << ' ';
}
*/