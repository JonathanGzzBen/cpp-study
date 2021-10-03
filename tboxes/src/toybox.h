#ifndef TBOXES_SRC_TOYBOX_H_
#define TBOXES_SRC_TOYBOX_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/i_figure.h"

class ToyBox {
 private:
  std::string name;
  std::vector<std::unique_ptr<I_Figure>> figures;

 public:
  explicit ToyBox(std::string name);
  ~ToyBox();
  std::string get_name() const;
  bool set_name(std::string name);
  std::vector<std::unique_ptr<I_Figure>>& get_figures();
};

#endif  // TBOXES_SRC_TOYBOX_H_
