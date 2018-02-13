/* 
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. 
Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
*/


#include <iostream>
#include <vector>
#include <fstream>

namespace vic {
    struct Pair {
        int l;
        int r;

        explicit Pair() = default;

        Pair(const int _l, const int _r) : l(_l), r(_r) {}

        ~Pair() = default;

        int length() {
            return r - l;
        }
    };

    class Compare {
    public:
        bool operator()(const Pair &first, const Pair &second) {
            return left_pair_compare(first, second);
        }

    private:
        bool left_pair_compare(const Pair &first, const Pair &second) {
            return first.l == second.l ? first.r >= second.r : first.l < second.l;
        }
    };

    //function receive elem_index because not every type has iterator, e.x. int
    //so we make local var elem_iter to work with iterators
    template<typename Iterator, typename Compare>
    void sift_down(Iterator begin, Iterator end,
                   std::ptrdiff_t elem_index, Compare &cmp) {

        Iterator left = begin + elem_index * 2 + 1; //2i+1
        Iterator right = begin + elem_index * 2 + 2; //2i+2

        Iterator elem_iter = begin + elem_index;

        Iterator largest = elem_iter;
        if (left < end && cmp(*elem_iter, *left)) {
            largest = left;
        }

        if (right < end && cmp(*largest, *right)) {
            largest = right;
        }

        if (largest != elem_iter) {
            std::iter_swap(elem_iter, largest);
            sift_down(begin, end, std::distance(begin, largest), cmp);
        }
    }

    template<typename Iterator>
    void sift_down(Iterator begin, Iterator end, std::ptrdiff_t elem_index) {

        std::less<typename Iterator::value_type> cmp;

        return sift_down(begin, end, elem_index, cmp);
    }

    template<typename Iterator, typename Compare>
    void make_heap(Iterator begin, Iterator end, Compare &cmp) {

        std::ptrdiff_t iter_dist = std::distance(begin, end);
        std::ptrdiff_t elem_index = iter_dist / 2 - 1;

        for (std::ptrdiff_t i = elem_index; i >= 0; i--) {
            sift_down(begin, end, i, cmp);
        }
    }

    template<typename Iterator>
    void make_heap(Iterator begin, Iterator end) {
        std::less<typename Iterator::value_type> cmp;

        return make_heap(begin, end, cmp);
    }

    template<typename Iterator, typename Compare>
    void heap_sort(Iterator begin, Iterator end, Compare cmp) {
        std::ptrdiff_t heap_size = std::distance(begin, end);
        vic::make_heap(begin, end, cmp);

        Iterator tmp;
        while (heap_size > 1) {
            tmp = begin + heap_size - 1;
            std::iter_swap(begin, tmp);
            --heap_size;
            vic::sift_down(begin, tmp, 0, cmp);
        }

    }

    template<typename Iterator>
    void heap_sort(Iterator begin, Iterator end) {
        std::less<typename Iterator::value_type> cmp;
        return heap_sort(begin, end, cmp);
    }
};


int colored_part(std::vector<vic::Pair> &vec) {
    int colored_length = vec[0].length();
    int cur_right = vec[0].r;

    for (std::size_t i = 1; i < vec.size(); i++) {
        if (vec[i].l <= cur_right && vec[i].r > cur_right) {
            colored_length += (vec[i].r - cur_right);
            cur_right = vec[i].r;
        } else if (vec[i].l > cur_right) {
            colored_length += vec[i].length();
            cur_right = vec[i].r;
        }
    }

    return colored_length;
}

int main() {
    std::ifstream input("input.txt", std::ios::in);
    int num = 0;
    input >> num;

    std::vector<vic::Pair> vec;
    vic::Pair pair;

    for (std::size_t i = 0; i < num; i++) {
        input >> pair.l >> pair.r;
        vec.push_back(pair);
    }

    vic::Compare cmp;
    vic::heap_sort(vec.begin(), vec.end(), cmp);

    std::cout << colored_part(vec);
    return 0;
}
