#ifndef SORT_H_
#define SORT_H_

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>

template <typename T>
void selection_sort(T* array, size_t size)
{
    auto array_end = std::next(array, size);

    auto sorted_end = array;

    while (sorted_end != array_end)
    {
        std::iter_swap(sorted_end, std::min_element(sorted_end, array_end));
        sorted_end++;
    }
}

#endif // SORT_H_
