#include "Shiftsort.h"

void Shiftsort::sort(std::vector<int>& arr, int size)
{
	int maxdepth = std::floor(std::log2(size)) * 2;
	shiftsort(arr, 0, size - 1, maxdepth);
}

void Shiftsort::shiftsort(std::vector<int>& arr, int left, int right, int maxdepth)
{
	int n = right - left + 1;

	if (n <= INSERTION_SORT_THRESHOLD) {
		insertionSort(arr, left, right);
	}
	else if (maxdepth == 0) {
		Radixsort rs;
		rs.sortRange(arr, left, right);
	}
	else {
		threePivotSort(arr, left, right, maxdepth);
	}
}

void Shiftsort::threePivotSort(std::vector<int>& A, int left, int right, int maxdepth)
{
	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	int a = left + 2;
	int b = left + 2;
	int c = right - 1;
	int d = right - 1;

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
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
				if (A[c] < p)
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

	shiftsort(A, left, a - 1, maxdepth - 1);
	shiftsort(A, a + 1, b - 1, maxdepth - 1);
	shiftsort(A, b + 1, d - 1, maxdepth - 1);
	shiftsort(A, d + 1, right, maxdepth - 1);
}

void Shiftsort::insertionSort(std::vector<int>& arr, int start, int end)
{
	for (int i = start + 1; i <= end; ++i) {
		int key = arr[i];
		int j = i - 1;
		while (j >= start && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}
