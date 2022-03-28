#ifndef SORT_H_
#define SORT_H_

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <type_traits>

template <typename T>
void merge_sort(T* array, size_t size);

template <typename T>
void merge_sort_pointers_merge(T** begin, T** middle, T** end);

template <typename T>
void merge_sort_pointers(T** begin, T** end);

template <typename T>
void merge_sort(T* array, size_t size)
{
    T** sorted_pointers = new T*[size];

    for (size_t i = 0; i < size; i++)
    {
        sorted_pointers[i] = array + i;
    }

    // Proper sorting algorithm called here
    merge_sort_pointers(sorted_pointers, sorted_pointers + size);

    size_t* index_to_sorted_index = new size_t[size];
    size_t* sorted_index_to_index = new size_t[size];

    for (size_t i = 0; i < size; i++)
    {
        size_t index_in_array = sorted_pointers[i] - array;

        sorted_index_to_index[i] = index_in_array;
        index_to_sorted_index[index_in_array] = i;
    }

    for (size_t i = 1; i < size; i++)
    {
        auto replacement_index = sorted_index_to_index[i];

        if (i == replacement_index)
        {
            continue;
        }

        std::swap(array[i], array[replacement_index]);

        size_t new_sorted_index = index_to_sorted_index[i];
        index_to_sorted_index[replacement_index] = new_sorted_index;
        sorted_index_to_index[new_sorted_index] = replacement_index;
    }
}

template <typename T>
void merge_sort_pointers(T** begin, T** end)
{
    size_t size = std::distance(begin, end);

    if (size < 2)
    {
        return;
    }

    T** middle = std::next(begin, size / 2);

    merge_sort_pointers(begin, middle);
    merge_sort_pointers(middle, end);

    merge_sort_pointers_merge(begin, middle, end);
}

template <typename T>
void merge_sort_pointers_merge(T** begin, T** middle, T** end)
{
    size_t s1_size = std::distance(begin, middle);
    T** first_part_copy = new T*[s1_size];
    T** first_part_copy_end = std::next(first_part_copy, s1_size);

    std::copy(begin, middle, first_part_copy);

    T** cur_h1 = first_part_copy;
    T** cur_h2 = middle;
    T** cur_filling = begin;

    while (cur_h1 != first_part_copy_end && cur_h2 != end)
    {
        if (**cur_h1 < **cur_h2)
        {
            *cur_filling = *cur_h1;
            cur_h1++;
        }
        else
        {
            *cur_filling = *cur_h2;
            cur_h2++;
        }

        cur_filling++;
    }

    while (cur_h1 != first_part_copy_end)
    {
        *cur_filling = *cur_h1;
        cur_filling++;
        cur_h1++;
    }
    while (cur_h2 != end)
    {
        *cur_filling = *cur_h2;
        cur_filling++;
        cur_h2++;
    }
}

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
