#include <iostream>
#include <cstring>
#include <stdexcept>

namespace vic {
    template<class T>
    class Vector {
    public:
        Vector() : _size(0), _capacity(16) {
            _data = new T[_capacity]();
        }

        Vector(const std::size_t new_size) : _size(new_size), _capacity(new_size + 2) {
            _data = new T[_capacity]();
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

        const std::size_t size() {
            return _size;
        }

        void push(const T& value) {
            if (_size == _capacity) {
                resize_data(2);
            }
            _data[_size] = value;
            ++_size;
        }

        T& operator[](size_t index) {
            if (index < _size)
                return _data[index];
            else {
                std::cout << _size << " - size, index : " << index;
                throw std::runtime_error("index is bigger than vector's size");
            }
        }

    private:
        T* _data;
        std::size_t _size;
        std::size_t _capacity;

        void resize_data(double capacity_factor) {
            _capacity = static_cast<std::size_t >(_capacity * capacity_factor);

            T* temp = new T[_capacity]();
            std::memcpy(temp, _data, _size * sizeof(T));
            delete[] _data;

            _data = temp;
        }
    };
}

void fill_table(vic::Vector<vic::Vector<int64_t>>& table, std::size_t n){
    for (std::size_t i = 0; i < n + 1; i++){
        for (std::size_t j = 0; j < n + 1; j++){
            if (i == 0){
                table[i][j] = 1;
            }
            else if (j == 0){
                table[i][j] = 0;
            }
            else if (j > 0 && j <= i){
                table[i][j] = table[i][j - 1] + table[i - j][j];
            }
            else if (j > i){
                table[i][j] = table[i][i];
            }
        }
    }
}

int main() {
    std::size_t n = 0;
    std::cin >> n;
    vic::Vector<vic::Vector<int64_t>> table(n + 2);

    for (std::size_t i = 0; i < n + 2; i++) {
        vic::Vector<int64_t> temp(n + 2);
        table[i] = temp;
    }

    fill_table(table, n);
    std::cout << table[n][n];

    return 0;
}
