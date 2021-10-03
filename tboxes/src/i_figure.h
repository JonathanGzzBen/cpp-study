#ifndef TBOXES_SRC_I_FIGURE_H_
#define TBOXES_SRC_I_FIGURE_H_
#include <iostream>

#include "src/i_printable.h"

class I_Figure : public I_Printable {
 public:
  virtual ~I_Figure() = default;
  virtual int get_area() const = 0;
};
#endif  // TBOXES_SRC_I_FIGURE_H_
