#include <iostream>
#include <vector>
#include <array>


//binary msd

template<class RAIter>
void __msd_sort(RAIter begin, RAIter end, RAIter buffer, std::size_t shift) {
    if (end - begin < 1) {
        return;
    }

    if (end - begin == 1){
        *buffer = *begin;
        return;
    }

    std::array<std::size_t, 2> count = {};
    std::array<RAIter, 2> begins = {};
    std::array<RAIter, 2> ends = {};

    for (auto i = begin; i < end; i++) {
        count[(*i >> shift) & 1]++;
    }

    begins[0] = ends[0] = buffer;
    begins[1] = ends[1] = buffer + count[0];

    for (auto i = begin; i < end; i++) {
        *ends[(*i >> shift) & 1]++ = *i;
    }

    if (shift != 0) {
        __msd_sort(begins[0], ends[0], begin, shift - 1);
        __msd_sort(begins[1], ends[1], begin + (begins[1] - begins[0]), shift - 1);
    }
}

template<class RAIter>
void msd_sort(RAIter begin, RAIter end) {
    const size_t shift = sizeof(typename RAIter::value_type) * 8 - 1;
    std::vector<typename RAIter::value_type> buffer(end - begin);

    __msd_sort(begin, end, buffer.begin(), shift);

}

int main() {
    std::size_t vector_size = 0;
    std::cin >> vector_size;


    std::vector<long long> vector(vector_size);
    for (auto& i : vector) {
        std::cin >> i;
    }

    msd_sort(vector.begin(), vector.end());
    for (auto i : vector) {
        std::cout << i << ' ';
    }
    return 0;
}