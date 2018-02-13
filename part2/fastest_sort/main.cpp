#include <iostream>
#include <unistd.h>

#define BUFFSIZE 0xF400 //l1

char tmpChar[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32};


inline size_t inputNums(int *arr) {
    int temp = 0;
    size_t currNum = 0;
    size_t i = 0;
    char *buffer = new char[BUFFSIZE];

    ssize_t numsRead = 0;
    for (; (numsRead = read(STDIN_FILENO, buffer, BUFFSIZE)) > 0;) {
        for (i = 0; i < numsRead; i++) {
            if (buffer[i] > 47) temp = temp * 10 + (int(buffer[i]) - 48);
            else {
                arr[currNum++] = temp;
                temp = 0;
            };
        }
    }
    delete[] buffer;
    return currNum;
}


void inline radix_lsb(int *begin, int *end, int *begin1, int maxshift) {
    register int *end1 = begin1 + (end - begin);

    for (int shift = 0; shift <= maxshift; shift += 8) {
        register size_t count[0x100] = {};

        for (int *p = begin; p != end; p++)
            count[(*p >> shift) & 0xFF]++;

        int *bucket[0x100], *q = begin1;
        for (int i = 0; i < 0x100; q += count[i++])
            bucket[i] = q;

        for (int *p = begin; p != end; p++)
            *bucket[(*p >> shift) & 0xFF]++ = *p;

        std::swap(begin, begin1);
        std::swap(end, end1);
    }
}


void radix_sort(int *begin, int *end) {
    int *begin1 = new int[end - begin];

    size_t count[0x3B] = {};
    for (int *p = begin; p != end; p++)
        count[*p >> 24]++;

    int *bucket[0x3B], *obucket[0x3B], *q = begin1;
    for (int i = 0; i < 0x3B; q += count[i++])
        obucket[i] = bucket[i] = q;

    for (int *p = begin; p != end; p++)
        *bucket[*p >> 24]++ = *p;

    for (int i = 0; i < 0x3B; ++i)
        radix_lsb(obucket[i], bucket[i], begin + (obucket[i] - begin1), 16);

    delete[] begin1;
}

struct itostr_helper {
    static unsigned out[10000];

    itostr_helper() {
        for (int i = 0; i < 10000; i++) {
            unsigned v = i;
            char *o = (char *) (out + i);
            o[3] = v % 10 + '0';
            o[2] = (v % 100) / 10 + '0';
            o[1] = (v % 1000) / 100 + '0';
            o[0] = (v % 10000) / 1000;
            if (o[0]) o[0] |= 0x30;
            else if (o[1] != '0') o[0] |= 0x20;
            else if (o[2] != '0') o[0] |= 0x10;
            else o[0] |= 0x00;
        }
    }
};

unsigned itostr_helper::out[10000];

itostr_helper hlp_init;

unsigned blocks[3];

template<typename T>
int itostr(T o, char *&arr) {
    typedef itostr_helper hlp;

    unsigned *b = blocks + 2;
    blocks[0] = o < 0 ? ~o + 1 : o;
    blocks[2] = blocks[0] % 10000;
    blocks[0] /= 10000;
    blocks[2] = hlp::out[blocks[2]];

    if (blocks[0]) {
        blocks[1] = blocks[0] % 10000;
        blocks[0] /= 10000;
        blocks[1] = hlp::out[blocks[1]];
        blocks[2] |= 0x30303030;
        b--;
    }

    if (blocks[0]) {
        blocks[0] = hlp::out[blocks[0] % 10000];
        blocks[1] |= 0x30303030;
        b--;
    }

    char *f = ((char *) b);
    f += 3 - (*f >> 4);

    char *str = (char *) blocks;
    if (o < 0) *--f = '-';
    arr = f;
    return (str + 12) - f;
}

char *buff;

void writeInt(int val) {
    int size = itostr<int>(val, buff);

    for (int i = 0; i < size; i++) {
        putchar_unlocked(buff[i]);
    }
    putchar_unlocked(32);
}

int main() {

    int *arr = new int[25000000];

    setvbuf(stdout, NULL, _IOFBF, 1024 * 1024 * 27); // large buffer

    size_t sizeArr = inputNums(arr);
    radix_sort(arr, arr + sizeArr);
    for (size_t i = 9; i < sizeArr; writeInt(arr[i]), i += 10);

    delete[] arr;
}