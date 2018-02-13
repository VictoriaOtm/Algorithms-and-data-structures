#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <algorithm>


typedef std::pair<int, std::size_t> Pair;

namespace vic {
    template<class Type, class Compare>
    class BinaryHeap {

    public:
        explicit BinaryHeap() : _size(0), _capacity(16), _cmp(){
            std::less<int> cmp;
            _cmp = cmp;
            heap = new Type[_capacity];
        }

        explicit BinaryHeap(Compare& cmp) : _size(0), _capacity(16), _cmp(cmp) {
            heap = new Type[_capacity];
        }

        explicit BinaryHeap(const Type* begin, const Type* end, Compare& cmp) :
                _size(static_cast<std::size_t>(std::distance(begin, end))), _cmp(cmp) {

            _capacity = _size * 2;
            heap = new Type[_capacity];

            std::copy(begin, end, heap);

            build_heap();
        }

        std::size_t add(const Type& value) {
            if (_size == _capacity){
                resize_data(2);
            }

            heap[_size] = value;
            ++_size;

            sift_up(&heap[_size - 1]);
        }

        const Type& top(){
            return heap[0];
        }

        void pop(){
            if (_size > 0){
                heap[0] = heap[_size - 1];
                --_size;

                if (_size > 0){
                    sift_down(heap);
                }
            }
        }

        Type* data() {
            return heap;
        }

        const std::size_t size() const {
            return _size;
        }

        Type& operator[](std::size_t index) throw(std::runtime_error) {
            if (index < _size)
                return heap[index];
            throw std::runtime_error("index is bigger than vector's _size");
        }

        ~BinaryHeap() noexcept {
            delete[] heap;
        }


    private:
        Type* heap;

        std::size_t _size;
        std::size_t _capacity;

        Compare& _cmp;

        void sift_up(Type* elem) {
            while (elem > heap) {
                Type* parent = heap + (std::distance(heap, (elem - 1)) / 2);

                if (!_cmp(*parent, *elem)) {
                    return;
                }

                std::iter_swap(elem, parent);
                elem = parent;
            }
        }

        void sift_down(Type* elem) {
            std::ptrdiff_t index_val = elem - heap;

            Type* left = elem + index_val + 1; //2i+1
            Type* right = elem + index_val + 2; //2i+2

            Type* largest = elem;
            if (left < heap + _size && _cmp(*elem, *left)) {
                largest = left;
            }

            if (right < heap + _size && _cmp(*largest, *right)) {
                largest = right;
            }

            if (largest != elem) {
                std::iter_swap(elem, largest);
                sift_down(largest);
            }

        }

        void build_heap() {
            for (Type* iter = heap + (_size / 2 - 1); iter >= heap; iter--) {
                sift_down(iter);
            }
        }

        void resize_data(const std::size_t capacity_factor){
            _capacity *= capacity_factor;

            auto* temp = new Type[_capacity];
            std::copy(heap, heap + _size, temp);
            delete[] heap;

            heap = temp;
        }

    };

    class Compare {
    public:
        bool operator()(const Pair& first, const Pair& second) {
            return pairs_cmp(first, second);
        }

    private:
        bool pairs_cmp(const Pair& first, const Pair& second) {
            return first < second;
        }

    };

}



void sliding_max(std::vector<int>& data, std::size_t window_size) {

    if (window_size == 1) {
        for (std::size_t i = 0; i < data.size() - 1; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << data.back();
        return;
    }

    if (window_size == 0) {
        return;
    }

    vic::Compare cmp;
    vic::BinaryHeap<Pair, vic::Compare> heap(cmp);

    for (std::size_t i = 0; i < window_size; i++){
        heap.add(Pair(data[i], i));
    }

    for (std::size_t i = window_size; i < data.size(); i++){
        Pair pair = heap.top();
        std::cout << pair.first << " ";

        while(pair.second <= i - window_size){
            heap.pop();
            pair.first = heap.top().first;
            pair.second = heap.top().second;
        }
        heap.add(Pair(data[i], i));
    }
    std::cout << heap.top().first;

}

int main() {
    int size = 0;
    std::cin >> size;

    std::vector<int> vec;

    int number = 0;

    for (std::size_t i = 0; i < size; i++) {
        std::cin >> number;

        vec.push_back(number);
    }

    std::size_t window_size = 0;
    std::cin >> window_size;

    sliding_max(vec, window_size);

    return 0;
}