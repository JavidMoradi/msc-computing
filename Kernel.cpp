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

int main()
{
	// Input arrays
	const int size = 21;

	std::vector<int> arr1(size);
	fillArrayWithRandomIntegers(arr1, size, 0, INT_MAX);
	
	std::vector<int> arr2(arr1);
	std::vector<int> arr3(arr1);
	std::vector<int> arr4(arr1);
	std::vector<int> arr5(arr1);
	std::vector<int> arr6(arr1);

	std::vector<int> arrM(arr1);
	std::vector<int> arrR(arr1);

	bool shouldSort = false;
	bool isReversed = false;

	// Regular Quicksort
	if (shouldSort)
		sortVector(arr1);
	if (isReversed)
		reverseVector(arr1);

	std::cout << "Regular Quicksort" << std::endl;

	Quicksort qs;

	auto start = std::chrono::high_resolution_clock::now();

	/*std::cout << "Memory usage before allocation:" << std::endl;
	printMemoryUsage();*/

	qs.sort(arr1, 0, size - 1);

	//std::cout << "\nMemory usage after allocation:" << std::endl;
	//printMemoryUsage();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr1, size) << std::endl;

	printDashLines();

	arr1.clear();
	arr1.shrink_to_fit();

	// Mergesort
	Mergesort ms;

	if (shouldSort)
		sortVector(arrM);
	if (isReversed)
		reverseVector(arrM);

	std::cout << "Regular Mergesort" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	ms.sort(arrM, 0, size - 1);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arrM, size) << std::endl;

	printDashLines();

	arrM.clear();
	arrM.shrink_to_fit();

	// Radixsort
	Radixsort rs;

	if (shouldSort)
		sortVector(arrR);
	if (isReversed)
		reverseVector(arrR);

	std::cout << "Regular Radixsort" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	rs.sort(arrR);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arrR, size) << std::endl;

	printDashLines();

	arrR.clear();
	arrR.shrink_to_fit();

	// Three-pivot Quicksort
	TPquicksort tp;

	if (shouldSort)
		sortVector(arr2);
	if (isReversed)
		reverseVector(arr2);

	std::cout << "Three-pivot Quicksort" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	/*std::cout << "Memory usage before allocation:" << std::endl;
	printMemoryUsage();*/

	tp.threePivotSort(arr2, 0, size - 1);

	/*std::cout << "\nMemory usage after allocation:" << std::endl;
	printMemoryUsage();*/

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr2, size) << std::endl;

	printDashLines();

	arr2.clear();
	arr2.shrink_to_fit();

	// Naive multi-threaded Three-pivot Quicksort
	if (shouldSort)
		sortVector(arr3);
	if (isReversed)
		reverseVector(arr3);

	std::cout << "Naive multi-threaded Three-pivot Quicksort" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	//std::cout << "Memory usage before allocation:" << std::endl;
	//printMemoryUsage();

	tp.naive_mt_threePivotSort(arr3, size);

	//std::cout << "\nMemory usage after allocation:" << std::endl;
	//printMemoryUsage();

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr3, size) << std::endl;

	printDashLines();

	arr3.clear();
	arr3.shrink_to_fit();

	// Naive multi-threaded Three-pivot Quicksort (test for various k values)
	/*for (int k = 1; k <= 16; k++) {
		std::vector<int> arr4(size);

		fillArrayWithRandomIntegers(arr4, size, 0, INT_MAX);

		std::cout << "K=" << k << std::endl;

		start = std::chrono::high_resolution_clock::now();

		tp.naive_mt_threePivotSort(arr4, size, k);

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		std::cout << std::endl;
		std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
		std::cout << std::endl;

		std::cout << "Is array sorted? " << isArraySorted(arr3, size) << std::endl;

		printDashLines();
	}*/

	// Data Stream Test
	//simpleStreamTest(size);

	// Parallel TP Quicksort
	if (shouldSort)
		sortVector(arr4);
	if (isReversed)
		reverseVector(arr4);

	std::cout << "Parallel Three-pivot Quicksort" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	tp.parallelTPquicksort(arr4, 0, size - 1);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr4, size) << std::endl;

	printDashLines();

	arr4.clear();
	arr4.shrink_to_fit();

	// TP Quicksort with Cache
	if (shouldSort)
		sortVector(arr5);
	if (isReversed)
		reverseVector(arr5);

	std::cout << "Three-pivot Quicksort with Cache" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortWithCache(arr5, 0, size - 1);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr5, size) << std::endl;

	printDashLines();

	arr5.clear();
	arr5.shrink_to_fit();

	// TP Quicksort with Alternative Pivot Choice
	if (shouldSort)
		sortVector(arr6);
	if (isReversed)
		reverseVector(arr6);

	std::cout << "Three-pivot Quicksort with Alternative Pivot Choice" << std::endl;

	start = std::chrono::high_resolution_clock::now();

	tp.threePivotSortAltPvt(arr6, 0, size - 1);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	std::cout << std::endl;
	std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl;

	std::cout << "Is array sorted? " << isArraySorted(arr6, size) << std::endl;

	printDashLines();

	arr6.clear();
	arr6.shrink_to_fit();

	return 0;
}
