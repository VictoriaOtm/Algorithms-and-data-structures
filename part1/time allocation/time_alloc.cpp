/*7_2. Заявки на переговоры.
В большой IT-фирме есть только одна переговорная комната.
Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
 Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
Число заявок ≤ 100000.
Формат входных данных:
Вход содержит только пары целых чисел — начала и концы заявок.
Формат выходных данных:
Выход должен содержать натуральное число — максимальное число заявок.
 */

#include <iostream>
#include <fstream>
#include <cstddef>
#include <cstring>
#include <stdexcept>

namespace vic{
    template <class T>
    class Vector{
    public:
        Vector() : _size(0), _capacity(16) {
            _data = new T[_capacity]();
        }

        Vector(const std::size_t new_size) : _size(new_size), _capacity(new_size + 2) {
            _data = new T[_capacity];
        }

        ~Vector() {
            delete[] _data;
        }

        Vector& operator=(const Vector& another) {
            _size = another._size;
            _capacity = another._capacity;

            delete[] _data;
            _data = new T[_capacity]();
            memcpy(_data, another._data, _size);

            return *this;
        }

        const bool empty() {
            return (_size == 0);
        }

        const std::size_t size() const{
            return _size;
        }

        void push(const T &value) {
            if (_size == _capacity) {
                resize_data(2);
            }
            _data[_size] = value;
            ++_size;
        }

        T& operator[](size_t index) {
            if (index < _size)
                return _data[index];
            else{
                std::cout << _size << " - size, index : " << index;
                throw std::runtime_error("index is bigger than vector's size");
            }
        }

    private:
        T *_data;
        std::size_t _size;
        std::size_t _capacity;

        void resize_data(double capacity_factor) {
            _capacity = static_cast<std::size_t >(_capacity * capacity_factor);

            T *temp = new T[_capacity]();
            std::memcpy(temp, _data, _size * sizeof(T));
            delete[] _data;

            _data = temp;
        }
    };
}

namespace vic {
    struct int_pair {
        int first;
        int second;
        int length;

        int_pair() : first(0), second(0), length(0) {}

        int_pair(const int new_first, const int new_second) :
                first(new_first),
                second(new_second),
                length(first - second) {}

        ~int_pair() = default;

        bool operator==(const int_pair& rhs) {
            return (first == rhs.first && second == rhs.second);
        }

        bool operator>(const int_pair& rhs) {
            return second > rhs.second;
        }

        bool operator<(const int_pair& rhs) {
            return second < rhs.second;
        }

        int_pair& operator=(const int_pair& rhs) {
            first = rhs.first;
            second = rhs.second;
            length = rhs.length;
            return *this;
        }

    };
}

void read_pairs(vic::Vector<vic::int_pair>& pairs) {
    std::ifstream input("input.txt", std::ios::in);

    vic::int_pair pair;

    while (!input.eof()) {
        input >> pair.first >> pair.second;
        pair.length = pair.second - pair.first;
        pairs.push(pair);
    }

}

void quick_sort(vic::Vector<vic::int_pair>& vec, long l, long r) {
    long i = l, j = r;

    vic::int_pair temp;
    vic::int_pair mid;

    mid = vec[(l+r) / 2];

    do {
        while (vec[i] < mid) i++;
        while (vec[j] > mid) j--;

        if (i <= j) {
            temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
            j--;
        }

    } while (i <= j);

    if (i < r) {
        quick_sort(vec, i, r);
    }
    if (j > l){
        quick_sort(vec, l, j);
    }

}

int count_pairs(vic::Vector<vic::int_pair>& vec){
    int counter = 1;
    int cur_min = vec[0].second;

    for (int i = 1; i < vec.size(); i++){
        if (vec[i].second > cur_min && vec[i].first >= cur_min){
            ++counter;
            cur_min = vec[i].second;
        }
    }
    return counter;
}


int main() {
    vic::Vector<vic::int_pair> pairs;

    read_pairs(pairs);
    quick_sort(pairs, 0 , pairs.size() - 1);

    std::cout << count_pairs(pairs);

    return 0;
}
