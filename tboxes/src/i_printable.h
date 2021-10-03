#ifndef TBOXES_SRC_I_PRINTABLE_H_
#define TBOXES_SRC_I_PRINTABLE_H_
#include <iostream>
class I_Printable {
 public:
  friend std::ostream &operator<<(std::ostream &os, const I_Printable &obj);
  virtual void print(std::ostream &os) const = 0;
  virtual ~I_Printable() = default;
};

#endif  //  TBOXES_SRC_I_PRINTABLE_H_
