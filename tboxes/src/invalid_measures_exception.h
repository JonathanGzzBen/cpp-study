#ifndef TBOXES_SRC_INVALID_MEASURES_EXCEPTION_H_
#define TBOXES_SRC_INVALID_MEASURES_EXCEPTION_H_
#include <iostream>
#include <ostream>
#include <string>

class InvalidMeasuresException : public std::exception {
 private:
  std::string message;

 public:
  explicit InvalidMeasuresException(std::string message) noexcept
      : message{message} {}
  ~InvalidMeasuresException() = default;
  virtual const char* what() const noexcept;
};

#endif  // TBOXES_SRC_INVALID_MEASURES_EXCEPTION_H_
