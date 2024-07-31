#pragma once
#include <iostream>
#include <vector>

class Radixsort
{
public:
	Radixsort();
	~Radixsort();

	void sort(std::vector<int>& vec);
	void countSort(std::vector<int>& vec, int exp);	

private:
};

