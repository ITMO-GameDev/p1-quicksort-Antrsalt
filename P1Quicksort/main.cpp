#include <iostream>

const auto intComparator = [](int a, int b) { return a > b; };

template <typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
	while (first < last) {
		int length = last - first + 1;
		if (length > 1) {
			int i = 0;
			int j = last - first;

			if (length <= 12) {
				insertionSort(first, last, comp);
				return;
			}

			T pivot = median(first, last, comp);

			do {
				while (comp(pivot, first[i]))
					i++;
				while (comp(first[j], pivot))
					j--;
				if (i <= j) {
					std::swap(first[i], first[j]);
					i++;
					if (j > 0) {
						j--;
					}
				}
			} while (i <= j);

			if (j < length + i) {
				sort(first, first + j, comp);
				first = first + i + 1;
			}
			else {
				sort(first + i, last, comp);
				last = first + i - 1;
			}
		}
	}
}

template<typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp)
{
    int length = (last - first) + 1;
    for (int i = 1; i < length; i++)
    {
        int j = i;
        while (j > 0 && comp(first[j - 1], first[j]))
        {
            std::swap(first[j - 1], first[j]);
            j--;
        }
    }
}

template<typename T, typename Compare>
T median(const T* first, const T* last, Compare comp)
{
    int length = last - first;
    int middle = length / 2;
    return (comp(first[0], last[0])
            ? (comp(last[0], first[middle]) ? last[0] :
                comp(first[0], first[middle]) ? first[middle] : first[0])
            : (comp(first[middle], last[0]) ? last[0] :
                comp(first[middle], first[0]) ? first[middle] : first[0]));
}