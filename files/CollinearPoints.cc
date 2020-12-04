#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>
//sort using -O3 flag for fast sort
namespace AMA {
  template <typename T>
  class Compare {
  public:
    bool operator()(T a, T b) { //overloading the parenthesis operator for use in sort function
      return a < b;
    }
  };

  class Point{
    int x;
    int y;
  public:
    Point(int _x, int _y) : x{_x}, y{_y} {}
    Point():x{0}, y{0} {}

    void print_point() {
      std::cout << x << " " << y << '\n';
    }

    bool operator<(Point p) {
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

  class LineSegment{
  public:
    LineSegment(Point a, Point b) {
      p = new Point(a.x_crd(), a.y_crd());
      q = new Point(b.x_crd(), b.y_crd());
      //std::cout << "main constructor" << '\n';
    }

    LineSegment(const LineSegment& ls) { //copy constructor
      p = new Point(ls.point_p()->x_crd(), ls.point_p()->y_crd());
      q = new Point(ls.point_q()->x_crd(), ls.point_q()->y_crd());
      //std::cout << "copy constructor" << '\n';
    }

    LineSegment& operator=(const LineSegment& ls) { //copy assignment
      Point* temp_p = new Point(ls.point_p()->x_crd(), ls.point_p()->y_crd());
      Point* temp_q = new Point(ls.point_q()->x_crd(), ls.point_q()->y_crd());
      delete p;
      delete q;
      p = temp_p;
      q = temp_q;
      //std::cout << "copy assignment" << '\n';
      return *this;
    }

    LineSegment(LineSegment&& ls) noexcept { //move constructor
      /*noexcept ensures move constructor to be called when the vector reallocates
      memory*/
      p = ls.p;
      q = ls.q;
      ls.p = nullptr;
      ls.q = nullptr;
      //std::cout << "move constructor" << '\n';
    }

    LineSegment& operator=(LineSegment&& ls) noexcept   { //move assignment
      delete p;
      delete q;
      p = ls.p;
      q = ls.q;
      ls.p = nullptr;
      ls.q = nullptr;
      //std::cout << "move assignment" << '\n';
      return *this;
    }

    Point* point_p() const {
      return p;
    }

    Point* point_q() const {
      return q;
    }

    void printSegment() {
      std::cout << "(" << p->x_crd() << ", " << p->y_crd() << ") -> (" << q->x_crd() << ", "<< q->y_crd() << ")\n";
    }

    ~LineSegment() {
      delete p;
      delete q;
    }

  private:
    Point* p;
    Point* q;
  };

  class FastCollinearPoints {
  public:
    FastCollinearPoints(std::vector<Point>& points): numberOfSegments{0} {

      Compare<Point> compare_points;
      std::sort(points.begin(), points.end(), compare_points);

      int count;
      int k, l;

      for (size_t i = 0; i < points.size() - 3; i++) {
        std::vector<Point> temp_points(points.size() - i - 1);
        //std::vector<Point> temp_points; use back_inserter() with this approach
        std::copy(points.begin() + i + 1, points.end(), temp_points.begin());
        //Point::CompareSlopeOrder cmpslp(&points[i]);
        auto cmpslp = [&points, &i](Point a, Point b) { //lambda
          return points[i].slopeTo(a) < points[i].slopeTo(b);
        };

        std::sort(temp_points.begin(), temp_points.end(), cmpslp);

        count = 0;

        for (k = 0; k < temp_points.size(); k++) {
          for (l = k; l < temp_points.size() - 1; l++) {
            if (points[i].slopeTo(temp_points[l]) == points[i].slopeTo(temp_points[l + 1])) {
              count++;
            } else break;
          }

          if (count >= 2) {
            LineSegment tempLine(points[i], temp_points[k + count]);
            lines.push_back(std::move(tempLine));
            numberOfSegments++;
          }
          count = 0;
          k = l;
        }
      }
    }

    int numSegments() {
      return numberOfSegments;
    }

    std::vector<LineSegment>& segments() {
      return lines;
    }

  private:
    std::vector<LineSegment> lines;
    int numberOfSegments;
  };
}

int main(int argc, char const *argv[]) {
  const auto start = std::chrono::steady_clock::now();
  int n_points;
  int x, y;

  std::cin >> n_points;

  std::vector<AMA::Point> v_points;

  for (size_t i = 0; i < n_points; i++) {
    std::cin >> x >> y;
    AMA::Point p(x, y);
    v_points.push_back(p);
  }

  AMA::FastCollinearPoints fcp(v_points);
  std::cout << fcp.numSegments() << '\n';
  const auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time in seconds: " << elapsed.count() << '\n';
  std::vector<AMA::LineSegment> lines = std::move(fcp.segments());
  for (size_t i = 0; i < lines.size(); i++) {
    lines[i].printSegment();
  }
  //AMA::Compare<AMA::Point> compare_points; //الحمد لله works!
  std::cout << __cplusplus << '\n';

  return 0;
}
