/* Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop*.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение. Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
 */


#include "Queue.hpp"
#include <stdexcept>


int main() {
    Queue<int> q;

    bool ok = true;
    int command = 0;
    int value = 0;

    size_t n = 0;
    std::cin >> n;

    for (size_t i = 0; i < n; i++){
        std::cin >> command;
        std::cin >> value;

        switch(command){
            case 2:{
                int elem = 0;

                try {
                    elem = q.pop_front();
                }
                catch (const std::runtime_error& err){
                    elem = -1;
                }

                if (value != elem){
                    ok = false;
                }
            }break;

            case 3:{
                q.push_back(value);
            }break;

            default:{}
        }

        if (!ok){
            std::cout << "NO " << "command number " << i+1;
            break;
        }
    }
    if (ok)
        std::cout << "YES";

    return 0;
}