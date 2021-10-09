#ifndef TBOXES_SRC_TOYBOX_NOT_FOUND_H_
#define TBOXES_SRC_TOYBOX_NOT_FOUND_H_
#include <iostream>
#include <ostream>
#include <string>

class ToyBoxNotFound : public std::exception {
 private:
  std::string message;

 public:
  explicit ToyBoxNotFound(std::string box_name) noexcept
      : message{box_name + " not found"} {}
  ~ToyBoxNotFound() = default;
  virtual const char* what() const noexcept;
};

#endif  // TBOXES_SRC_TOYBOX_NOT_FOUND_H_
