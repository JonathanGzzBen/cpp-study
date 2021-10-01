#ifndef TBOXES_SRC_TOYBOX_H_
#define TBOXES_SRC_TOYBOX_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/triangle.h"

class ToyBox {
 private:
  std::string name;
  std::vector<std::unique_ptr<Triangle>> triangles;

 public:
  explicit ToyBox(std::string name);
  ~ToyBox();
  std::string get_name() const;
  bool set_name(std::string name);
  std::vector<std::unique_ptr<Triangle>>& get_triangles();
};

#endif  // TBOXES_SRC_TOYBOX_H_
