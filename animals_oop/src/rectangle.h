#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"

class Rectangle : public Figure {
 private:
  double _width;
  double _height;

 public:
  Rectangle(double width, double height);
  virtual ~Rectangle();
  void area() const override;
};

#endif  // RECTANGLE_H