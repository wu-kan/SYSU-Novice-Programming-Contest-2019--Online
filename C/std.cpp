#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 9;
char s[N];
int main()
{
	for (; fgets(s, N, stdin) && s[0] != '\n'; printf("<br/>\n"))
	{
		*strchr(s, '\n') = 0;
		if (s[0] == '#')
		{
			int hn = strchr(s, ' ') - s;
			printf("<h%d>%s</h%d>", hn, s + hn + 1, hn);
			continue;
		}
		for (int i = 0; s[i]; ++i)
		{
			if (s[i] != '[')
			{
				printf("%c", s[i]);
				continue;
			}
			int title = i + 1,
				link = strchr(s + title, '(') + 1 - s;
			s[link - 2] = s[i = strchr(s + link, ')') - s] = 0;
			printf("<a href=\"%s\">%s</a>", s + link, s + title);
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
*/
/*
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ofstream fout("input.9.in");
	fout << "###### " + string(1e6 - 1 - 7, 'w') + "\n";
}
*/