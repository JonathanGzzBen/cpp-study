#ifndef TBOXES_SRC_TRIANGLE_H_
#define TBOXES_SRC_TRIANGLE_H_
#include <iostream>

class Triangle {
 private:
  int base;
  int height;

 public:
  Triangle(int base, int height);
  int get_area() const;
  friend std::ostream &operator<<(std::ostream &os, const Triangle &triangle);
};

#endif  // TBOXES_SRC_TRIANGLE_H_
