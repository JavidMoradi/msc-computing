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

void printDashLines() {
	std::cout << "----------------------------" << std::endl;
}

void sortVector(std::vector<int>& vector) {
	std::sort(vector.begin(), vector.end());
}

void reverseVector(std::vector<int>& vector) {
	std::reverse(vector.begin(), vector.end());
}

void printMemoryUsage() {
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
		std::cout << "Memory usage: " << pmc.WorkingSetSize / 1024 << " KB" << std::endl;
	}
	else {
		std::cerr << "Failed to retrieve memory usage" << std::endl;
	}
}

void simpleStreamTest(int size) {
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
}

void quicksortTest(std::vector<int>& arr, int size) {
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
}

void mergesortTest(std::vector<int>& arr, int size) {
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
}

void radixsortTest(std::vector<int>& arr, int size) {
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
}

void threepivotQuicksortTest(std::vector<int>& arr, int size) {
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
}

void naiveMultiThreadSortTest(std::vector<int>& arr, int size) {
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

void parallelThreepivotSortTest(std::vector<int>& arr, int size) {
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
}

void threepivotSortWithCacheTest(std::vector<int>& arr, int size) {
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
}

void threepivotSortAltPivotTest(std::vector<int>& arr, int size) {
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
}

int main()
{
	// Input arrays
	const int size = 1e7;

	std::vector<int> arr1(size);
	fillArrayWithRandomIntegers(arr1, size, 0, INT_MAX);

	bool shouldSort = false;
	bool isReversed = false;

	if (shouldSort)
		sortVector(arr1);
	if (isReversed)
		reverseVector(arr1);

	// Regular Quicksort
	quicksortTest(arr1, size);

	// Mergesort
	mergesortTest(arr1, size);

	// Radixsort
	radixsortTest(arr1, size);

	// Three-pivot Quicksort
	threepivotQuicksortTest(arr1, size);

	// Naive multi-threaded Three-pivot Quicksort
	naiveMultiThreadSortTest(arr1, size);

	// Naive multi-threaded Three-pivot Quicksort (test for various k values)
	//naiveMultiThreadSortTestForK(size);

	// Data Stream Test
	//simpleStreamTest(size);

	// Parallel TP Quicksort
	parallelThreepivotSortTest(arr1, size);

	// TP Quicksort with Cache
	threepivotSortWithCacheTest(arr1, size);

	// TP Quicksort with Alternative Pivot Choice
	threepivotSortAltPivotTest(arr1, size);

	return 0;
}
