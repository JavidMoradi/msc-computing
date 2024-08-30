#include <iostream>
#include <vector>

class Mergesort
{
public:
	Mergesort();
	~Mergesort();

	void sort(std::vector<int>& vec, int left, int right);
	void merge(std::vector<int>& vec, int left, int mid, int right);

private:
};

