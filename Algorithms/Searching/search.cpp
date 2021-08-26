#include <iostream>
#include <cmath>
using namespace std;

#define min(a, b) ((a < b) ? (a) : (b))

// Find key in arr, print index of key if it is present else print "Not found".
// Time complexity: O(N).
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

// Find key in arr, print index of key if it is present else print "Not found".
// Time complexity: O(logN)
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
        else // arr[mid]==key
        {
            cout << "Found at index: " << mid << endl;
            return;
        }
    }
    // We reach here when key is not in arr.
    cout << "Not found" << endl;
}

// Find key in arr, print index of key if it is present else print "Not found".
// Time complexity: O(log(logN))
void interpolationSearch(int *arr, int n, int key)
{
    int l = 0, r = n - 1;
    // If key is in arr, it must be in range defined by corner values
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
        else // arr[pos] < key
        {
            l = pos + 1;
        }
    }
    cout << "Not found" << endl;
}

// Find key in arr, print index of key if it is present else print "Not found".
// Time complexity: O(sqrt(N))
void jumpSearch(int *arr, int n, int key)
{
    // Find step to jump
    int step = sqrt(n);
    // pos-1 is the last index of first block
    int pos = step;
    // Find the block where key is in
    while (arr[min(pos, n) - 1] < key)
    {
        pos += step;
        if (pos >= n + step)
        {
            cout << "Not found" << endl;
            return;
        }
    }
    // lo is the first index of the block we found
    int lo = (pos > step) ? pos - step : 0;
    // Linear search until we find key or arr[pos]<key
    while (arr[pos] > key)
    {
        pos--;
        if (pos < lo)
        {
            cout << "Not found" << endl;
            return;
        }
    }
    if (arr[pos] == key)
    {
        cout << "Found at index: " << pos << endl;
    }
    else // arr[pos]<key
    {
        cout << "Not found" << endl;
    }
}

int main()
{
    int arr[] = {1, 2, 2, 3, 4, 4, 5, 6, 7, 8, 9, 9, 9, 10, 11, 12, 12, 14, 15, 16};
    int n = sizeof(arr) / sizeof(int);
    int key = 8;
    linearSearch(arr, n, key);
    binarySearch(arr, n, key);
    interpolationSearch(arr, n, key);
    jumpSearch(arr, n, key);
}