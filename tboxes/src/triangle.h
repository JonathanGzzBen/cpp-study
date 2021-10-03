#ifndef TBOXES_SRC_TRIANGLE_H_
#define TBOXES_SRC_TRIANGLE_H_
#include <iostream>
#include <ostream>

#include "src/i_figure.h"

class Triangle : public I_Figure {
 private:
  int base;
  int height;

 public:
  Triangle(int base, int height);
  virtual ~Triangle();
  int get_area() const override;
  void print(std::ostream &os) const override;
};

#endif  // TBOXES_SRC_TRIANGLE_H_
