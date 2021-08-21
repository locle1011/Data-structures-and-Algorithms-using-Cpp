#include <iostream>
using namespace std;

#define abs(x) ((x >= 0) ? (x) : -(x))
#define eps 1e-8

/* Solve tower of Hanoi problem. */
void towerOfHanoi(int, int, int, int);
/* Find nth Fibonacci number. */
int fib(int);
/* Find GCD of two numbers. */
int gcd(int, int);
/* Find LCM of two numbers. */
int lcm(int, int);
/* Calculate n power of base. */
int pow(int, unsigned int);
/* Calulate factorial of a non-negative number. */
int factorial(unsigned int);
/* Recursively calculate square root of a non-negative number. */
float findSqrtUntils(double, double, double);
/* Calculate square root. */
float sqrt(float);

int main()
{
    // towerOfHanoi(3, 1, 3, 2);
    // cout << fib(6);
    // cout << gcd(2, 3) << " " << lcm(2, 3);
    // cout << pow(3, 2) << " " << factorial(5);
    cout.precision(10);
    cout << sqrt(2);
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

int gcd(int a, int b)
{
    /* Euclidean algorithm */
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    if (a == 0 || b == 0)
    {
        return 0;
    }
    return (a * b) / gcd(a, b);
}

int pow(int base, unsigned int power)
{
    /* Divide and conquer algorithm */
    if (power == 0)
    {
        return 1;
    }
    int temp = pow(base, power / 2);
    if (power % 2 == 0)
    {
        return temp * temp;
    }
    else
    {
        return base * temp * temp;
    }
}

int factorial(unsigned int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

float findSqrtUntils(double n, double lo, double hi)
{
    /* Binary search approach */
    double mid = (lo + hi) / 2;
    double mul = mid * mid;
    if (abs(mul - n) < eps)
    {
        return mid;
    }
    else if (mul < n)
    {
        return findSqrtUntils(n, mid, hi);
    }
    else
    {
        return findSqrtUntils(n, lo, mid);
    }
}

float sqrt(float n)
{
    return findSqrtUntils(n, 0, n);
}