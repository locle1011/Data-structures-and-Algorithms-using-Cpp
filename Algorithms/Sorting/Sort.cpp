#include "Sort.h"
#include <stack>
#include <utility>
using namespace std;
//using namespace sort;

#define mp(a,b) make_pair(a,b)
#define max(a,b) (((a)>=(b))?(a):(b))
#define min(a,b) (((a)<=(b))?(a):(b))

/*Helper function*/
void sort::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

bool sort::ascend(const int& a, const int& b)
{
	return a < b;
}

bool sort::descend(const int& a, const int& b)
{
	return a > b;
}

/*Selection sort*/
void sort::selectionSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		int lowIndex = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[lowIndex])
				lowIndex = j;
		}
		swap(arr[i], arr[lowIndex]);
	}
}

/*Heap sort*/
void sort::shift_down(int arr[], int high, int low)
{
	int parent = high;
	int child = 2 * parent + 1;
	int parentKey = arr[parent];
	while (child <= low) {
		if (child < low) {
			if (arr[child + 1] > arr[child])
				child++;
		}
		if (arr[child] > parentKey) {
			arr[parent] = arr[child];
			parent = child;
			child = 2 * parent + 1;
		}
		else break;
	}
	arr[parent] = parentKey;
}

void sort::heapSort(int arr[], int n)
{
	//Phrase 1: making a heap from arr
	for (int i = n / 2 - 1; i >= 0; i--) {
		shift_down(arr, i, n - 1);
	}
	//Phrase 2: extract root from max heap once by once
	for (int i = n - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		shift_down(arr, 0, i - 1);
	}
}

/*Bubble sort*/
void sort::bubbleSort(int arr[], int n)
{
	for (int i = n - 1; i > 0; i--) {
		bool flag = true;
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
			break;
	}
}

void sort::shakerSort(int arr[], int n)
{
	int high = 0;
	int low = n - 1;
	int lastSwap = 0;
	while (high < low) {
		//top-down
		for (int i = high; i < low; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				lastSwap = i;
			}
		}
		low = lastSwap;
		//bottom-up
		for (int i = low; i > high; i--) {
			if (arr[i] < arr[i - 1]) {
				swap(arr[i], arr[i - 1]);
				lastSwap = i;
			}
		}
		high = lastSwap;
	}
}

void sort::insertionSort(int arr[], int n)
{
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && key < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void sort::shellSort(int arr[], int n)
{
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; i++) {
			int key = arr[i];
			int j = i - gap;
			while (j >= 0 && key < arr[j]) {
				arr[j + gap] = arr[j];
				j -= gap;
			}
			arr[j + gap] = key;
		}
	}
}

void sort::partition(int arr[], int start, int end)
{
	int i = start;
	int j = end;
	int pivot = arr[(i + j) / 2];
	while (i < j) {
		while (arr[i] < pivot) {
			i++;
		}
		while (pivot < arr[j]) {
			j--;
		}
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	if (start < j) {
		partition(arr, start, j);
	}
	if (i < end) {
		partition(arr, i, end);
	}
}

int sort::HoarePartition(int arr[], int start, int end)
{
	int i = start;
	int j = end;
	int pivot = arr[(i + j) / 2];
	while (i < j) {
		while (arr[i] < pivot) {
			i++;
		}
		while (pivot < arr[j]) {
			j--;
		}
		if (i < j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	}
	return j;
}

int sort::LomutoPartition(int arr[], int start, int end)
{
	int i = start;
	int pivot = arr[end];
	for (int j = start; j < end; j++) {
		if (arr[j] < pivot) {
			swap(arr[i], arr[j]);
			i++;
		}
	}

	/*Swap arr[end] and arr[i] without calling swap() function*/
	//arr[end]=arr[i];
	//arr[i]=pivot;

	swap(arr[i], arr[end]);
	return i;
}



void sort::sortPartition(int arr[], int start, int end)
{
	if (start < end) {
		/*Hoare's method*/
		int k = HoarePartition(arr, start, end);
		sortPartition(arr, start, k);

		/*Lomuto's method*/
		/*int k = LomutoPartition(arr, start, end);
		sortPartition(arr, start, k - 1);*/
		sortPartition(arr, k + 1, end);
	}
}

void sort::quickSort(int arr[], int n)
{
	/*Making partition with recursive*/
	partition(arr, 0, n - 1);

	/*Making partition without using recursive*/
	//sortPartition(arr, 0, n - 1);
}

void sort::interativeQuickSort(int arr[], int n)
{
	stack<pair<int, int>> st;
	st.push(mp(0, n - 1));
	while (!st.empty())
	{
		int start = st.top().first;
		int end = st.top().second;
		st.pop();
		while (start < end) {
			int i = start, j = end;
			int pivot = arr[(i + j) / 2];
			while (i < j) {
				while (arr[i] < pivot) {
					i++;
				}
				while (pivot < arr[j]) {
					j--;
				}
				if (i <= j) {
					swap(arr[i], arr[j]);
					i++;
					j--;
				}
			}
			if (i < end) {
				st.push(mp(i, end));
			}
			end = j;
		}
	}
}

/// <summary>
/// Merge two run in order
/// </summary>
/// <param name="arr:"> Main array</param>
/// <param name="temp:"> Temporary array</param>
/// <param name="start:"> Start index of first run</param>
/// <param name="mid:"> Start index of second run</param>
/// <param name="end:"> End index of second run</param>
void sort::merge(int arr[], int temp[], int start, int mid, int end)
{
	int i = start; // index of first run
	int j = mid; // index of second run
	int count = 0; // count element in temp
	while (i < mid && j <= end) {
		if (arr[i] < arr[j]) {
			temp[count] = arr[i];
			i++;
		}
		else {
			temp[count] = arr[j];
			j++;
		}
		count++;
	}

	while (i < mid) {
		temp[count] = arr[i];
		count++;
		i++;
	}

	while (j <= end) {
		temp[count] = arr[j];
		count++;
		j++;
	}
	for (int k = 0; k < count; k++) {
		arr[start + k] = temp[k];
	}
}

void sort::sortRun(int arr[], int temp[], int start, int end)
{
	if (start < end) {
		int mid = (start + end) / 2;
		sortRun(arr, temp, start, mid);
		sortRun(arr, temp, mid + 1, end);
		merge(arr, temp, start, mid + 1, end);
	}
}

void sort::mergeSort(int arr[], int n)
{
	int* temp = new int[n];
	sortRun(arr, temp, 0, n - 1);
	delete[] temp;
}

void sort::interativeMergeSort(int arr[], int n)
{
	int* temp = new int[n];
	for (int runLength = 1; runLength < n; runLength *= 2) {
		int count = 0;//count element in temp
		int left_index = 0;
		int not_merge = n;//number of not merge element
		while (not_merge > 0) {
			int count_left, count_right;
			count_left = min(runLength, not_merge);
			not_merge -= count_left;
			int right_index = left_index + count_left;
			count_right = min(runLength, not_merge);
			not_merge -= count_right;
			while (count_left > 0 && count_right > 0) {
				if (arr[left_index] < arr[right_index]) {
					temp[count] = arr[left_index];
					left_index++;
					count_left--;
				}
				else {
					temp[count] = arr[right_index];
					right_index++;
					count_right--;
				}
				count++;
			}
			while (count_left > 0) {
				temp[count] = arr[left_index];
				left_index++;
				count_left--;
				count++;
			}
			while (count_right > 0) {
				temp[count] = arr[right_index];
				right_index++;
				count_right--;
				count++;
			}
			left_index += runLength;
		}
		for (int i = 0; i < n; i++) {
			arr[i] = temp[i];
		}
	}
	delete[] temp;
}

void sort::radixSort_LSD(int arr[], int n)
{
	const int BASE = 10;
	int* temp = new int[n];
	int maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		maxVal = max(maxVal, arr[i]);
	}
	int bucket[BASE] = { 0 };
	for (int weight = 1; maxVal / weight > 0; weight *= BASE) {
		for (int i = 0; i < BASE; i++) {
			bucket[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			int key = (arr[i] / weight) % BASE;
			bucket[key]++;
		}
		for (int i = 1; i < BASE; i++) {
			bucket[i] += bucket[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			int key = (arr[i] / weight) % BASE;
			bucket[key]--;
			temp[bucket[key]] = arr[i];
		}
		for (int i = 0; i < n; i++) {
			arr[i] = temp[i];
		}
	}
	delete[] temp;
}

void sort::radixSort_MSD(int arr[], int n)
{
	int weight = 1;
	int maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		maxVal = max(maxVal, arr[i]);
	}
	while (maxVal / weight > 0) {
		weight *= 10;
	}
	weight /= 10;
	MSD_sort(arr, 0, n - 1, weight);
}

void sort::MSD_sort(int arr[], int low, int high, int weight)
{
	if (low < high) {
		int* temp = new int[high - low + 1];
		int bucket[10 + 1] = { 0 };
		for (int i = low; i <= high; i++) {
			int key = (arr[i] / weight) % 10;
			bucket[key]++;
		}
		for (int i = 1; i < 10 + 1; i++) {
			bucket[i] += bucket[i - 1];
		}
		for (int i = low; i <= high; i++) {
			int key = (arr[i] / weight) % 10;
			bucket[key]--;
			temp[bucket[key]] = arr[i];
		}

		for (int i = low; i <= high; i++) {
			arr[i] = temp[i - low];
		}
		delete[] temp;

		for (int i = 0; i < 10; i++) {
			MSD_sort(arr, low + bucket[i], low + bucket[i + 1] - 1, weight / 10);
		}
	}
}

void sort::countingSort(int arr[], int n)
{
	int* temp = new int[n];
	int maxVal, minVal;
	maxVal = minVal = arr[0];
	for (int i = 1; i < n; i++) {
		maxVal = max(maxVal, arr[i]);
		minVal = min(minVal, arr[i]);
	}
	int range = maxVal - minVal + 1;
	int* count = new int[range];
	for (int i = 0; i < range; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		count[arr[i] - minVal]++;
	}

	for (int i = 1; i < range; i++) {
		count[i] += count[i - 1];
	}

	for (int i = 0; i < n; i++) {
		count[arr[i]-minVal]--;
		temp[count[arr[i] - minVal]] = arr[i];
	}

	for (int i = 0; i < n; i++) {
		arr[i] = temp[i];
	}

	delete[] temp, count;
}
