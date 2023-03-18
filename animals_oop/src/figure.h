#ifndef FIGURE_H
#define FIGURE_H

class Figure {
 public:
  virtual ~Figure();
  virtual void area() const = 0;
};

#endif  // FIGURE_H