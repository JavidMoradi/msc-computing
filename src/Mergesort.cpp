#include "Mergesort.h"

Mergesort::Mergesort()
{
}

Mergesort::~Mergesort()
{
}

void Mergesort::sort(std::vector<int>& vec, int left, int right)
{
    if (left < right) {
        // Find the middle point
        int mid = left + (right - left) / 2;

        // Sort the first and second halves
        sort(vec, left, mid);
        sort(vec, mid + 1, right);

        // Merge the sorted halves
        merge(vec, left, mid, right);
    }
}

void Mergesort::merge(std::vector<int>& vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;  
    int n2 = right - mid;     

    std::vector<int> leftVec(n1);
    std::vector<int> rightVec(n2);

    for (int i = 0; i < n1; ++i)
        leftVec[i] = vec[left + i];
    for (int j = 0; j < n2; ++j)
        rightVec[j] = vec[mid + 1 + j];

    int i = 0; 
    int j = 0; 
    int k = left; 

    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            ++i;
        }
        else {
            vec[k] = rightVec[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = leftVec[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = rightVec[j];
        ++j;
        ++k;
    }
}
