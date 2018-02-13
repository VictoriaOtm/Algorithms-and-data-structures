#include <iostream>
#include <fstream>
#include <cstddef>
#include <vector>

template<class Value, class Hash>
class HashSet {
public:
    explicit HashSet(const Hash &hash) : _hash(hash),
                                         _size(0),
                                         _capacity(8),
                                         _is_empty(_capacity, true),
                                         _is_deleted(_capacity, false) {
        _data = new Value[_capacity]();
    }

    ~HashSet() {
        delete[] _data;
    }


    bool add(const Value &value) {
        if (_size >= (_capacity * 3) / 4) {
            resize();
        }

        size_t index = 0;
        int current_deleted = -1;

        for (size_t i = 0; i < _capacity; i++) {
            index = _hash(value, _capacity, i);

            if (_is_empty[index] && !_is_deleted[index]) {
                if (current_deleted == -1){
                    _data[index] = value;
                    ++_size;

                    _is_empty[index] = 0;
                    _is_deleted[index] = 0;
                    return true;
                }
                break;
            }

            if (_is_empty[index] && _is_deleted[index]){
                if (current_deleted == -1){
                    current_deleted = index;
                }
            }

            if (!_is_empty[index] && _data[index] == value) {
                return false;
            }

        }
        if (current_deleted != -1){
            _data[current_deleted] = value;
            ++_size;

            _is_empty[current_deleted] = 0;
            _is_deleted[current_deleted] = 0;
            return true;
        }

        return false;
    }

    bool remove(const Value &value) {
        int index = search(value);

        if (index != -1) {
            _is_deleted[index] = true;
            _is_empty[index] = true;
            --_size;

            return true;
        }

        return false;
    }

    bool has(const Value &value) {
        return search(value) != -1;
    }

private:
    Value *_data;
    Hash _hash;

    size_t _size; //count of elements
    size_t _capacity; //size of table

    std::vector<bool> _is_empty;
    std::vector<bool> _is_deleted;

    int search(const Value &value) {
        int index = 0;

        for (size_t i = 0; i < _capacity; i++) {
            index = _hash(value, _capacity, i);

            if (_is_empty[index] && !_is_deleted[index]) {
                return -1;
            }

            if (!_is_empty[index] && _data[index] == value) {
                return index;
            }
        }

        return -1;
    }

    void resize() {
        std::vector<bool> old_empty = _is_empty;
        std::vector<bool> old_deleted = _is_deleted;

        size_t old_capacity = _capacity;
        _capacity *= 2;
        _size = 0;

        auto old_data = _data;
        _data = new Value[_capacity];

        _is_empty.assign(_capacity, true);
        _is_deleted.assign(_capacity, false);

        for (size_t i = 0; i < old_capacity; i++) {
            if (!old_empty[i]) {
                add(old_data[i]);
            }
        }

        delete[] old_data;
    }

};


class Hash {
public:
    explicit Hash() = default;

    size_t operator()(const std::string &str, size_t mod, size_t probe) {
        return count_hash(str, mod, probe);
    }

private:
    size_t hash_factor = 11011;

    size_t count_hash(const std::string &str, size_t mod, size_t probe) {
        size_t hash = 0;

        if (probe == 0) {
            for (auto i = str.begin(); i < str.end(); i++) {
                hash = hash * hash_factor + (size_t) (*i);
            }

        } else {
            hash = count_hash(str, mod, probe - 1) + probe;
        }

        return hash % mod;
    }

};


int main() {

    Hash hash;
    HashSet<std::string, Hash> string_set(hash);

    std::ifstream in("input.txt", std::ios::in);

    std::string str;
    char operation;

    while (in.good()) {

        if (!(in >> operation && in >> str)) {
            break;
        }

        switch (operation) {
            case '+': {
                string_set.add(str) ? std::cout << "OK" : std::cout << "FAIL";
            }
                break;

            case '?': {
                string_set.has(str) ? std::cout << "OK" : std::cout << "FAIL";
            }
                break;

            case '-': {
                string_set.remove(str) ? std::cout << "OK" : std::cout << "FAIL";
            }
                break;

            default: {

            }
                break;
        }

        std::cout << std::endl;
    }

    in.close();

    return 0;
}