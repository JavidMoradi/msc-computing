#include <iostream>
#include <vector>

class Quicksort
{
public:
	Quicksort();
	~Quicksort();

	// Source: https://www.geeksforgeeks.org/cpp-program-for-quicksort/
	int partition(std::vector<int>& arr, int start, int end);
	void sort(std::vector<int>& arr, int start, int end);

private:

};