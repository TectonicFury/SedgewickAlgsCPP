#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

class Point{
  int x;
  int y;
public:
  Point(int _x, int _y) : x{_x}, y{_y} {}
  Point():x{0}, y{0} {}
  //hi
  void print_point() {
    std::cout << x << " " << y << '\n';
  }

  bool operator<(const Point p) const {
    if (this->y < p.y) return true;
    if (this->y == p.y && this->x < p.x) return true;
    return false;
  }

  int x_crd() {
    return x;
  }

  int y_crd() {
    return y;
  }

  double slopeTo(Point p) {
    if (this->x == p.x) return INFINITY;
    return static_cast<double>(p.y - this->y)/(p.x - this->x);
  }

  bool cmpSlopeOrder(Point a, Point b) {
    if (slopeTo(a) < slopeTo(b)) return true;
    return false;
  }

  class CompareSlopeOrder { //will wrap call to cmpSlopeOrder()
  public:
    CompareSlopeOrder(Point* outer) {
      _outer = outer;
    }
    bool operator()(Point a, Point b) {
      return _outer->cmpSlopeOrder(a, b);
    }
  private:
    Point* _outer;
  };
};

namespace AMA {
  template <typename Iterator , typename T> // Iterator should satisfy * and ++
  void selection_sort(Iterator begin, Iterator end) {
    //using value_type = T;
    T min;
    T temp;
    //unsigned int n = end - begin;
    for (auto& i = begin; i != end; i++) {
      min = *i;
      for (auto j = i + 1; j != end; j++) {
        if (*j < min) {
          min = *j;
          *j = *i;
          *i = min;
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  std::mt19937_64 engine(time(NULL));
  std::uniform_int_distribution dist(1, 6);

  std::vector<Point> v(100000);

  for (auto& i : v) {
    i = Point(dist(engine), dist(engine));
  }

  std::vector<Point> v_copy = v;
  
  const auto start = std::chrono::steady_clock::now();
  AMA::selection_sort<decltype(v.begin()), Point>(v.begin(), v.end());
  const auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time in seconds for selection_sort: " << elapsed.count() << '\n';

  const auto start2 = std::chrono::steady_clock::now();
  std::sort(v_copy.begin(), v_copy.end());
  const auto end2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed2 = end2 - start2;
  std::cout << "Time in seconds for std::sort: " << elapsed2.count() << '\n';

  return 0;
}
