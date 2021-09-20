#ifndef TBOXES_SRC_TOYBOX_H_
#define TBOXES_SRC_TOYBOX_H_
#include <iostream>
#include <string>
#include <vector>

#include "src/triangle.h"

class ToyBox {
 private:
  std::string name;
  std::vector<Triangle*> triangles;

 public:
  explicit ToyBox(std::string name);
  ~ToyBox();
  std::string get_name() const;
  bool set_name(std::string name);
  std::vector<Triangle*> get_triangles();
};

#endif  // TBOXES_SRC_TOYBOX_H_
