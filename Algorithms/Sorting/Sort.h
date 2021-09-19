#ifndef SORT_H
#define SORT_H

namespace sort
{
	/*Helper function*/

	// Swap two integer
	void swap(int&, int&);
	// Ascending order
	bool ascend(const int&, const int&);
	// Descending order
	bool descend(const int&, const int&);

	/*Selection sort*/

	// Sorting array using selection sort algorithm
	void selectionSort(int[], int);

	/*Heap sort*/

	void shift_down(int[], int, int);
	// Sorting array using heap sort algorithm
	void heapSort(int[], int);

	/*Bubble sort*/

	// Sorting array using bubble sort algorithm
	void bubbleSort(int[], int);

	/*Shaker sort*/

	// Sorting array using shaker sort algorithm
	void shakerSort(int[], int);

	/*Insertion sort*/

	// Sorting array using insertion sort algorithm
	void insertionSort(int[], int);

	/*Shell sort*/

	// Sorting array using shell sort algorithm
	void shellSort(int[], int);

	/*Quick sort*/

	// Making partition for array recursively
	void partition(int[], int, int);
	// Making partition for array using Hoare's method
	int HoarePartition(int[], int, int);
	// Making partition for array using Lomuto's method
	int LomutoPartition(int[], int, int);
	// Sort each partition
	void sortPartition(int[], int, int);
	// Sorting array using quick sort algorithm
	void quickSort(int[], int);
	// Implement quick sort algorithm without using recursive
	void interativeQuickSort(int[], int);

	/*Merge sort*/

	// Merge two run in order
	void merge(int[], int[], int, int, int);
	// Sort each run
	void sortRun(int[], int[], int, int);
	// Sorting array using merge sort algorithm
	void mergeSort(int[], int);
	// Implement merge sort algorithm without using recursive
	void interativeMergeSort(int[], int);

	/*Radix sort*/

	//MSD radix sort
	void MSD_sort(int[], int, int, int);
	// Sorting array using LSD radix sort algorithm
	void radixSort_LSD(int[], int);
	//
	void radixSort_MSD(int[], int);

	/*Counting sort*/

	// Sorting array using counting sort algorithm
	void countingSort(int[], int);

}
#endif // !SORT_H