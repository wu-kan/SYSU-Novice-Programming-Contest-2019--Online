/* Output validator for "A Different Problem".  This validator is only
 * provided as an example: the problem is so simple that it does not
 * need a custom output validator and it would be more appropriate to
 * use the default token-based diff validator.
 *
 * Note: if you start writing error messages in, say, Swedish, make
 * sure your file is UTF-8 coded.
 */
#include "validate.h"
#include <string>
#include <sstream>

using namespace std;
typedef long long int64;
const int N = 63;
int n, g[N][N];
bool read_input(istream &in)
{
	in >> n;
	for (int i = 0; i < n; ++i)
	{
		string x, s, y, t;
		in >> x >> s >> y >> t;
		int P = (x[0] - 'a' << 1) | (s[0] == 'w'),
			Q = (y[0] - 'a' << 1) | (t[0] == 'w');
		g[P][Q ^ 1] = g[Q ^ 1][P] = g[P ^ 1][Q] = g[Q][P ^ 1] = 1;
	}
	return true;
}

string read_solution(istream &sol, feedback_function feedback)
{
	// read a solution from "sol" (can be either judge answer or
	// submission output), check its feasibility etc and return some
	// representation of it

	string s;
	getline(sol, s);
	if (!sol)
	{
		feedback("EOF or next token is not an string");
	}
	return s;
}

bool check_case()
{
	if (!read_input(judge_in))
		return false;
	string ans = read_solution(judge_ans, judge_error);
	string out = read_solution(author_out, wrong_answer);

	if (ans == "Nie")
	{
		if (ans != out)
			wrong_answer("judge answer = %s but submission output = %s\n", ans.c_str(), out.c_str());
		return true;
	}
	int ou = 0;
	if (out != "All")
	{
		istringstream sin(out);
		for (string s; sin >> s;)
		{
			if (s.size() > 1 || s.empty() || !('a' <= s[0] && s[0] <= 'z'))
			{
				wrong_answer("invalid output %s\n", out.c_str());
				return true;
			}
			ou |= 1 << s[0] - 'a';
		}
	}
	for (int P = (n << 1) - 1; ~P; --P)
		for (int Q = (n << 1) - 1; ~Q; --Q)
			if (g[P][Q])
			{
				int cnt = 0;
				for (int a[2] = {P, Q}, i = 0; i < 2; ++i)
				{
					int x = a[i] >> 1, s = a[i] & 1;
					if (((ou >> x) & 1) == s)
						++cnt;
				}
				if (cnt == 1)
					wrong_answer("wrong answer\n");
			}
	return true;
}

int main(int argc, char **argv)
{
	init_io(argc, argv);

	//while (check_case());
	check_case();

	/* Check for trailing output. */
	string trash;
	if (author_out >> trash)
	{
		wrong_answer("Trailing output");
	}

	accept();
}
