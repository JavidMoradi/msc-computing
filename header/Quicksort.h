#include <iostream>
#include <vector>

class Quicksort
{
public:
	Quicksort();
	~Quicksort();

	int partition(std::vector<int>& arr, int start, int end);
	void sort(std::vector<int>& arr, int start, int end);

private:

};