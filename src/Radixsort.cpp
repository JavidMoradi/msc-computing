#include "Radixsort.h"

int getMax(const std::vector<int>& vec) {
    return *std::max_element(vec.begin(), vec.end());
}

Radixsort::Radixsort()
{
}

Radixsort::~Radixsort()
{
}

void Radixsort::sort(std::vector<int>& vec)
{
    int m = getMax(vec);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(vec, exp);
}

void Radixsort::countSort(std::vector<int>& vec, int exp)
{
    int n = vec.size();
    std::vector<int> output(n); // Output array
    int count[10] = { 0 }; // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = 0; i < n; ++i)
        ++count[(vec[i] / exp) % 10];

    // Change count[i] so that it contains the actual position of this digit in output[]
    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; --i) {
        output[count[(vec[i] / exp) % 10] - 1] = vec[i];
        --count[(vec[i] / exp) % 10];
    }

    // Copy the output array to vec, so that vec now contains sorted numbers according to the current digit
    for (int i = 0; i < n; ++i)
        vec[i] = output[i];
}

void Radixsort::sortRange(std::vector<int>& vec, int left, int right)
{
    if (left >= right) return;  // No need to sort if the range is invalid

    // Find the maximum number in the range [left, right]
    int m = getMaxRange(vec, left, right);

    // Perform counting sort for each digit position
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSortRange(vec, left, right, exp);
}

void Radixsort::countSortRange(std::vector<int>& vec, int left, int right, int exp)
{
    int n = right - left + 1;
    std::vector<int> output(n);  // Output array for the current range
    int count[10] = { 0 };         // Initialize count array as 0

    // Store count of occurrences in count[]
    for (int i = left; i <= right; ++i)
        ++count[(vec[i] / exp) % 10];

    // Change count[i] so that it contains the actual position of this digit in output[]
    for (int i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = right; i >= left; --i) {
        int index = (vec[i] / exp) % 10;
        output[count[index] - 1] = vec[i];
        --count[index];
    }

    // Copy the output array to vec, so that vec now contains sorted numbers according to the current digit
    for (int i = 0; i < n; ++i)
        vec[left + i] = output[i];
}

int Radixsort::getMaxRange(const std::vector<int>& vec, int left, int right)
{
    int maxVal = vec[left];
    for (int i = left + 1; i <= right; ++i) {
        if (vec[i] > maxVal) {
            maxVal = vec[i];
        }
    }
    return maxVal;
}