#include <bits/stdc++.h>
using namespace std;
int t = 20, n = 17792, m = 17792;
int main()
{
    srand(time(0));
    for (int i = 2; i < 10; ++i)
    {
        ofstream fout("data/secret/" + string(1, '0' + i) + ".in");
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
                /*
                l = rand() % 9, r = rand() % 9 ? n - 1 - rand() % 9 : l;
                if (ti < 9)
                {
                    if (ti < 4)
                        w = 1;
                    if (ti < 6)
                        p = rand() % 2;
                    else if (ti == 6)
                        p = p ? p : 2;
                    else if (ti == 7)
                        p = p ? p : 3;
                    else
                        p = rand() % 4;
                }
                */
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