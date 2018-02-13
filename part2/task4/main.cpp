#include <iostream>
#include <vector>
#include <algorithm>

namespace vic {


//median of three
    template<typename Iterator, typename Compare>
    Iterator get_pivot(Iterator begin, Iterator end, Compare &cmp) {

        Iterator middle = begin + (std::distance(begin, end + 1) >> 1);

        if (!cmp(*middle, *begin) && !cmp(*end, *begin)) {
            return (!cmp(*end, *middle) ? middle : end);
        }

        if (!cmp(*begin, *middle) && !cmp(*begin, *end)) {
            return (!cmp(*middle, *end) ? middle : end);
        }

        return begin;
    }


    template<typename Iterator, typename Compare>
    Iterator partition(Iterator begin, Iterator end, Compare &cmp) {
        Iterator pivot = get_pivot(begin, end, cmp);

        if (pivot != begin) {
            std::iter_swap(begin, pivot);
        }

        Iterator store_iter = end;

        for (Iterator it = end; it >= begin + 1; it--) {
            if (!cmp(*it, *begin)) {
                std::iter_swap(it, store_iter);
                --store_iter;
            }
        }

        std::iter_swap(begin, store_iter);

        return store_iter;
    };
}


template<typename Iterator, typename Compare>
Iterator k_order_statistics(Iterator begin, Iterator end, const std::size_t k, Compare &cmp) {
    Iterator left = begin;
    Iterator right = end - 1;
    Iterator kth = begin + k;
    Iterator pivot = begin;

    while (true) {
        if (right == left) {
            return left;
        }

        pivot = vic::partition(left, right, cmp);

        if (kth == pivot) {
            return kth;
        }

        if (kth < pivot) {
            right = pivot - 1;
        } else {
            left = pivot + 1;
        }
    }
}

int main() {

    std::size_t size = 0;
    std::size_t k = 0;
    std::cin >> size >> k;

    std::vector<unsigned long> vec(size);
    for (auto &i : vec) {
        std::cin >> i;
    }

    std::less<unsigned long> cmp;
    std::cout << *k_order_statistics(vec.begin(), vec.end(), k, cmp);

    return 0;
}