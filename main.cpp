#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include <rapidcheck.h>

#include "prettyprint.hpp"
#include "sort.hpp"

int main()
{
    std::array<int, 6> arr_merge = { 5, 4, 1, 6, 2, 3 };
    std::array<int, 6> arr_selection = { 5, 4, 1, 6, 2, 3 };

    std::cout << arr_merge << std::endl;
    std::cout << arr_selection << std::endl;

    merge_sort(arr_merge.data(), 6);
    selection_sort(arr_selection.data(), 6);

    std::cout << std::endl << "Sorted:" << std::endl;
    std::cout << arr_merge << std::endl;
    std::cout << arr_selection << std::endl;

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

    return 0;
}
