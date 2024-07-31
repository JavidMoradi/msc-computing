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

