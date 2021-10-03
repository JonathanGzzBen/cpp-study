#ifndef TBOXES_SRC_SQUARE_H_
#define TBOXES_SRC_SQUARE_H_
#include <iostream>
#include <ostream>

#include "src/i_figure.h"

class Square : public I_Figure {
 private:
  int side;

 public:
  Square(int side);
  virtual ~Square();
  int get_area() const override;
  void print(std::ostream &os) const override;
};

#endif  // TBOXES_SRC_SQUARE_H_
