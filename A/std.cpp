#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	getline(cin, s);
	cout << map<string, int>{{"Yamada Tae", 0},
							 {"Minamoto Sakura", 1},
							 {"Nikaido Saki", 2},
							 {"Mizuno Ai", 3},
							 {"Konno Junko", 4},
							 {"Yugiri", 5},
							 {"Hoshikawa Lily", 6}}
				.at(s);
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
*/