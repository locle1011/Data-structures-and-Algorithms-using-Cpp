#include <iostream>
using namespace std;

void linearSearch(int *arr, int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            cout << "Found at index: " << i << endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

void binarySearch(int *arr, int n, int key)
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (arr[mid] < key)
        {
            l = mid + 1;
        }
        else if (arr[mid] > key)
        {
            r = mid - 1;
        }
        else
        {
            cout << "Found at index: " << mid << endl;
            return;
        }
    }
    cout << "Not found" << endl;
}

int main()
{
}