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

void interpolationSearch(int *arr, int n, int key)
{
    int l = 0, r = n - 1;
    while (l <= r && key >= arr[l] && key <= arr[r])
    {
        int pos = l + (key - arr[l]) * (double(r - l) / (arr[r] - arr[l]));
        if (arr[pos] == key)
        {
            cout << "Found at index: " << pos << endl;
            return;
        }
        else if (arr[pos] > key)
        {
            r = pos - 1;
        }
        else
        {
            l = pos + 1;
        }
    }
    cout << "Not found" << endl;
}

int main()
{
    int arr[] = {1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 12, 14, 15, 16};
    int n = sizeof(arr) / sizeof(int);
    int key = 16;
    linearSearch(arr, n, key);
    binarySearch(arr, n, key);
    interpolationSearch(arr, n, key);
}