#include "src/invalid_measures_exception.h"

const char* InvalidMeasuresException::what() const noexcept {
    return message.c_str();
}
