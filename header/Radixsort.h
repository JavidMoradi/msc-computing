#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Radixsort
{
public:
	Radixsort();
	~Radixsort();

	void sort(std::vector<int>& vec);
	void countSort(std::vector<int>& vec, int exp);	

	void sortRange(std::vector<int>& vec, int left, int right);
	void countSortRange(std::vector<int>& vec, int left, int right, int exp);
	int getMaxRange(const std::vector<int>& vec, int left, int right);

private:
};
