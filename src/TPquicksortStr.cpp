#include "TPquicksortStr.h"

TPquicksortStr::TPquicksortStr() {}

TPquicksortStr::~TPquicksortStr() {}

void TPquicksortStr::quicksortStr(std::vector<std::string>& arr, int start, int end)
{
	// base case
	if (start >= end)
		return;

	// partitioning the array
	int p = partition(arr, start, end);

	// Sorting the left part
	quicksortStr(arr, start, p - 1);

	// Sorting the right part
	quicksortStr(arr, p + 1, end);
}

void TPquicksortStr::threePivotSortStr(std::vector<std::string>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSortStr(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (compareStr(A[left], A[mid]))
		std::swap(A[left], A[mid]);
	if (compareStr(A[mid], A[right]))
		std::swap(A[mid], A[right]);
	if (compareStr(A[left], A[mid]))
		std::swap(A[left], A[mid]);

	std::string p = A[left];
	std::string q = A[mid];
	std::string r = A[right];

	std::swap(A[left + 1], A[mid]);

	int a = left + 2;
	int b = left + 2;
	int c = right - 1;
	int d = right - 1;

	while (b <= c)
	{
		while (!compareStr(A[b], q) && b <= c)
		{
			if (!compareStr(A[b], p))
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (compareStr(A[c], q) && b <= c)
		{
			if (compareStr(A[c], r))
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (compareStr(A[b], r))
			{
				if (compareStr(A[c], p))
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (!compareStr(A[c], p))
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSortStr(A, left, a - 1);
	threePivotSortStr(A, a + 1, b - 1);
	threePivotSortStr(A, b + 1, d - 1);
	threePivotSortStr(A, d + 1, right);
}

int TPquicksortStr::partition(std::vector<std::string>& arr, int start, int end)
{
	std::string pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (compareStr(arr[i], pivot))
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = start + count;
	std::swap(arr[pivotIndex], arr[start]);

	// Sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) 
	{
		while (compareStr(arr[i], pivot)) {
			i++;
		}

		while (!compareStr(arr[j], pivot)) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			std::swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

// Compares str1 and str2
// returns true if str1 is alphabetically bigger than str2
bool TPquicksortStr::compareStr(std::string& str1, std::string& str2)
{
	return str1 <= str2;
}

void TPquicksortStr::insertionSortStr(std::vector<std::string>& arr, int start, int end)
{
	for (int i = start + 1; i <= end; ++i) {
		std::string key = arr[i];
		int j = i - 1;
		while (j >= start && compareStr(arr[j], key)) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}
