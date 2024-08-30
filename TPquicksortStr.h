#pragma once
#include <iostream>
#include <vector>
#include <string>

class TPquicksortStr
{
public:
	TPquicksortStr();
	~TPquicksortStr();

	void quicksortStr(std::vector<std::string>& arr, int start, int end);
	void threePivotSortStr(std::vector<std::string>& A, int left, int right);

	int partition(std::vector<std::string>& arr, int start, int end);
	bool compareStr(std::string& str1, std::string& str2);
	void insertionSortStr(std::vector<std::string>& arr, int start, int end);

private:
	const int INSERTION_SORT_THRESHOLD = 10;
};

