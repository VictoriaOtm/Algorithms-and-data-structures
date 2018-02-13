/* 3_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
 * A[0..n-1] и B[0..m-1]. n >> m.
 * Найдите их пересечение.
 * Требуемое время работы: O(m * log k), где k - позиция элемента B[m-1] в массиве A..
 * В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1].
n, k ≤ 10000.
*/


#include <iostream>

typedef struct Array {
    long* data;
    int size;

    Array() = default;

    Array(const int new_size) : size(new_size) {
        data = new long[size]();
    }

    ~Array() {
        delete[] data;
    }

    void fill_array() {
        for (size_t i = 0; i < size; i++) {
            std::cin >> data[i];
        }
    }

} array;

int binary_search(const array& A, const long elem, int first_index, int last_index) {
    int last = last_index;
    int first = first_index;

    while (first < last) {
        int mid = (first + last) / 2;
        if (A.data[mid] < elem) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }

    return (first == last_index || A.data[first] != elem) ? -1 : first;
}


bool find_elem(const array& A, const long elem, int& first) {
    int prev_index = first;
    int last = A.size;

    for (int i = first, pow_f = 1; i < last; i += pow_f, pow_f <<= 1) {
        if (A.data[i] == elem) {
            first = i;
            return true;
        }

        if (A.data[i] < elem) {
            prev_index = i;
            first = i;
        } else {
            last = i;
            first = prev_index;
        }
    }
    first = binary_search(A, elem, first, last);

    if (first == -1){
        first = prev_index;
        return false;
    }
    return true;

}

void find_intersection(const array& A, const array& B) {

    for (int i = 0, cur_index = 0; i < B.size && cur_index < A.size; i++) {
        if (find_elem(A, B.data[i], cur_index)) {
            std::cout << B.data[i] << '\n';
        }
    }
}

int main() {
    int A_size;
    int B_size;

    std::cin >> A_size >> B_size;

    Array A(A_size);
    Array B(B_size);

    A.fill_array();
    B.fill_array();

    find_intersection(A, B);

    return 0;
}
