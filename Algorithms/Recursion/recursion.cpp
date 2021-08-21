#include <iostream>
using namespace std;

void towerOfHanoi(int, int, int, int);
int fib(int);
int gcd(int, int);
int lcm(int, int);
int pow(int, int);
int factorial(int);

int main()
{
    // towerOfHanoi(3, 1, 3, 2);
    cout << fib(6);
}

void towerOfHanoi(int n, int src, int des, int aux)
{
    if (n == 1)
    {
        // Base case: if there is 1 disk, move it form src to des and finish.
        cout << "Move disk 1 from " << src << " to " << des << endl;
    }
    else
    {
        // Move n-1 disks from src to aux
        towerOfHanoi(n - 1, src, aux, des);
        // Move disk n from src to des
        cout << "Move disk " << n << " from " << src << " to " << des << endl;
        // Move n-1 disks from aux to des
        towerOfHanoi(n - 1, aux, des, src);
    }
}

int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}