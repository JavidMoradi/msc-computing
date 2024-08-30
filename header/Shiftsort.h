#pragma once
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include "Radixsort.h"

class Shiftsort
{
public:
	void sort(std::vector<int>& arr, int size);
	void shiftsort(std::vector<int>& arr, int left, int right, int maxdepth);

	void threePivotSort(std::vector<int>& A, int left, int right, int maxdepth);
	void insertionSort(std::vector<int>& arr, int start, int end);
	
private:
	const int INSERTION_SORT_THRESHOLD = 10;
};

