#include <stdio.h>
#include <iostream>
#include <chrono>
#include <string>
#include <Windows.h>
#include <Psapi.h>

#include "Quicksort.h"
#include "TPquicksort.h"
#include "Mergesort.h"
#include "Radixsort.h"
#include "TPquicksortStr.h"
#include "Shiftsort.h"

std::string generateRandomString(int length) {
	const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string randomString;
	for (int i = 0; i < length; ++i) {
		randomString += characters[std::rand() % characters.size()];
	}
	return randomString;
}

void fillArrayWithRandomStrings(std::vector<std::string>& array, int size, int stringLength) {
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	array.resize(size); // Resize the vector to the desired size
	for (int i = 0; i < size; ++i) {
		array[i] = generateRandomString(stringLength);
	}
}

void fillArrayWithRandomIntegers(std::vector<int>& array, int size, int min, int max)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));

	for (int i = 0; i < size; ++i) {
		array[i] = min + std::rand() % (max - min + 1);
	}
}

void printArray(std::vector<int> arr, int size)
{
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

std::string isArraySorted(std::vector<int> arr, int size)
{
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1]) {
			std::cout << "Occurred here: " << arr[i] << ", " << arr[i + 1] << std::endl;
			return "false";
		}
	}
	return "true";
}

std::string isArraySortedStr(const std::vector<std::string>& arr, int size)
{
	for (int i = 0; i < size - 1; ++i) {
		if (arr[i] > arr[i + 1]) {
			std::cout << "Occurred here: " << arr[i] << ", " << arr[i + 1] << std::endl;
			return "false";
		}
	}
	return "true";
}

void printDashLines() {
	std::cout << "----------------------------" << std::endl;
}

void sortVector(std::vector<int>& vector) {
	std::sort(vector.begin(), vector.end());
}

void reverseVector(std::vector<int>& vector) {
	std::reverse(vector.begin(), vector.end());
}

void simpleStreamTest(int size) {
	const int ITERATION = 5;
	int duration1 = 0;
	int duration2 = 0;

	for (int i = 0; i < ITERATION; i++) {
		std::vector<int> original(size);
		fillArrayWithRandomIntegers(original, original.size(), 0, INT_MAX);

		std::vector<int> copy = original;
		std::sort(copy.begin(), copy.end());
		std::swap(copy[copy.size() - 1], copy[copy.size() - 2]);

		// Sorting original
		int originalSize = original.size();

		TPquicksort tp;

		auto start = std::chrono::high_resolution_clock::now();

		tp.threePivotSort(original, 0, originalSize - 1);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << std::endl;
		std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
		std::cout << std::endl;

		std::cout << "Is array sorted? " << isArraySorted(original, original.size()) << std::endl;

		duration1 += duration.count();

		// Sorting copy
		int copySize = copy.size();

		start = std::chrono::high_resolution_clock::now();

		tp.threePivotSort(copy, 0, copySize - 1);

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << std::endl;
		std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
		std::cout << std::endl;

		std::cout << "Is array sorted? " << isArraySorted(original, copy.size()) << std::endl;

		duration2 += duration.count();
	}
	
	std::cout << "Random Duration 1: " << duration1 << std::endl;
	std::cout << "Stream Duration 2: " << duration2 << std::endl;
}

long long quicksortTest(std::vector<int>& arr, int size) {
	Quicksort qs;

	std::cout << "Regular Quicksort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	qs.sort(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long mergesortTest(std::vector<int>& arr, int size) {
	Mergesort ms;

	std::cout << "Regular Mergesort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	ms.sort(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long radixsortTest(std::vector<int>& arr, int size) {
	Radixsort rs;

	std::cout << "Regular Radixsort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	rs.sort(arr);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotQuicksortTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSort(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long naiveMultiThreadSortTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Naive multi-threaded Three-pivot Quicksort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.naive_mt_threePivotSort(arr, size);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();
	
	return duration.count();
}

void naiveMultiThreadSortTestForK(int size) {
	TPquicksort tp;
	
	for (int k = 1; k <= 16; k++) {
		std::vector<int> arr4(size);

		fillArrayWithRandomIntegers(arr4, size, 0, INT_MAX);

		std::cout << "K=" << k << std::endl;

		auto start = std::chrono::high_resolution_clock::now();

		tp.naive_mt_threePivotSort(arr4, size, k);

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << std::endl;
		std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
		std::cout << std::endl;

		std::cout << "Is array sorted? " << isArraySorted(arr4, size) << std::endl;

		printDashLines();
	}
}

long long parallelThreepivotSortTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Parallel Three-pivot Quicksort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.parallelTPquicksort(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotSortWithCacheTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Cache" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortWithCache(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotSortAltPivotTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Alternative Pivot Choice" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortAltPvt(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotQuicksortTestStr(std::vector<std::string>& arr, int size) {
	TPquicksortStr tps;

	std::cout << "Three-pivot Quicksort (String)" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tps.threePivotSortStr(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	printDashLines();

	return duration.count();
}

long long quicksortTestStr(std::vector<std::string>& arr, int size) {
	TPquicksortStr tps;

	std::cout << "Quicksort (String)" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tps.quicksortStr(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	printDashLines();

	return duration.count();
}

void threepivotQuicksortWithDifferentInsertionSortThresholdTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Varying Insertion Sort Threshold Value" << std::endl;

	std::vector<int> _arr = arr;
	const int ITERATION_COUNT = 5;

	for (int i = 5; i <= 100; i++) {
		auto sum = 0;
		for (int j = 0; j < ITERATION_COUNT; j++) {
			arr = _arr;

			auto start = std::chrono::high_resolution_clock::now();

			tp.threePivotSort(arr, 0, size - 1, i);

			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

			//std::cout << std::endl;
			//std::cout << "THRESHOLD VALUE: " << i << ", Time Taken: " << duration.count() << " microseconds" << std::endl;
			//std::cout << std::endl;
			sum += duration.count();
		}
		std::cout << "THRESHOLD VALUE: " << i << ", Avg Time Taken: " << sum / ITERATION_COUNT << " microseconds" << std::endl;
	}

	printDashLines();
}

long long threepivotSortWithCacheHeapTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Cache Heap" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortWithCacheHeap(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotSortWithCacheArrayTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Cache Array" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortWithCacheArray(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long threepivotSortWithCacheArrayHeapTest(std::vector<int>& arr, int size) {
	TPquicksort tp;

	std::cout << "Three-pivot Quicksort with Cache Array Heap" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortWithCacheArrayHeap(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

long long shiftsortTest(std::vector<int>& arr, int size) {
	Shiftsort ss;

	std::cout << "Shift Sort" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	ss.sort(arr, size);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr, size) << std::endl;

	printDashLines();

	return duration.count();
}

void threepivotQuicksortTestStr(std::vector<std::string>& arr, int size) {
	TPquicksortStr tps;

	std::cout << "Three-pivot Quicksort (String)" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tps.threePivotSortStr(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	printDashLines();
}

void quicksortTestStr(std::vector<std::string>& arr, int size) {
	TPquicksortStr tps;

	std::cout << "Quicksort (String)" << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	tps.quicksortStr(arr, 0, size - 1);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	printDashLines();
}

int main()
{
	// Input arrays
	const int size = 1e7;

	std::vector<int> arr1(size);
	fillArrayWithRandomIntegers(arr1, size, 0, INT_MAX);

	std::vector<int> _arr1 = arr1;

	bool shouldSort = false;
	bool isReversed = false;

	if (shouldSort)
		sortVector(arr1);
	if (isReversed)
		reverseVector(arr1);

	std::vector<int> _arr1 = arr1;

	int iteration = 5;
	auto sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0, sum6 = 0, sum7 = 0, sum8 = 0, sum9 = 0, sum10 = 0, sum11 = 0, sum12 = 0;

	for (int i = 0; i < iteration; i++) {
		// Regular Quicksort
		arr1 = _arr1;
		sum1 += quicksortTest(arr1, size);

		// Mergesort
		arr1 = _arr1;
		sum2 += mergesortTest(arr1, size);

		// Radixsort
		arr1 = _arr1;
		sum3 += radixsortTest(arr1, size);

		// Three-pivot Quicksort
		arr1 = _arr1;
		sum4 += threepivotQuicksortTest(arr1, size);

		// Naive multi-threaded Three-pivot Quicksort
		arr1 = _arr1;
		sum5 += naiveMultiThreadSortTest(arr1, size);

		// Naive multi-threaded Three-pivot Quicksort (test for various k values)
		// naiveMultiThreadSortTestForK(size);

		// Data Stream Test
		//simpleStreamTest(size);

		// Parallel TP Quicksort
		arr1 = _arr1;
		sum6 += parallelThreepivotSortTest(arr1, size);

		// TP Quicksort with Cache
		arr1 = _arr1;
		sum7 += threepivotSortWithCacheTest(arr1, size);

		// TP Quicksort with Alternative Pivot Choice
		arr1 = _arr1;
		sum8 += threepivotSortAltPivotTest(arr1, size);

		// TP Quicksort with Cache Heap
		arr1 = _arr1;
		sum9 += threepivotSortWithCacheHeapTest(arr1, size);

		// TP Quicksort with Cache Array
		arr1 = _arr1;
		sum10 += threepivotSortWithCacheArrayTest(arr1, size);

		// TP Quicksort with Cache Array Heap
		arr1 = _arr1;
		sum11 += threepivotSortWithCacheArrayHeapTest(arr1, size);

		// Shift sort
		arr1 = _arr1;
		sum12 += shiftsortTest(arr1, size);
	}
	std::cout << "Quicksort: "		<< sum1 / iteration << std::endl;
	std::cout << "TP quicksort: "	<< sum4 / iteration << std::endl;
	std::cout << "Naive MT: "		<< sum5 / iteration << std::endl;
	std::cout << "Parallel MT: "	<< sum6 / iteration << std::endl;
	std::cout << "Cache TP: "		<< sum7 / iteration << std::endl;
	std::cout << "Alt pivot: "		<< sum8 / iteration << std::endl;
	std::cout << "Mergesort: "		<< sum2 / iteration << std::endl;
	std::cout << "Radixsort: "		<< sum3 / iteration << std::endl;
	std::cout << "Cache Heap TP: "	<< sum9 / iteration << std::endl;
	std::cout << "Cache Array TP: " << sum10 / iteration << std::endl;
	std::cout << "Cache Arr H TP: " << sum11 / iteration << std::endl;
	std::cout << "Shift sort: " 	<< sum12 / iteration << std::endl;

	// Data Stream Test
	simpleStreamTest(size);

	// String Sortings
	int sizeStr = 1e7;
	int length = 5;
	std::vector<std::string> arr2;

	fillArrayWithRandomStrings(arr2, sizeStr, length);

	bool shouldSortStr	  = true;   
	bool shouldReverseStr = true;  

	if (shouldSortStr) {
		TPquicksortStr tps;
		tps.quicksortStr(arr2, 0, sizeStr - 1);
	}
	if (shouldReverseStr) {
		std::reverse(arr2.begin(), arr2.end());
	}
	
	std::vector<std::string> _arr2 = arr2;
	auto sum1 = 0;
	auto sum2 = 0;
	int iter = 5;


	for (int i = 0; i < iter; i++) {
		arr2 = _arr2;
		//sum1 += quicksortTestStr(arr2, sizeStr);
	
		arr2 = _arr2;
		sum2 += threepivotQuicksortTestStr(arr2, sizeStr);
	}
	std::cout << "Avg1: " << sum1/iter << std::endl;
	std::cout << "Avg2: " << sum2/iter << std::endl;

	// Insertion Sort Threshold Test
	threepivotQuicksortWithDifferentInsertionSortThresholdTest(arr1, size);

	// String Sortings
	int sizeStr = 20;
	int length = 5;
	std::vector<std::string> arr2;

	fillArrayWithRandomStrings(arr2, sizeStr, length);

	bool shouldSortStr = false;
	bool shouldReverseStr = false;

	if (shouldSortStr) {
		TPquicksortStr tps;
		tps.quicksortStr(arr2, 0, sizeStr - 1);
	}
	if (shouldReverseStr) {
		std::reverse(arr2.begin(), arr2.end());
	}
	
	std::vector<std::string> _arr2 = arr2;

	quicksortTestStr(arr2, sizeStr);
	
	arr2 = _arr2;
	threepivotQuicksortTestStr(arr2, sizeStr);

	return 0;
}
