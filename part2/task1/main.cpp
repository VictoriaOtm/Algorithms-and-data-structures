#include <iostream>
#include <vector>
#include <cmath>


struct Point {
    int x = 0;
    int y = 0;

    Point() = default;

    Point(const Point& point) = default;

    Point(const int _x, const int _y) : x(_x), y(_y) {}

    Point& operator=(const Point& point) = default;

    inline bool operator==(const Point& rhs) const {
        return (x == rhs.x && y == rhs.y);
    }

    friend std::istream& operator>>(std::istream& is, Point& point);

    friend std::ostream& operator<<(std::ostream& os, Point& point);

    ~Point() = default;
};


struct Compare {

    explicit Compare(const Point& sp = {0, 0}) : start_point(sp) {};

    bool operator()(const Point& first, const Point& second) const {
        return compare_by_angle(first, second);
    }

private:
    Point start_point;

    double tan_point(const Point& point) const {
        double new_y = point.y - start_point.y;
        double new_x = point.x - start_point.x;

        return new_y / new_x;
    }

    //if first > second return true
    //else return false

    bool compare_by_angle(const Point& first, const Point& second) const {
        if (first == start_point) {
            return true;
        }

        if (second == start_point) {
            return false;
        }

        if (first.x == start_point.x) {
            return true;
        }

        if (second.x == start_point.x) {
            return false;
        }

        return tan_point(first) > tan_point(second);
    }
};

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point& point) {
    os << point.x << " " << point.y;
    return os;
}


void fill_vec(std::vector<Point>& vec) {
    for (auto& i : vec) {
        std::cin >> i;
    }
}

Point get_start_point(std::vector<Point>& vec) {
    Point start_p = vec[0];

    for (std::size_t i = 1; i < vec.size(); i++) {
        if (vec[i].x < start_p.x) {
            start_p = vec[i];
        } else if (vec[i].x == start_p.x && vec[i].y < start_p.y) {
            start_p = vec[i];
        }
    }

    return start_p;
}


template<typename Iterator, typename Compare>
void insertion_sort(Iterator begin, Iterator end, Compare cmp) {

    for (Iterator i = begin + 1; i < end; i++) {
        typename Iterator::value_type tmp = *i;

        Iterator j = i - 1;
        for (; j >= begin && cmp(tmp, *j); j--) {
            *(j + 1) = *j;
        }
        *(j + 1) = tmp;
    }
}

template<typename Iterator>
void insertion_sort(Iterator begin, Iterator end) {
    std::less<typename Iterator::value_type> cmp;

    return insertion_sort(begin, end, cmp);
}

int main() {
    std::size_t point_num;
    std::cin >> point_num;

    std::vector<Point> vec(point_num);
    fill_vec(vec);

    Compare compare(get_start_point(vec));

    insertion_sort(vec.begin(), vec.end(), compare);

    for (auto& i : vec) {
        std::cout << i << std::endl;
    }

    return 0;
}
