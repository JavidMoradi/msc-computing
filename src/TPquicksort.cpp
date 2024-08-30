#include "TPquicksort.h"

TPquicksort::TPquicksort() {}

TPquicksort::~TPquicksort() {}

void TPquicksort::insertionSort(std::vector<int>& arr, int start, int end)
{
	for (int i = start + 1; i <= end; ++i) {
		int key = arr[i];
		int j = i - 1;
		while (j >= start && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

void TPquicksort::mergeArrays(std::vector<int>& arr, int begin, int mid, int end)
{
	std::vector<int> temp(end - begin + 1);

	int i = begin;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (arr[i] < arr[j]) {
			temp[k] = arr[i];
			i++;
		}
		else {
			temp[k] = arr[j];
			j++;
		}
		k++;
	}

	while (i <= mid) {
		temp[k] = arr[i];
		i++;
		k++;
	}

	while (j <= end) {
		temp[k] = arr[j];
		j++;
		k++;
	}

	for (int index = 0; index < temp.size(); index++)
	{
		arr[begin + index] = temp[index];
	}
}

int TPquicksort::calculatePivot(const std::vector<int>& arr, int begin, int end)
{
	int mid = (begin + end) / 2;

	// Initialize min and max values for both halves
	int minl = arr[begin], maxl = arr[begin];
	int minr = arr[begin], maxr = arr[begin];

	// Calculate min and max for the left half
	for (int i = begin; i <= mid; i++) {
		if (arr[i] < minl) minl = arr[i];
		if (arr[i] > maxl) maxl = arr[i];
	}

	// Calculate min and max for the right half
	for (int i = mid + 1; i <= end; i++) {
		if (arr[i] < minr) minr = arr[i];
		if (arr[i] > maxr) maxr = arr[i];
	}

	// Calculate means of the left and right halves
	double meanl = (minl + maxl) / 2.0;
	double meanr = (minr + maxr) / 2.0;

	// Return the floor of the average of the two means
	return static_cast<int>(std::floor((meanl + meanr) / 2));
}

void TPquicksort::threePivotSort(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	int a = left + 2;
	int b = left + 2;
	int c = right - 1;
	int d = right - 1;

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSort(A, left, a - 1);
	threePivotSort(A, a + 1, b - 1);
	threePivotSort(A, b + 1, d - 1);
	threePivotSort(A, d + 1, right);
}

void TPquicksort::naive_mt_threePivotSort(std::vector<int>& A, int size, int k)
{
	if (size < k) {
		threePivotSort(A, 0, size - 1);
		return;
	}

	unsigned int coreCount = std::thread::hardware_concurrency();
	if (coreCount == 0) {
		std::cout << "Unable to determine the number of CPU cores." << std::endl;
		std::cout << "Regular sorting is applied." << std::endl;

		threePivotSort(A, 0, size - 1);
		return;
	}
	else if (k > coreCount) {
		k = coreCount;
	}

	TPquicksort tp;

	const int subSize = std::floor(size / k);

	int begin = 0;
	int end = subSize - 1;
	int counter = 1;

	std::vector<std::thread> threads;

	for (int i = 0; i < k; i++) {
		threads.push_back(
			std::thread([&tp, &A, begin, end]() {
				tp.threePivotSort(A, begin, end);
				})
		);

		begin = end + 1;
		end = (++counter == k) ? size - 1 : begin + subSize - 1;
	}

	for (std::thread& thread : threads)
		thread.join();

	// merge arrays here through mergearrays()
	int n = size;
	for (int sz = subSize; sz < n; sz *= 2) {
		for (int start = 0; start < n - 1; start += 2 * sz) {
			int mid = std::min(start + sz - 1, n - 1);
			int end = std::min(start + 2 * sz - 1, n - 1);
			mergeArrays(A, start, mid, end);
		}
	}
}

void TPquicksort::parallelTPquicksort(std::vector<int>& seq, int first, int last)
{
	if (first < last) {
		int size = last + 1;

		if (size <= INSERTION_SORT_THRESHOLD) {
			insertionSort(seq, 0, size - 1);
			return;
		}

		const int i = 3;

		int t = pow(2, i - 1);
		int k = pow(2, i - 1) - 1;

		int kTh1 = ceil(size / t) - 1;	// Initial splitters
		int kTh2 = kTh1 + ceil(size / t);
		int kTh3 = kTh2 + ceil(size / t);
		int kTh4 = kTh3 + ceil(size / t);

		int part1 = 0,
			part2 = 0,
			part3 = 0,
			part4 = 0;	// Final splitters

		parallelKthPartition(seq, last, part1, part2, part3, part4, kTh1, kTh2, kTh3, kTh4);

		TPquicksort tp;
		std::thread t1 = std::thread([&tp, &seq, first, part1]() {
			tp.threePivotSort(seq, first, part1);
			});
		std::thread t2 = std::thread([&tp, &seq, part1, part2]() {
			tp.threePivotSort(seq, part1 + 1, part2);
			});
		std::thread t3 = std::thread([&tp, &seq, part2, part3]() {
			tp.threePivotSort(seq, part2 + 1, part3);
			});
		std::thread t4 = std::thread([&tp, &seq, part3, last]() {
			tp.threePivotSort(seq, part3 + 1, last);
			});

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
}

void TPquicksort::parallelKthPartition(std::vector<int>& seq, int last, 
	int& part1, int& part2, int& part3, int& part4, 
	int kTh1, int kTh2, int kTh3, int kTh4)
{
	std::vector<int> s;	// Sample set

	// Generate a random index value
	int sampleCount = 8;
	srand((unsigned)time(0));
	for (int i = 0; i < sampleCount; i++) {
		int randomIndex = rand() % seq.size();

		s.push_back(seq[randomIndex]);
	}

	threePivotSort(s, 0, s.size() - 1);

	int split1 = s[0],
		split2 = s[s.size() / 2],
		split3 = s[s.size() - 1];	// Intermediate splitters

	std::vector<int> bucket1; // Virtual buckets
	std::vector<int> bucket2;
	std::vector<int> bucket3;
	std::vector<int> bucket4;

	int count1 = 0, count2 = 0, count3 = 0, count4 = 0;

	auto partition = [&](int start, int end) {
		for (int i = start; i <= end; i++) {
			int element = seq[i];
			std::lock_guard<std::mutex> lock(mtx);
			if (element <= split1) {
				bucket1.push_back(element);
				count1++;
			}
			else if (element <= split2) {
				bucket2.push_back(element);
				count2++;
			}
			else if (element <= split3) {
				bucket3.push_back(element);
				count3++;
			}
			else {
				bucket4.push_back(element);
				count4++;
			}
		}
		};

	std::thread t1(partition, 0, kTh1);
	std::thread t2(partition, kTh1 + 1, kTh2);
	std::thread t3(partition, kTh2 + 1, kTh3);
	std::thread t4(partition, kTh3 + 1, last);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	part1 = count1 - 1;
	part2 = part1 + count2;
	part3 = part2 + count3;
	part4 = part3 + count4;

	int index = 0;
	for (int i = 0; i < bucket1.size(); i++) {
		seq[index++] = bucket1[i];
	}
	for (int i = 0; i < bucket2.size(); i++) {
		seq[index++] = bucket2[i];
	}
	for (int i = 0; i < bucket3.size(); i++) {
		seq[index++] = bucket3[i];
	}
	for (int i = 0; i < bucket4.size(); i++) {
		seq[index++] = bucket4[i];
	}
}

void TPquicksort::threePivotSortWithCache(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	Cache cache;
	cache.a = left + 2;
	cache.b = left + 2;
	cache.c = right - 1;
	cache.d = right - 1;

	while (cache.b <= cache.c)
	{
		while (A[cache.b] < q && cache.b <= cache.c)
		{
			if (A[cache.b] < p)
			{
				std::swap(A[cache.a], A[cache.b]);
				cache.a++;
			}
			cache.b++;
		}
		while (A[cache.c] > q && cache.b <= cache.c)
		{
			if (A[cache.c] > r)
			{
				std::swap(A[cache.c], A[cache.d]);
				cache.d--;
			}
			cache.c--;
		}
		if (cache.b <= cache.c)
		{
			if (A[cache.b] > r)
			{
				if (A[cache.c] < p)
				{
					std::swap(A[cache.b], A[cache.a]);
					std::swap(A[cache.a], A[cache.c]);
					cache.a++;
				}
				else
				{
					std::swap(A[cache.b], A[cache.c]);
				}
				std::swap(A[cache.c], A[cache.d]);
				cache.b++;
				cache.c--;
				cache.d--;
			}
			else
			{
				if (A[cache.c] < p)
				{
					std::swap(A[cache.b], A[cache.a]);
					std::swap(A[cache.a], A[cache.c]);
					cache.a++;
				}
				else
				{
					std::swap(A[cache.b], A[cache.c]);
				}
				cache.b++;
				cache.c--;
			}
		}
	}
	cache.a--;
	cache.b--;
	cache.c++;
	cache.d++;
	std::swap(A[left + 1], A[cache.a]);
	std::swap(A[cache.a], A[cache.b]);
	cache.a--;
	std::swap(A[left], A[cache.a]);
	std::swap(A[right], A[cache.d]);

	threePivotSortWithCache(A, left, cache.a - 1);
	threePivotSortWithCache(A, cache.a + 1, cache.b - 1);
	threePivotSortWithCache(A, cache.b + 1, cache.d - 1);
	threePivotSortWithCache(A, cache.d + 1, right);
}

void TPquicksort::threePivotSortAltPvt(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	int subsize = size / 4;

	int p = calculatePivot(A, left, left + 2 * subsize - 1);
	int q = calculatePivot(A, left + subsize, (left + subsize) + 2 * subsize - 1);
	int r = calculatePivot(A, left + 2 * subsize, right);

	int minIndx = left;
	int min = INT_MAX;
	for (int i = left; i < left + 2 * subsize; i++) {
		if (std::abs(A[i] - p) < min) {
			minIndx = i;
			min = std::abs(A[i] - p);
		}
	}
	std::swap(A[left], A[minIndx]);

	minIndx = left + subsize;
	min = INT_MAX;
	for (int i = left + subsize; i < (left + subsize) + 2 * subsize; i++) {
		if (std::abs(A[i] - q) < min) {
			minIndx = i;
			min = std::abs(A[i] - q);
		}
	}
	std::swap(A[mid], A[minIndx]);

	minIndx = left + 2 * subsize;
	min = INT_MAX;
	for (int i = left + 2 * subsize; i <= right; i++) {
		if (std::abs(A[i] - r) < min) {
			minIndx = i;
			min = std::abs(A[i] - r);
		}
	}
	std::swap(A[right], A[minIndx]);

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	p = A[left];
	q = A[mid];
	r = A[right];

	std::swap(A[left + 1], A[mid]);

	int a = left + 2;
	int b = left + 2;
	int c = right - 1;
	int d = right - 1;

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSortAltPvt(A, left, a - 1);
	threePivotSortAltPvt(A, a + 1, b - 1);
	threePivotSortAltPvt(A, b + 1, d - 1);
	threePivotSortAltPvt(A, d + 1, right);
}

void TPquicksort::threePivotSortWithCacheHeap(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	auto cache = std::make_unique<Cache>();
	cache->a = left + 2;
	cache->b = left + 2;
	cache->c = right - 1;
	cache->d = right - 1;

	while (cache->b <= cache->c)
	{
		while (A[cache->b] < q && cache->b <= cache->c)
		{
			if (A[cache->b] < p)
			{
				std::swap(A[cache->a], A[cache->b]);
				cache->a++;
			}
			cache->b++;
		}
		while (A[cache->c] > q && cache->b <= cache->c)
		{
			if (A[cache->c] > r)
			{
				std::swap(A[cache->c], A[cache->d]);
				cache->d--;
			}
			cache->c--;
		}
		if (cache->b <= cache->c)
		{
			if (A[cache->b] > r)
			{
				if (A[cache->c] < p)
				{
					std::swap(A[cache->b], A[cache->a]);
					std::swap(A[cache->a], A[cache->c]);
					cache->a++;
				}
				else
				{
					std::swap(A[cache->b], A[cache->c]);
				}
				std::swap(A[cache->c], A[cache->d]);
				cache->b++;
				cache->c--;
				cache->d--;
			}
			else
			{
				if (A[cache->c] < p)
				{
					std::swap(A[cache->b], A[cache->a]);
					std::swap(A[cache->a], A[cache->c]);
					cache->a++;
				}
				else
				{
					std::swap(A[cache->b], A[cache->c]);
				}
				cache->b++;
				cache->c--;
			}
		}
	}
	cache->a--;
	cache->b--;
	cache->c++;
	cache->d++;
	std::swap(A[left + 1], A[cache->a]);
	std::swap(A[cache->a], A[cache->b]);
	cache->a--;
	std::swap(A[left], A[cache->a]);
	std::swap(A[right], A[cache->d]);

	threePivotSortWithCacheHeap(A, left, cache->a - 1);
	threePivotSortWithCacheHeap(A, cache->a + 1, cache->b - 1);
	threePivotSortWithCacheHeap(A, cache->b + 1, cache->d - 1);
	threePivotSortWithCacheHeap(A, cache->d + 1, right);
}

void TPquicksort::threePivotSortWithCacheArray(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	int cache[4] = {left + 2, left + 2, right - 1, right - 1};
	int a = cache[0];
	int b = cache[1];
	int c = cache[2];
	int d = cache[3];

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSortWithCacheArray(A, left, a - 1);
	threePivotSortWithCacheArray(A, a + 1, b - 1);
	threePivotSortWithCacheArray(A, b + 1, d - 1);
	threePivotSortWithCacheArray(A, d + 1, right);
}

void TPquicksort::threePivotSortWithCacheArrayHeap(std::vector<int>& A, int left, int right)
{
	int size = right - left + 1;
	if (size < INSERTION_SORT_THRESHOLD) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	std::vector<int> cache = { left + 2, left + 2, right - 1, right - 1 };

	int a = cache[0];
	int b = cache[1];
	int c = cache[2];
	int d = cache[3];

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSortWithCacheArrayHeap(A, left, a - 1);
	threePivotSortWithCacheArrayHeap(A, a + 1, b - 1);
	threePivotSortWithCacheArrayHeap(A, b + 1, d - 1);
	threePivotSortWithCacheArrayHeap(A, d + 1, right);
}

void TPquicksort::threePivotSort(std::vector<int>& A, int left, int right, int insertionSortThreshold)
{
	int size = right - left + 1;
	if (size < insertionSortThreshold) {
		if (size > 1)
			insertionSort(A, left, right);
		return;
	}

	int mid = (right + left) / 2;

	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);
	if (A[mid] > A[right])
		std::swap(A[mid], A[right]);
	if (A[left] > A[mid])
		std::swap(A[left], A[mid]);

	int p = A[left];
	int q = A[mid];
	int r = A[right];

	std::swap(A[left + 1], A[mid]);

	int a = left + 2;
	int b = left + 2;
	int c = right - 1;
	int d = right - 1;

	while (b <= c)
	{
		while (A[b] < q && b <= c)
		{
			if (A[b] < p)
			{
				std::swap(A[a], A[b]);
				a++;
			}
			b++;
		}
		while (A[c] > q && b <= c)
		{
			if (A[c] > r)
			{
				std::swap(A[c], A[d]);
				d--;
			}
			c--;
		}
		if (b <= c)
		{
			if (A[b] > r)
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				std::swap(A[c], A[d]);
				b++;
				c--;
				d--;
			}
			else
			{
				if (A[c] < p)
				{
					std::swap(A[b], A[a]);
					std::swap(A[a], A[c]);
					a++;
				}
				else
				{
					std::swap(A[b], A[c]);
				}
				b++;
				c--;
			}
		}
	}
	a--;
	b--;
	c++;
	d++;
	std::swap(A[left + 1], A[a]);
	std::swap(A[a], A[b]);
	a--;
	std::swap(A[left], A[a]);
	std::swap(A[right], A[d]);

	threePivotSort(A, left, a - 1, insertionSortThreshold);
	threePivotSort(A, a + 1, b - 1, insertionSortThreshold);
	threePivotSort(A, b + 1, d - 1, insertionSortThreshold);
	threePivotSort(A, d + 1, right, insertionSortThreshold);
}
