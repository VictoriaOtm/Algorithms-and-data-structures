#include <iostream>


typedef struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}

    Point(const int new_x, const int new_y) :
            x(new_x), y(new_y) {}
} point;


class Polygon_square {
public:
    Polygon_square(const size_t amount) :
            points_num(amount),
            square(0),
            max_coordinate(0, 0),
            min_coordinate(0, 0) {
        coordinates_arr = new point[points_num]();
    }

    ~Polygon_square() {
        delete[] coordinates_arr;
    }

    const double get_square() {
        return square;
    }

    void read_coordinates() {
        for (size_t i = 0; i < points_num; i++) {
            std::cin >> coordinates_arr[i].x >> coordinates_arr[i].y;
        }
    }

    void print_coordinates() {
        for (size_t i = 0; i < points_num; i++) {
            std::cout << coordinates_arr[i].x
                      << ' '
                      << coordinates_arr[i].y
                      << std::endl;
        }
    }

    float count_trapeze(const point& first_coord, const point& second_coord) {
        float edge_y = first_coord.y + second_coord.y;
        float edge_x = 0;
        float delta_square = 0;

        if (first_coord.x > second_coord.x) {
            edge_x = first_coord.x - second_coord.x;

            delta_square = edge_x * ((edge_y / 2) - min_coordinate.y);
        } else {
            edge_x = second_coord.x - first_coord.x;

            delta_square = edge_x * (max_coordinate.y - (edge_y / 2));
        }

        return delta_square;
    }

    void count_square() {
        find_min();
        find_max();

        square = (max_coordinate.x - min_coordinate.x) * (max_coordinate.y - min_coordinate.y);
        for (size_t i = points_num - 1; i > 0; i--) {
            square -= count_trapeze(coordinates_arr[i], coordinates_arr[i - 1]);

        }

        square -= count_trapeze(coordinates_arr[0], coordinates_arr[points_num - 1]);
    	square = (square < 0) ? -square : square;

    }

    void find_max() {
        max_coordinate.x = coordinates_arr[0].x;
        max_coordinate.y = coordinates_arr[0].y;

        for (size_t i = 1; i < points_num; i++) {
            if (coordinates_arr[i].x > max_coordinate.x) {
                max_coordinate.x = coordinates_arr[i].x;
            }

            if (coordinates_arr[i].y > max_coordinate.y) {
                max_coordinate.y = coordinates_arr[i].y;
            }
        }
    }

    void find_min() {
        min_coordinate.x = coordinates_arr[0].x;
        min_coordinate.y = coordinates_arr[0].y;

        for (size_t i = 1; i < points_num; i++) {
            if (coordinates_arr[i].x < min_coordinate.x) {
                min_coordinate.x = coordinates_arr[i].x;
            }

            if (coordinates_arr[i].y < min_coordinate.y) {
                min_coordinate.y = coordinates_arr[i].y;
            }
        }
    }

private:
    const size_t points_num;

    float square;
    point* coordinates_arr;

    point max_coordinate;
    point min_coordinate;

};


int main() {
    size_t num = 0;
    std::cin >> num;

    if (num < 3) {
        std::cout << 0;
        return 0;
    }

    Polygon_square new_polygon(num);

    new_polygon.read_coordinates();

    new_polygon.count_square();

    std::cout << new_polygon.get_square();

    return 0;
}
