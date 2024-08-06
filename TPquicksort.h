#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include <mutex>

struct Cache {
	int a;
	int b;
	int c;
	int d;
};

class TPquicksort
{
public:
	TPquicksort();
	~TPquicksort();

	void threePivotSort(std::vector<int>& A, int left, int right);
	void naive_mt_threePivotSort(std::vector<int>& A, int size, int k = 8);
	void parallelTPquicksort(std::vector<int>& seq, int first, int last);
	void parallelKthPartition(std::vector<int>& seq, int last, int& part1, int& part2, int& part3, int& part4,
		int kTh1, int kTh2, int kTh3, int kTh4);
	void threePivotSortWithCache(std::vector<int>& A, int left, int right);
	void threePivotSortAltPvt(std::vector<int>& A, int left, int right);

	// Utility functions
	void insertionSort(std::vector<int>& arr, int start, int end);
	void mergeArrays(std::vector<int>& arr, int begin, int mid, int end);
	int calculatePivot(const std::vector<int>& arr, int begin, int end);

private:
	const int INSERTION_SORT_THRESHOLD = 10;
	std::mutex mtx;
};
