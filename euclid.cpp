#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int GCD(int, int, vector<int> *);

int main()
{
    int a {20}, b {97}, gcd;

    std::vector<int> v;
    gcd = GCD(a, b, &v);
    std::cout << "Greatest common divisior is: ";
    std::cout << gcd << endl;
    std::cout << "-----steps-----" << endl;

    int P, Q, p_new, q_new;

    P = p_new = 1;

    for (auto itr = v.cend(); (itr-1) != v.begin(); itr--)
    {
        Q = q_new = - (*(itr-1));
        p_new = Q;
        q_new = P - Q * (*(itr-2));
        P = p_new;
        Q = q_new;
        std::cout << P * a + Q * b << endl;
    }
}

int GCD(int m, int n, vector<int> *v)
{
    if (m == n)
        return m;

    int Max = max(m, n);
    int Min = min(m, n);

    (*v).push_back(Max / Min);

    if (Max % Min == 0) {
        (*v).pop_back();
        return Min;
    }
        

    return GCD(Min, Max % Min, v);
}