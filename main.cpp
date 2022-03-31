#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include <rapidcheck.h>

#include "prettyprint.hpp"
#include "sort.hpp"

std::vector<int> random_vector_int(std::vector<int>::size_type n);

int main()
{
    std::array<int, 6> arr_merge = { 5, 4, 1, 6, 2, 3 };
    std::array<int, 6> arr_selection = { 5, 4, 1, 6, 2, 3 };

    std::cout << arr_merge << std::endl;
    std::cout << arr_selection << std::endl;

    merge_sort(arr_merge.data(), 6);
    selection_sort(arr_selection.data(), 6);

    std::cout << std::endl
              << "Sorted:" << std::endl;
    std::cout << arr_merge << std::endl;
    std::cout << arr_selection << std::endl;
    std::cout << std::endl;

    rc::check("Works for int",
        [](std::vector<int> vec) {
            auto vec_merge = vec;
            auto vec_selection = vec;

            std::sort(vec.begin(), vec.end());

            merge_sort(vec_merge.data(), vec_merge.size());
            selection_sort(vec_selection.data(), vec_selection.size());

            RC_ASSERT(vec == vec_merge);
            RC_ASSERT(vec == vec_selection);
        });

    rc::check("Works for std::string",
        [](std::vector<std::string> vec) {
            auto vec_merge = vec;
            auto vec_selection = vec;

            std::sort(vec.begin(), vec.end());

            merge_sort(vec_merge.data(), vec_merge.size());
            selection_sort(vec_selection.data(), vec_selection.size());

            RC_ASSERT(vec == vec_merge);
            RC_ASSERT(vec == vec_selection);
        });

    // Benchmark
    std::map<size_t, double> merge_times;
    std::map<size_t, double> selection_times;

    std::vector<size_t> n_elements_to_test = { 256, 512, 1024, 2048, 4096, 8192, 16384 };
    // std::vector<size_t> n_elements_to_test = { 10, 100 };
    unsigned tests_per_n = 20;

    for (auto n_elements : n_elements_to_test)
    {
        std::vector<double> merge_times_for_n;
        std::vector<double> selection_times_for_n;

        for (unsigned i = 0; i < tests_per_n; i++)
        {
            auto vec_merge = random_vector_int(n_elements);
            auto vec_selection = vec_merge;

            auto t1 = std::chrono::high_resolution_clock::now();
            merge_sort(vec_merge.data(), vec_merge.size());
            auto t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> merge_time = t2 - t1;

            merge_times_for_n.push_back(merge_time.count());

            t1 = std::chrono::high_resolution_clock::now();
            selection_sort(vec_selection.data(), vec_selection.size());
            t2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> selection_time = t2 - t1;

            selection_times_for_n.push_back(selection_time.count());
        }

        double merge_time = std::accumulate(merge_times_for_n.begin(),
                                merge_times_for_n.end(),
                                0.0)
            / merge_times_for_n.size();

        double selection_time = std::accumulate(selection_times_for_n.begin(),
                                    selection_times_for_n.end(),
                                    0.0)
            / selection_times_for_n.size();

        merge_times[n_elements] = merge_time;
        selection_times[n_elements] = selection_time;
    }

    std::cout << "Times for merge:" << std::endl;
    std::cout << merge_times << std::endl;
    std::cout << std::endl;

    std::cout << "Times for selection:" << std::endl;
    std::cout << selection_times << std::endl;

    return 0;
}

std::vector<int> random_vector_int(std::vector<int>::size_type n)
{
    std::vector<int> vec(n);

    // From https://stackoverflow.com/a/19728404
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 10000);

    for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
    {
        vec[i] = uni(rng);
    }

    return vec;
}
